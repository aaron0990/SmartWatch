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

#include "nvs_flash.h"

static const char* GATTC_TAG = "BluetoothManager";

std::string BluetoothManager::remote_device_name = "Redmi Note 7";
bool BluetoothManager::connect = false;
bool BluetoothManager::get_server = false;
esp_gattc_char_elem_t *BluetoothManager::char_elem_result = nullptr;
esp_gattc_descr_elem_t *BluetoothManager::descr_elem_result = nullptr;

// UUID Definitions
esp_bt_uuid_t BluetoothManager::weather_service_uuid = { .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xAA, 0xAA, 0x00, 0x00 } } };
esp_bt_uuid_t BluetoothManager::temperature_char_uuid = { .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xAA, 0xA1, 0x00, 0x00 } } };
esp_bt_uuid_t BluetoothManager::humidity_char_uuid = { .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xAA, 0xA2, 0x00, 0x00 } } };
esp_bt_uuid_t BluetoothManager::air_quality_char_uuid = { .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xAA, 0xA3, 0x00, 0x00 } } };
esp_bt_uuid_t BluetoothManager::weather_condition_char_uuid = { .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xAA, 0xA4, 0x00, 0x00 } } };

esp_bt_uuid_t BluetoothManager::notifications_service_uuid = { .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xBB, 0xBB, 0x00, 0x00 } } };
esp_bt_uuid_t BluetoothManager::notifications_char_uuid = { .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xBB, 0xB0, 0x00, 0x00 } } };

esp_bt_uuid_t BluetoothManager::tasks_service_uuid = { .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xCC, 0xCC, 0x00, 0x00 } } };
esp_bt_uuid_t BluetoothManager::tasks_char_uuid = { .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0xCC, 0xC1, 0x00, 0x00 } } };

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
		.app_id = PROFILE_A_APP_ID,         /* Not get the app_id, so initial is 0 */
    	.conn_id = 0,
		.service_start_handle = 0,
		.service_end_handle = 0,
		.char_handle = 0,
		.remote_bda = { },
    }
};


BluetoothManager::BluetoothManager() {
    //remote_device_name = "";
}

BluetoothManager::~BluetoothManager() {
    // Clean up dynamic resources if any
}

void BluetoothManager::initialize() {
    // Initialize NVS.
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
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
        {
            esp_ble_gap_cb_param_t *scan_result = (esp_ble_gap_cb_param_t *)param;
        	if (param->scan_rst.search_evt == ESP_GAP_SEARCH_INQ_RES_EVT) {
        		esp_log_buffer_hex(GATTC_TAG, scan_result->scan_rst.bda, 6);
        		ESP_LOGI(GATTC_TAG, "searched Adv Data Len %d, Scan Response Len %d", scan_result->scan_rst.adv_data_len, scan_result->scan_rst.scan_rsp_len);
				const uint8_t *adv_name = esp_ble_resolve_adv_data(scan_result->scan_rst.ble_adv,
																   ESP_BLE_AD_TYPE_NAME_CMPL, &scan_result->scan_rst.adv_data_len);
				if (adv_name && strncmp((char *)adv_name, remote_device_name.c_str(), scan_result->scan_rst.adv_data_len) == 0) {
					ESP_LOGI(GATTC_TAG, "Device found: %s", remote_device_name.c_str());
					esp_ble_gap_stop_scanning();
					esp_ble_gattc_open(gl_profile_tab[PROFILE_A_APP_ID].gattc_if, scan_result->scan_rst.bda, scan_result->scan_rst.ble_addr_type, true);
				}
			}
            break;
        }
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
	if (event == ESP_GATTC_REG_EVT)
	{
		if (param->reg.status == ESP_GATT_OK)
		{
			gl_profile_tab[param->reg.app_id].gattc_if = gattc_if;
			ESP_LOGI(GATTC_TAG, "reg app succeded, app_id %04x, gattc_if %d",
								param->reg.app_id, gattc_if);
		}
		else
		{
			ESP_LOGI(GATTC_TAG, "reg app failed, app_id %04x, status %d",
					param->reg.app_id, param->reg.status);
			return;
		}
	}
	do
	{
		int idx;
		for (idx = 0; idx < PROFILE_NUM; idx++) {
			if (gattc_if == ESP_GATT_IF_NONE || /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
			gattc_if == gl_profile_tab[idx].gattc_if) {
				if (gl_profile_tab[idx].gattc_cb) {
					gl_profile_tab[idx].gattc_cb(event, gattc_if, param);
				}
			}
		}
	}
	while (0);
}

void BluetoothManager::gattc_profile_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param) {
    esp_ble_gattc_cb_param_t *p_data = param;

    switch (event)
    {
		case ESP_GATTC_REG_EVT:
		{
			ESP_LOGI(GATTC_TAG, "REG_EVT");
			esp_err_t scan_ret = esp_ble_gap_set_scan_params(&ble_scan_params);
			if (scan_ret) {
				ESP_LOGE(GATTC_TAG, "Set scan params error, error code = %x", scan_ret);
			}
			break;
		}
		case ESP_GATTC_CONNECT_EVT:
		{
			ESP_LOGI(GATTC_TAG, "ESP_GATTC_CONNECT_EVT conn_id %d, if %d", p_data->connect.conn_id, gattc_if);
			gl_profile_tab[PROFILE_A_APP_ID].conn_id = p_data->connect.conn_id;
			memcpy(gl_profile_tab[PROFILE_A_APP_ID].remote_bda, p_data->connect.remote_bda, sizeof(esp_bd_addr_t));
			ESP_LOGI(GATTC_TAG, "REMOTE BDA:");
			esp_log_buffer_hex(GATTC_TAG, gl_profile_tab[PROFILE_A_APP_ID].remote_bda, sizeof(esp_bd_addr_t));
			esp_ble_gattc_send_mtu_req(gattc_if, p_data->connect.conn_id);
			break;
		}
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
				esp_ble_gattc_search_service(gattc_if, p_data->dis_srvc_cmpl.conn_id, NULL);
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
		{
			ESP_LOGI(GATTC_TAG, "SEARCH RES: conn_id = %x is primary service %d", p_data->search_res.conn_id, p_data->search_res.is_primary);
			if (p_data->search_res.srvc_id.uuid.len == ESP_UUID_LEN_128) {
				if (memcmp(p_data->search_res.srvc_id.uuid.uuid.uuid128, weather_service_uuid.uuid.uuid128, ESP_UUID_LEN_128) == 0) {
					get_server = true;
					gl_profile_tab[PROFILE_A_APP_ID].service_start_handle = p_data->search_res.start_handle;
					gl_profile_tab[PROFILE_A_APP_ID].service_end_handle = p_data->search_res.end_handle;
					ESP_LOGI(GATTC_TAG, "Weather service found");
				} else if (memcmp(p_data->search_res.srvc_id.uuid.uuid.uuid128, notifications_service_uuid.uuid.uuid128, ESP_UUID_LEN_128) == 0) {
					get_server = true;
					gl_profile_tab[PROFILE_A_APP_ID].service_start_handle = p_data->search_res.start_handle;
					gl_profile_tab[PROFILE_A_APP_ID].service_end_handle = p_data->search_res.end_handle;
					ESP_LOGI(GATTC_TAG, "Notifications service found");
				} else if (memcmp(p_data->search_res.srvc_id.uuid.uuid.uuid128, tasks_service_uuid.uuid.uuid128, ESP_UUID_LEN_128) == 0) {
					get_server = true;
					gl_profile_tab[PROFILE_A_APP_ID].service_start_handle = p_data->search_res.start_handle;
					gl_profile_tab[PROFILE_A_APP_ID].service_end_handle = p_data->search_res.end_handle;
					ESP_LOGI(GATTC_TAG, "Tasks service found");
				}
			}
			break;
		}

		case ESP_GATTC_SEARCH_CMPL_EVT:
			if (p_data->search_cmpl.status != ESP_GATT_OK) {
				ESP_LOGE(GATTC_TAG, "search service failed, error status = %x", p_data->search_cmpl.status);
				break;
			}
			ESP_LOGI(GATTC_TAG, "ESP_GATTC_SEARCH_CMPL_EVT");
			if (get_server) {
				uint16_t count = 0;
				esp_gatt_status_t status = esp_ble_gattc_get_attr_count(gattc_if,
					p_data->search_cmpl.conn_id,
					ESP_GATT_DB_CHARACTERISTIC,
					gl_profile_tab[PROFILE_A_APP_ID].service_start_handle,
					gl_profile_tab[PROFILE_A_APP_ID].service_end_handle,
					INVALID_HANDLE,
					&count);
				if (status != ESP_GATT_OK) {
					ESP_LOGE(GATTC_TAG, "esp_ble_gattc_get_attr_count error");
					break;
				}
				if (count > 0) {
					char_elem_result = (esp_gattc_char_elem_t *)malloc(sizeof(esp_gattc_char_elem_t) * count);
					if (!char_elem_result) {
						ESP_LOGE(GATTC_TAG, "gattc no mem");
						break;
					} else {
						status = esp_ble_gattc_get_char_by_uuid(gattc_if,
							p_data->search_cmpl.conn_id,
							gl_profile_tab[PROFILE_A_APP_ID].service_start_handle,
							gl_profile_tab[PROFILE_A_APP_ID].service_end_handle,
							temperature_char_uuid,
							char_elem_result,
							&count);
						if (status != ESP_GATT_OK) {
							ESP_LOGE(GATTC_TAG, "esp_ble_gattc_get_char_by_uuid error");
							free(char_elem_result);
							char_elem_result = NULL;
							break;
						}
						if (count > 0) {
							gl_profile_tab[PROFILE_A_APP_ID].char_handle = char_elem_result[0].char_handle;
							esp_ble_gattc_register_for_notify(gattc_if, gl_profile_tab[PROFILE_A_APP_ID].remote_bda, char_elem_result[0].char_handle);
						}
						free(char_elem_result);
					}
				} else {
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
		{
			ESP_LOGI(GATTC_TAG, "Unhandled event %d", event);
			break;
		}
    }
}

void BluetoothManager::attach(IObserver* observer) {
    list_observer.push_back(observer);
}

void BluetoothManager::detach(IObserver* observer) {
    list_observer.remove(observer);
}

void BluetoothManager::notify() {
    for (IObserver* observer : list_observer) {
        observer->update();  // Asumiendo que `update` es el método de notificación en `IObserver`
    }
}
