# SmartWatch
DIY smartwatch project using ESP32. Focused on customization and smart features.

# Hardware used

- ESP32-S3-Touch-LCD-1.28: https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-1.28

# Software used

- Eclipse IDE (with Espressif plugin)
- ESP-IDF v5.2
- SquareLine Studio v1.4.0 (for UI design)
- LVGL Simulator for PC as an Eclipse project (used to test designed UI): https://github.com/SquareLineStudio/board_sim_sdl_eclipse/tree/v1.0.2
- LVGL v8.3.11

# Implementation workflow

- UI design with SquareLine Studio.
- Generate the UI files (.c and .h) in SquareLine Studio.
- Add the generated UI files to the LVGL Simulator to test the UI

Sure, here is the information in English:

## BLE Services and Characteristics Schema

### Weather Information Service
- **Service UUID:** `0000aaaa-0000-1000-8000-00805f9b34fb`
- **Characteristics:**
  - **Temperature**
    - **UUID:** `0000aaa1-0000-1000-8000-00805f9b34fb`
    - **Format:** `int16_t` (degrees Celsius multiplied by 100)
    - **Properties:** Read
  - **Humidity**
    - **UUID:** `0000aaa2-0000-1000-8000-00805f9b34fb`
    - **Format:** `uint8_t` (percentage)
    - **Properties:** Read
  - **Air Quality**
    - **UUID:** `0000aaa3-0000-1000-8000-00805f9b34fb`
    - **Format:** `uint16_t` (index)
    - **Properties:** Read
  - **Weather Condition**
    - **UUID:** `0000aaa4-0000-1000-8000-00805f9b34fb`
    - **Format:** `string` (e.g., "sunny", "cloudy", "rainy")
    - **Properties:** Read

### Notifications Service
- **Service UUID:** `0000bbbb-0000-1000-8000-00805f9b34fb`
- **Characteristics:**
  - **Notifications**
    - **UUID:** `0000bbb0-0000-1000-8000-00805f9b34fb`
    - **Format:** JSON encapsulated in a byte string
    - **Properties:** Read

### Google Tasks Service
- **Service UUID:** `0000cccc-0000-1000-8000-00805f9b34fb`
- **Characteristics:**
  - **Tasks**
    - **UUID:** `0000ccc1-0000-1000-8000-00805f9b34fb`
    - **Format:** JSON encapsulated in a byte string
    - **Properties:** Read, Write

## JSON Example

### JSON for Notifications
```json
{
  "notifications": [
    {
      "app": "Gmail",
      "message": "New email from Juan",
      "timestamp": "2024-05-18T10:15:30Z"
    },
    {
      "app": "WhatsApp",
      "message": "New message from María",
      "timestamp": "2024-05-18T10:16:00Z"
    }
  ]
}
```

### JSON for Google Tasks
```json
{
  "tasks": [
    {
      "description": "Team meeting",
      "time": "2024-05-18T14:00:00Z"
    },
    {
      "description": "Buy groceries",
      "time": "2024-05-18T17:30:00Z"
    }
  ]
}
```

## Summary

- **Weather Service:** Includes characteristics for temperature, humidity, air quality, and weather condition (sunny, cloudy, rainy, etc.).
- **Notifications Service:** Uses a single characteristic that encapsulates notifications in JSON format.
- **Google Tasks Service:** Uses JSON to encapsulate both the task description and the time it needs to be performed.

This updated schema allows for the transmission of a comprehensive range of weather and task information, leveraging the flexibility of the JSON format to efficiently structure complex data.