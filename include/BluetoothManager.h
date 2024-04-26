#ifndef SRC_MODEL_BLUETOOTHMANAGER_H_
#define SRC_MODEL_BLUETOOTHMANAGER_H_

#include <list>
#include <string>
#include "ISubject.h"
#include "IObserver.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"
#include "esp_bt.h"

/**
 * AL final, he decidido que el smartwatch implemente un GATT Server. Entonces, los datos del giroscopio y del acelerómetro
 * se enviarán a través de BLE en un servicio. Pero para el caso de otros datos como el clima y las notificaciones,
 * se expondrán en servicio que serán de escritura por parte del cliente y que el smartwatch capturará.
 * Así, podremos leer info del tiempo, notificaciones, etc. desde el móvil al smartwatch.
 */

#define GATTS_SERVICE_UUID_CLIMA       0x00FF
#define GATTS_CHAR_UUID_TEMPERATURA    0xFF01
#define GATTS_CHAR_UUID_HUMEDAD        0xFF02
#define GATTS_CHAR_UUID_CALIDAD_AIRE   0xFF03

#define GATTS_SERVICE_UUID_NOTIFICACIONES  0x0100
#define GATTS_CHAR_UUID_WHATSAPP           0x1001
#define GATTS_CHAR_UUID_GOOGLE_TASKS       0x1002
#define GATTS_CHAR_UUID_EVENTOS            0x1003

class BluetoothManager : public ISubject {
public:
    BluetoothManager();
    virtual ~BluetoothManager();

    void startConnection();
    void stopConnection();
    void sendData(const std::string& data);

    void attach(IObserver *observer) override;
    void detach(IObserver *observer) override;
    void notify() override;

    // Métodos para configurar y manejar los servicios BLE
    void configureBLEServices();
    void configureServiceClima();
    void configureServiceNotificaciones();

private:
    std::list<IObserver *> list_observer;

    // Identificadores de interfaz GATT
    esp_gatt_if_t gatts_if;
    uint16_t app_id;

    // Métodos para gestionar específicamente la conexión BLE y la transmisión de datos
    void _initialize_BLE();
    void _deinitialize_BLE();

    static void gattsEventCallback(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);
    static void gapEventCallback(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
};

#endif /* SRC_MODEL_BLUETOOTHMANAGER_H_ */
