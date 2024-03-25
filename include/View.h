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
#include <memory>

LV_FONT_DECLARE(ui_font_QuantifyFont_16)
LV_FONT_DECLARE(ui_font_QuantifyFont_70)

enum class ViewID {
	MAIN_VIEW = 0,
	ACTIVITY_VIEW,
	WEATHER_VIEW,
	NOTIFICATION_VIEW
};

class View: public IObserver {
public:
	View(ViewID view_id);
	ViewID getViewID();
	virtual void initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay) = 0;
	virtual void initView() = 0;
	virtual ~View();
	void update() override;

private:
	ViewID view_id;
};

#endif /* SRC_VIEW_H_ */
