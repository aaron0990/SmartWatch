/*
 * BluetoothManager.cpp
 *
 *  Created on: 16 mar 2024
 *      Author: root
 */

#include "BluetoothManager.h"
#include "esp_log.h"
#include "esp_bt.h"
#include <cstring>

static const char* GATTC_TAG = "BluetoothManager";

std::string BluetoothManager::remote_device_name = "Redmi Note 7";
bool BluetoothManager::connect = false;
bool BluetoothManager::get_server = false;
esp_gattc_char_elem_t *BluetoothManager::char_elem_result = nullptr;
esp_gattc_descr_elem_t *BluetoothManager::descr_elem_result = nullptr;

esp_bt_uuid_t BluetoothManager::remote_filter_service_uuid = { .len = ESP_UUID_LEN_16, .uuid = {.uuid16 = 0x00FF} };
esp_bt_uuid_t BluetoothManager::remote_filter_char_uuid = { .len = ESP_UUID_LEN_16, .uuid = {.uuid16 = 0xFF01} };
esp_bt_uuid_t BluetoothManager::notify_descr_uuid = { .len = ESP_UUID_LEN_16, .uuid = {.uuid16 = ESP_GATT_UUID_CHAR_CLIENT_CONFIG} };

esp_ble_scan_params_t BluetoothManager::ble_scan_params = {
    .scan_type = BLE_SCAN_TYPE_ACTIVE,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
    .scan_interval = 0x50,
    .scan_window = 0x30,
    .scan_duplicate = BLE_SCAN_DUPLICATE_DISABLE
};

/* One gatt-based profile one app_id and one gattc_if, this array will store the gattc_if returned by ESP_GATTS_REG_EVT */
struct gattc_profile_inst BluetoothManager::gl_profile_tab[PROFILE_NUM] = {
    [PROFILE_A_APP_ID] = {
        .gattc_cb = gattc_profile_event_handler,
        .gattc_if = ESP_GATT_IF_NONE,       /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
    },
};


BluetoothManager::BluetoothManager(const std::string& target_device_name) {
    remote_device_name = target_device_name;
}

BluetoothManager::~BluetoothManager() {
    // Clean up dynamic resources if any
}

void BluetoothManager::initialize() {
    esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
    initialize_bluetooth_controller();
    initialize_bluedroid();
    esp_ble_gap_register_callback(gap_event_handler);
    esp_ble_gattc_register_callback(gattc_event_handler);
    esp_ble_gattc_app_register(PROFILE_A_APP_ID);
}

void BluetoothManager::startScan() {
    esp_ble_gap_start_scanning(30); // Scanning for 30 seconds
}

void BluetoothManager::stopScan() {
    esp_ble_gap_stop_scanning();
}


void BluetoothManager::initialize_bluetooth_controller() {
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_err_t ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
		ESP_LOGE(GATTC_TAG, "%s initialize controller failed: %s", __func__, esp_err_to_name(ret));
		return;
	}
    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
    if (ret) {
		ESP_LOGE(GATTC_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name(ret));
		return;
	}
}

void BluetoothManager::initialize_bluedroid() {
	esp_bluedroid_config_t bluedroid_cfg = BT_BLUEDROID_INIT_CONFIG_DEFAULT();
	esp_err_t ret = esp_bluedroid_init_with_cfg(&bluedroid_cfg);
	if (ret) {
		ESP_LOGE(GATTC_TAG, "%s init bluetooth failed: %s", __func__, esp_err_to_name(ret));
		return;
	}
	ret = esp_bluedroid_enable();
	if (ret) {
		ESP_LOGE(GATTC_TAG, "%s enable bluetooth failed: %s", __func__, esp_err_to_name(ret));
		return;
	}
}


void BluetoothManager::gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
    switch (event) {
        case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT:
            if (param->scan_param_cmpl.status == ESP_BT_STATUS_SUCCESS) {
                ESP_LOGI(GATTC_TAG, "Scan parameters set, starting scan");
                esp_ble_gap_start_scanning(30);
            } else {
                ESP_LOGE(GATTC_TAG, "Failed to set scan parameters, error code: %d", param->scan_param_cmpl.status);
            }
            break;

        case ESP_GAP_BLE_SCAN_RESULT_EVT:
        	if (param->scan_rst.search_evt == ESP_GAP_SEARCH_INQ_RES_EVT) {
				const uint8_t *adv_name = esp_ble_resolve_adv_data(param->scan_rst.ble_adv,
																   ESP_BLE_AD_TYPE_NAME_CMPL, &param->scan_rst.adv_data_len);
				if (adv_name && strncmp((char *)adv_name, remote_device_name.c_str(), param->scan_rst.adv_data_len) == 0) {
					ESP_LOGI(GATTC_TAG, "Device found: %s", remote_device_name.c_str());
					esp_ble_gap_stop_scanning();
					esp_ble_gattc_open(gl_profile_tab[PROFILE_A_APP_ID].gattc_if, param->scan_rst.bda, BLE_ADDR_TYPE_PUBLIC, true);
				}
			}
            break;

        case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
            if (param->scan_stop_cmpl.status == ESP_BT_STATUS_SUCCESS) {
                ESP_LOGI(GATTC_TAG, "Scan stopped successfully");
            } else {
                ESP_LOGE(GATTC_TAG, "Failed to stop scanning, error code: %d", param->scan_stop_cmpl.status);
            }
            break;

        default:
            ESP_LOGI(GATTC_TAG, "Unhandled GAP event %d", event);
            break;
    }
}


void BluetoothManager::gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param) {
    switch (event) {
        case ESP_GATTC_REG_EVT:
            if (param->reg.status == ESP_GATT_OK) {
                ESP_LOGI(GATTC_TAG, "GATT client registered, app_id %d", param->reg.app_id);
                esp_ble_gap_set_scan_params(&ble_scan_params);
            } else {
                ESP_LOGE(GATTC_TAG, "GATT client registration failed, status %d", param->reg.status);
            }
            break;

        case ESP_GATTC_CONNECT_EVT:
            ESP_LOGI(GATTC_TAG, "Connected to device");
            break;

        case ESP_GATTC_DISCONNECT_EVT:
            ESP_LOGI(GATTC_TAG, "Disconnected from device");
            break;

        default:
            ESP_LOGI(GATTC_TAG, "Unhandled GATTC event %d", event);
            break;
    }
}

void BluetoothManager::gattc_profile_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param) {
    esp_ble_gattc_cb_param_t *p_data = param;

    switch (event) {
	case ESP_GATTC_REG_EVT:
		ESP_LOGI(GATTC_TAG, "REG_EVT");
		esp_err_t scan_ret = esp_ble_gap_set_scan_params(&ble_scan_params);
		if (scan_ret) {
			ESP_LOGE(GATTC_TAG, "Set scan params error, error code = %x", scan_ret);
		}
		break;

	case ESP_GATTC_CONNECT_EVT:
		ESP_LOGI(GATTC_TAG, "ESP_GATTC_CONNECT_EVT conn_id %d, if %d", p_data->connect.conn_id, gattc_if);
		gl_profile_tab[PROFILE_A_APP_ID].conn_id = p_data->connect.conn_id;
		memcpy(gl_profile_tab[PROFILE_A_APP_ID].remote_bda, p_data->connect.remote_bda, sizeof(esp_bd_addr_t));
		ESP_LOGI(GATTC_TAG, "REMOTE BDA:");
		esp_log_buffer_hex(GATTC_TAG, gl_profile_tab[PROFILE_A_APP_ID].remote_bda, sizeof(esp_bd_addr_t));
		esp_ble_gattc_send_mtu_req(gattc_if, p_data->connect.conn_id);
		break;

	case ESP_GATTC_OPEN_EVT:
		if (p_data->open.status != ESP_GATT_OK) {
			ESP_LOGE(GATTC_TAG, "Open failed, status %d", p_data->open.status);
		} else {
			ESP_LOGI(GATTC_TAG, "Open success");
		}
		break;

	case ESP_GATTC_DIS_SRVC_CMPL_EVT:
		if (p_data->dis_srvc_cmpl.status != ESP_GATT_OK) {
			ESP_LOGE(GATTC_TAG, "Discover service failed, status %d", p_data->dis_srvc_cmpl.status);
		} else {
			ESP_LOGI(GATTC_TAG, "Discover service complete conn_id %d", p_data->dis_srvc_cmpl.conn_id);
			esp_ble_gattc_search_service(gattc_if, p_data->dis_srvc_cmpl.conn_id, &remote_filter_service_uuid);
		}
		break;

	case ESP_GATTC_CFG_MTU_EVT:
		if (p_data->cfg_mtu.status != ESP_GATT_OK) {
			ESP_LOGE(GATTC_TAG, "Config MTU failed, error status = %x", p_data->cfg_mtu.status);
		} else {
			ESP_LOGI(GATTC_TAG, "Config MTU success, MTU %d", p_data->cfg_mtu.mtu);
		}
		break;

	case ESP_GATTC_SEARCH_RES_EVT:
		ESP_LOGI(GATTC_TAG, "SEARCH RES: conn_id = %x is primary service %d", p_data->search_res.conn_id, p_data->search_res.is_primary);
		if (p_data->search_res.srvc_id.uuid.len == ESP_UUID_LEN_16 && p_data->search_res.srvc_id.uuid.uuid.uuid16 == REMOTE_SERVICE_UUID) {
			get_server = true;
			gl_profile_tab[PROFILE_A_APP_ID].service_start_handle = p_data->search_res.start_handle;
			gl_profile_tab[PROFILE_A_APP_ID].service_end_handle = p_data->search_res.end_handle;
		}
		break;

	case ESP_GATTC_SEARCH_CMPL_EVT:
		if (p_data->search_cmpl.status != ESP_GATT_OK){
			ESP_LOGE(GATTC_TAG, "search service failed, error status = %x", p_data->search_cmpl.status);
			break;
		}
		if(p_data->search_cmpl.searched_service_source == ESP_GATT_SERVICE_FROM_REMOTE_DEVICE) {
			ESP_LOGI(GATTC_TAG, "Get service information from remote device");
		}
		else if (p_data->search_cmpl.searched_service_source == ESP_GATT_SERVICE_FROM_NVS_FLASH) {
			ESP_LOGI(GATTC_TAG, "Get service information from flash");
		}
		else {
			ESP_LOGI(GATTC_TAG, "unknown service source");
		}
		ESP_LOGI(GATTC_TAG, "ESP_GATTC_SEARCH_CMPL_EVT");
		if (get_server){
			uint16_t count = 0;
			esp_gatt_status_t status = esp_ble_gattc_get_attr_count( gattc_if,
																	 p_data->search_cmpl.conn_id,
																	 ESP_GATT_DB_CHARACTERISTIC,
																	 gl_profile_tab[PROFILE_A_APP_ID].service_start_handle,
																	 gl_profile_tab[PROFILE_A_APP_ID].service_end_handle,
																	 INVALID_HANDLE,
																	 &count);
			if (status != ESP_GATT_OK){
				ESP_LOGE(GATTC_TAG, "esp_ble_gattc_get_attr_count error");
				break;
			}

			if (count > 0)
			{
				char_elem_result = (esp_gattc_char_elem_t *)malloc(sizeof(esp_gattc_char_elem_t) * count);
				if (!char_elem_result){
					ESP_LOGE(GATTC_TAG, "gattc no mem");
					break;
				}
				else
				{
					status = esp_ble_gattc_get_char_by_uuid( gattc_if,
															 p_data->search_cmpl.conn_id,
															 gl_profile_tab[PROFILE_A_APP_ID].service_start_handle,
															 gl_profile_tab[PROFILE_A_APP_ID].service_end_handle,
															 remote_filter_char_uuid,
															 char_elem_result,
															 &count);
					if (status != ESP_GATT_OK){
						ESP_LOGE(GATTC_TAG, "esp_ble_gattc_get_char_by_uuid error");
						free(char_elem_result);
						char_elem_result = NULL;
						break;
					}

					/*  Every service have only one char in our 'ESP_GATTS_DEMO' demo, so we used first 'char_elem_result' */
					if (count > 0 && (char_elem_result[0].properties & ESP_GATT_CHAR_PROP_BIT_NOTIFY)){
						gl_profile_tab[PROFILE_A_APP_ID].char_handle = char_elem_result[0].char_handle;
						esp_ble_gattc_register_for_notify (gattc_if, gl_profile_tab[PROFILE_A_APP_ID].remote_bda, char_elem_result[0].char_handle);
					}
				}
				/* free char_elem_result */
				free(char_elem_result);
			}
			else
			{
				ESP_LOGE(GATTC_TAG, "no char found");
			}
		}
		break;

	case ESP_GATTC_REG_FOR_NOTIFY_EVT:
		if (p_data->reg_for_notify.status == ESP_GATT_OK) {
			ESP_LOGI(GATTC_TAG, "Registered for notify on handle %d", p_data->reg_for_notify.handle);
		} else {
			ESP_LOGE(GATTC_TAG, "Reg for notify failed, error status = %d", p_data->reg_for_notify.status);
		}
		break;

	case ESP_GATTC_NOTIFY_EVT:
		if (p_data->notify.is_notify) {
			ESP_LOGI(GATTC_TAG, "Notification received, value len = %d", p_data->notify.value_len);
			esp_log_buffer_hex(GATTC_TAG, p_data->notify.value, p_data->notify.value_len);
		} else {
			ESP_LOGI(GATTC_TAG, "Indication received, value len = %d", p_data->notify.value_len);
		}
		break;

	case ESP_GATTC_WRITE_DESCR_EVT:
		if (p_data->write.status == ESP_GATT_OK) {
			ESP_LOGI(GATTC_TAG, "Descriptor write successful");
		} else {
			ESP_LOGE(GATTC_TAG, "Failed to write descriptor, error %d", p_data->write.status);
		}
		break;

	case ESP_GATTC_SRVC_CHG_EVT:
		ESP_LOGI(GATTC_TAG, "Service changed");
		break;

	case ESP_GATTC_DISCONNECT_EVT:
		ESP_LOGI(GATTC_TAG, "Disconnected");
		break;

	default:
		ESP_LOGI(GATTC_TAG, "Unhandled event %d", event);
		break;
    }
}
