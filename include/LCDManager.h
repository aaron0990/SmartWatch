/*
 * LCDManager.h
 *
 *  Created on: 20 mar 2024
 *      Author: root
 */

#ifndef SRC_MODEL_LCDMANAGER_H_
#define SRC_MODEL_LCDMANAGER_H_

#include <stdio.h>

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_lcd_gc9a01.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_touch.h"
#include "esp_lcd_touch_cst816s.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "lvgl.h"

class LCDManager {
public:
	LCDManager();
	virtual ~LCDManager();
	static void init();
	static void lvgl_port_update_callback(lv_disp_drv_t *drv);
	static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx);
	static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map);
	static void lvgl_touch_cb(lv_indev_drv_t *drv, lv_indev_data_t *data);
	static void lvgl_increase_tick(void *arg);
	static bool lvgl_lock(int timeout_ms);
	static void lvgl_unlock(void);
private:
	static constexpr spi_host_device_t LCD_HOST = SPI2_HOST;
	static constexpr int LCD_PIXEL_CLOCK_HZ     = 20 * 1000 * 1000;
	static constexpr int LCD_BK_LIGHT_ON_LEVEL  = 1;
	static constexpr int LCD_BK_LIGHT_OFF_LEVEL = !LCD_BK_LIGHT_ON_LEVEL;

	static constexpr int PIN_NUM_SCLK           = 10;
	static constexpr int PIN_NUM_MOSI           = 11;
	static constexpr int PIN_NUM_MISO           = 12;
	static constexpr int PIN_NUM_LCD_DC         = 8;
	static constexpr int PIN_NUM_LCD_RST        = 14;
	static constexpr int PIN_NUM_LCD_CS         = 9;
	static constexpr int PIN_NUM_BK_LIGHT       = 2;
	static constexpr int PIN_NUM_TOUCH_INT      = 5;
	static constexpr int PIN_NUM_TOUCH_RST      = 13;
	static constexpr int PIN_NUM_I2C1_SDA      	= 6;
	static constexpr int PIN_NUM_I2C1_SCL      	= 7;

	static constexpr int LCD_H_RES              = 240;
	static constexpr int LCD_V_RES              = 240;
	static constexpr int LCD_CMD_BITS           = 8;
	static constexpr int LCD_PARAM_BITS         = 8;

	static constexpr int LVGL_TICK_PERIOD_MS    = 2;
	static constexpr int LVGL_TASK_MAX_DELAY_MS = 500;
	static constexpr int LVGL_TASK_MIN_DELAY_MS = 1;
	static constexpr int LVGL_TASK_STACK_SIZE   = (4 * 1024);
	static constexpr int LVGL_TASK_PRIORITY     = 2;

	gpio_config_t bk_gpio_config;		// Backlight GPIO pin configuration
	static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
	static lv_disp_drv_t disp_drv;      // contains callback functions
	static esp_lcd_touch_handle_t tp;
	static SemaphoreHandle_t lvgl_mux;
};

#endif /* SRC_MODEL_LCDMANAGER_H_ */
