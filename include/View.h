/*
 * View.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_VIEW_H_
#define SRC_VIEW_H_

#include "IObserver.h"
#include "ui_themes.h"
#include "lvgl.h"
#include "ui_helpers.h"

LV_FONT_DECLARE(ui_font_QuantifyFont_16)
LV_FONT_DECLARE(ui_font_QuantifyFont_70)

enum view_id {
	MAIN_VIEW = 0,
	ACTIVITY_VIEW,
	WEATHER_VIEW,
	NOTIFICATION_VIEW
};

class View: public IObserver {
public:
	View(uint8_t view_id);
	uint8_t get_view_id();
	virtual void initView() = 0;
	virtual ~View();
private:
	uint8_t view_id;
};

#endif /* SRC_VIEW_H_ */
