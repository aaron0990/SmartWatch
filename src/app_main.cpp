/*
 * SPDX-FileCopyrightText: 2021-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include <driver/i2c.h>
#include "esp_err.h"
#include "esp_lcd_gc9a01.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "FitnessActivity.h"
#include "FitnessActivityController.h"
#include "FitnessActivityView.h"
#include "LCDManager.h"
#include "MainView.h"
#include "NavigationController.h"
#include "Notification.h"
#include "NotificationController.h"
#include "NotificationView.h"
#include "Time.h"
#include "TimeController.h"
#include "Weather.h"
#include "WeatherController.h"
#include "WeatherView.h"

static const char *TAG = "example";


extern "C" void app_main(void)
{

    ESP_LOGI(TAG, "Display LVGL Meter Widget");
    // Lock the mutex due to the LVGL APIs are not thread-safe
    LCDManager lcdManager;


    auto navigationController = std::make_shared<NavigationController>();

    auto timeController = std::make_shared<TimeController>(navigationController);
    auto fitnessActivityController = std::make_shared<FitnessActivityController>(navigationController);
    auto notificationController = std::make_shared<NotificationController>(navigationController);
    auto weatherController = std::make_shared<WeatherController>(navigationController);

    navigationController->addController(timeController);
	navigationController->addController(fitnessActivityController);
	navigationController->addController(notificationController);
	navigationController->addController(weatherController);

	auto mainView = std::make_shared<MainView>(timeController);
	auto notificationView = std::make_shared<NotificationView>(notificationController);
	auto weatherView = std::make_shared<WeatherView>(weatherController);
	auto fitnessActivityView = std::make_shared<FitnessActivityView>(fitnessActivityController);

	timeController->setView(mainView);
	notificationController->setView(notificationView);
	weatherController->setView(weatherView);
	fitnessActivityController->setView(fitnessActivityView);

	auto time = std::make_shared<Time>();
	auto fitnessActivity = std::make_shared<FitnessActivity>();
	auto weather = std::make_shared<Weather>();
	auto notification = std::make_shared<Notification>();

	timeController->setTime(time);
	fitnessActivityController->setFitnessActivity(fitnessActivity);
	weatherController->setWeather(weather);
	notificationController->setNotification(notification);

    timeController->initView();

    uint32_t task_delay_ms = 500;
	while (1) {
		// Lock the mutex due to the LVGL APIs are not thread-safe
		if (LCDManager::lvgl_lock(-1)) {
			task_delay_ms = lv_timer_handler();

			// Release the mutex
			LCDManager::lvgl_unlock();
		}
		if (task_delay_ms > 500) {
			task_delay_ms = 500;
		} else if (task_delay_ms < 1) {
			task_delay_ms = 1;
		}
		vTaskDelay(pdMS_TO_TICKS(task_delay_ms));
	}
}
