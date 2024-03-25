/*
 * LCDManager.cpp
 *
 *  Created on: 20 mar 2024
 *      Author: root
 */

#include <driver/i2c.h>
#include "LCDManager.h"

static const char* TAG = "LCDManager";

lv_disp_draw_buf_t LCDManager::disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
lv_disp_drv_t LCDManager::disp_drv;      // contains callback functions
esp_lcd_touch_handle_t LCDManager::tp;
SemaphoreHandle_t LCDManager::lvgl_mux = nullptr;


LCDManager::LCDManager()
{	// TODO Auto-generated constructor stub
	init();
}

void LCDManager::lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
	esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
	int offsetx1 = area->x1;
	int offsetx2 = area->x2;
	int offsety1 = area->y1;
	int offsety2 = area->y2;
	// copy a buffer's content to a specific area of the display
	esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}

bool LCDManager::notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io,
		esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
	lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
	lv_disp_flush_ready(disp_driver);
	return false;
}

void LCDManager::lvgl_port_update_callback(lv_disp_drv_t *drv)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;

    switch (drv->rotated) {
    case LV_DISP_ROT_NONE:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, true, false);
        // Rotate LCD touch
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
        break;
    case LV_DISP_ROT_90:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, true, true);
        // Rotate LCD touch
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
        break;
    case LV_DISP_ROT_180:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, false, true);
        // Rotate LCD touch
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
        break;
    case LV_DISP_ROT_270:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, false, false);
        // Rotate LCD touch
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
        break;
    }
}
LCDManager::~LCDManager() {
	// TODO Auto-generated destructor stub
}

void LCDManager::lvgl_touch_cb(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
	uint16_t touchpad_x[1] = {0};
    uint16_t touchpad_y[1] = {0};
    uint8_t touchpad_cnt = 0;

    /* Read touch controller data */
    esp_lcd_touch_read_data(reinterpret_cast<esp_lcd_touch_handle_t>(drv->user_data));

    /* Get coordinates */
    bool touchpad_pressed = esp_lcd_touch_get_coordinates(reinterpret_cast<esp_lcd_touch_handle_t>(drv->user_data), touchpad_x, touchpad_y, NULL, &touchpad_cnt, 1);

    if (touchpad_pressed && touchpad_cnt > 0) {
        data->point.x = touchpad_x[0];
        data->point.y = touchpad_y[0];
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void LCDManager::init()
{
	ESP_LOGI(TAG, "Turn off LCD backlight");
	gpio_config_t bk_gpio_config = {
		.pin_bit_mask = 1ULL << PIN_NUM_BK_LIGHT,
		.mode = GPIO_MODE_OUTPUT,
	};
	ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));

	ESP_LOGI(TAG, "Initialize SPI bus");
	spi_bus_config_t buscfg = {
		.mosi_io_num = PIN_NUM_MOSI,
		.miso_io_num = PIN_NUM_MISO,
		.sclk_io_num = PIN_NUM_SCLK,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1,
		.max_transfer_sz = LCD_H_RES * 80 * sizeof(uint16_t),
	};
	ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

	ESP_LOGI(TAG, "Install panel IO");
	esp_lcd_panel_io_handle_t io_handle = NULL;
	esp_lcd_panel_io_spi_config_t io_config = {
		.cs_gpio_num = PIN_NUM_LCD_CS,
		.dc_gpio_num = PIN_NUM_LCD_DC,
		.spi_mode = 0,
		.pclk_hz = LCD_PIXEL_CLOCK_HZ,
		.trans_queue_depth = 10,
		.on_color_trans_done = LCDManager::notify_lvgl_flush_ready,
		.user_ctx = &LCDManager::disp_drv,
		.lcd_cmd_bits = LCD_CMD_BITS,
		.lcd_param_bits = LCD_PARAM_BITS,
	};
	// Attach the LCD to the SPI bus
	ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

	esp_lcd_panel_handle_t panel_handle = NULL;
	esp_lcd_panel_dev_config_t panel_config = {
		.reset_gpio_num = PIN_NUM_LCD_RST,
		.rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
		.bits_per_pixel = 16,
	};

	ESP_LOGI(TAG, "Install GC9A01 panel driver");
	ESP_ERROR_CHECK(esp_lcd_new_panel_gc9a01(io_handle, &panel_config, &panel_handle));

	ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
	ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
	ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));
	ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, true, false));

	// user can flush pre-defined pattern to the screen before we turn on the screen or backlight
	ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));


	//***************************** TOUCH SETTING *************************************************************//

	i2c_config_t i2c_conf = {
		.mode = I2C_MODE_MASTER,
		.sda_io_num = PIN_NUM_I2C1_SDA,
		.scl_io_num = PIN_NUM_I2C1_SCL,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		.master =
		{
			.clk_speed = 400 * 1000,
		},
	};

	ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_1, &i2c_conf));
	ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_1, I2C_MODE_MASTER, 0, 0, 0));

	esp_lcd_panel_io_handle_t tp_io_handle = nullptr;
	esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_CST816S_CONFIG();
	// Attach the TOUCH to the I2C bus
	ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c_v1((esp_lcd_i2c_bus_handle_t)I2C_NUM_1, &tp_io_config, &tp_io_handle));

	esp_lcd_touch_config_t tp_cfg = {
		.x_max = LCD_H_RES,
		.y_max = LCD_V_RES,
		.rst_gpio_num = static_cast<gpio_num_t>(-1),
		.int_gpio_num = static_cast<gpio_num_t>(-1),
		.flags = {
			.swap_xy = 0,
			.mirror_x = 0,
			.mirror_y = 0,
		},
	};

	ESP_LOGI(TAG, "Install CST816S touch driver");
	ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_cst816s(tp_io_handle, &tp_cfg, &tp));

	//***************************** TOUCH SETTING *************************************************************//

	ESP_LOGI(TAG, "Turn ON LCD backlight");
	gpio_set_level(static_cast<gpio_num_t>(PIN_NUM_BK_LIGHT), LCD_BK_LIGHT_ON_LEVEL);


	ESP_LOGI(TAG, "Initialize LVGL library");
	lv_init();
	// alloc draw buffers used by LVGL
	// it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
	lv_color_t *buf1 = reinterpret_cast<lv_color_t *>(heap_caps_malloc(LCD_H_RES * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA));
	assert(buf1);
	lv_color_t *buf2 = reinterpret_cast<lv_color_t *>(heap_caps_malloc(LCD_H_RES * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA));
	assert(buf2);
	// initialize LVGL draw buffers
	lv_disp_draw_buf_init(&LCDManager::disp_buf, buf1, buf2, LCD_H_RES * 20);

	ESP_LOGI(TAG, "Register display driver to LVGL");
	lv_disp_drv_init(&disp_drv);
	disp_drv.hor_res = LCD_H_RES;
	disp_drv.ver_res = LCD_V_RES;
	disp_drv.flush_cb = LCDManager::lvgl_flush_cb;
	disp_drv.drv_update_cb = LCDManager::lvgl_port_update_callback;
	disp_drv.draw_buf = &disp_buf;
	disp_drv.user_data = panel_handle;
	lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

	ESP_LOGI(TAG, "Install LVGL tick timer");
	// Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
	const esp_timer_create_args_t lvgl_tick_timer_args = {
		.callback = &LCDManager::lvgl_increase_tick,
		.name = "lvgl_tick"
	};
	esp_timer_handle_t lvgl_tick_timer = NULL;
	ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
	ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, LVGL_TICK_PERIOD_MS * 1000));

	static lv_indev_drv_t indev_drv;    // Input device driver (Touch)
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.disp = disp;
	indev_drv.read_cb = LCDManager::lvgl_touch_cb;
	indev_drv.user_data = tp;

	lv_indev_drv_register(&indev_drv);

	lvgl_mux = xSemaphoreCreateRecursiveMutex();
	assert(lvgl_mux);
	//ESP_LOGI(TAG, "Create LVGL task");
	//xTaskCreate(LCDManager::lvgl_port_task, "LVGL", LVGL_TASK_STACK_SIZE, nullptr, LVGL_TASK_PRIORITY, nullptr);
}

void LCDManager::lvgl_increase_tick(void *arg)
{
	/* Tell LVGL how many milliseconds has elapsed */
	lv_tick_inc(LVGL_TICK_PERIOD_MS);
}


bool LCDManager::lvgl_lock(int timeout_ms)
{
	// Convert timeout in milliseconds to FreeRTOS ticks
	// If `timeout_ms` is set to -1, the program will block until the condition is met
	const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
	return xSemaphoreTakeRecursive(lvgl_mux, timeout_ticks) == pdTRUE;
}

void LCDManager::lvgl_unlock(void)
{
	 xSemaphoreGiveRecursive(lvgl_mux);
}

