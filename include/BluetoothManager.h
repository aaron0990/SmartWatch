#ifndef SRC_MODEL_BLUETOOTHMANAGER_H_
#define SRC_MODEL_BLUETOOTHMANAGER_H_

#include <list>
#include <string>
#include "ISubject.h"
#include "IObserver.h"
#include "esp_gap_ble_api.h"
#include "esp_gattc_api.h"
#include "esp_bt_main.h"
#include "esp_bt.h"
#include "esp_gatt_defs.h"

constexpr uint8_t PROFILE_NUM = 1;
constexpr uint16_t PROFILE_A_APP_ID = 0;
constexpr uint16_t INVALID_HANDLE = 0;

struct gattc_profile_inst {
        esp_gattc_cb_t gattc_cb;
        uint16_t gattc_if;
        uint16_t app_id;
        uint16_t conn_id;
        uint16_t service_start_handle;
        uint16_t service_end_handle;
        uint16_t char_handle;
        esp_bd_addr_t remote_bda;
};

class BluetoothManager : public ISubject {

public:
    BluetoothManager();
    ~BluetoothManager();

    void attach(IObserver *observer) override;
    void detach(IObserver *observer) override;
    void notify() override;

    void initialize();
    void startScan();
    void stopScan();

private:
    static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
    static void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);
    static void gattc_profile_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);

    void initialize_bluetooth_controller();
    void initialize_bluedroid();

    std::list<IObserver *> list_observer;

    static std::string remote_device_name;
    static bool connect;
    static bool get_server;
    static esp_gattc_char_elem_t *char_elem_result;
    static esp_gattc_descr_elem_t *descr_elem_result;

    static esp_bt_uuid_t weather_service_uuid;
	static esp_bt_uuid_t temperature_char_uuid;
	static esp_bt_uuid_t humidity_char_uuid;
	static esp_bt_uuid_t air_quality_char_uuid;
	static esp_bt_uuid_t weather_condition_char_uuid;

	static esp_bt_uuid_t notifications_service_uuid;
	static esp_bt_uuid_t notifications_char_uuid;

	static esp_bt_uuid_t tasks_service_uuid;
	static esp_bt_uuid_t tasks_char_uuid;

    static esp_ble_scan_params_t ble_scan_params;

    static struct gattc_profile_inst gl_profile_tab[PROFILE_NUM];
};

#endif /* SRC_MODEL_BLUETOOTHMANAGER_H_ */
