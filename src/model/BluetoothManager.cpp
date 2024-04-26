/*
 * BluetoothManager.cpp
 *
 *  Created on: 16 mar 2024
 *      Author: root
 */
#include "BluetoothManager.h"
#include "esp_log.h"

static const char* TAG = "BluetoothManager";

BluetoothManager::BluetoothManager() : gatts_if(ESP_GATT_IF_NONE), app_id(0) {
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_BLE);
    esp_bluedroid_init();
    esp_bluedroid_enable();

    registerApp();
}

BluetoothManager::~BluetoothManager() {
    esp_bluedroid_disable();
    esp_bluedroid_deinit();
    esp_bt_controller_disable();
    esp_bt_controller_deinit();
}

void BluetoothManager::startConnection() {
    _initialize_BLE();
}

void BluetoothManager::stopConnection() {
    _deinitialize_BLE();
}

void BluetoothManager::sendData(const std::string& data) {
    // Example: send data to a specific characteristic
}

void BluetoothManager::attach(IObserver *observer) {
    list_observer.push_back(observer);
}

void BluetoothManager::detach(IObserver *observer) {
    list_observer.remove(observer);
}

void BluetoothManager::notify() {
    for (auto& observer : list_observer) {
        observer->update();
    }
}

void BluetoothManager::registerApp() {
    esp_ble_gatts_register_callback(gattsEventCallback);
    esp_ble_gap_register_callback(gapEventCallback);
    esp_ble_gatts_app_register(0);
}

void BluetoothManager::configureBLEServices() {
    configureServiceClima();
    configureServiceNotificaciones();
}

void BluetoothManager::configureServiceClima() {
    // Define and start the Clima service
}

void BluetoothManager::configureServiceNotificaciones() {
    // Define and start the Notificaciones service
}

void BluetoothManager::gattsEventCallback(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
    switch (event) {
        case ESP_GATTS_REG_EVT:
            ESP_LOGI(TAG, "ESP_GATTS_REG_EVT");
            configureBLEServices();
            break;
        default:
        	break;
        // Handle other events
    }
}

void BluetoothManager::gapEventCallback(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
    switch (event) {
        case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
            // Start advertising
            break;
        default:
        	break;
        // Handle other GAP events
    }
}

void BluetoothManager::_initialize_BLE() {
    ESP_LOGI(TAG, "Initializing BLE...");
    // BLE initialization logic here
}

void BluetoothManager::_deinitialize_BLE() {
    ESP_LOGI(TAG, "Deinitializing BLE...");
    // BLE deinitialization logic here
}
