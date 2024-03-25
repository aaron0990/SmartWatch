/*
 * MainView.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_MAINVIEW_H_
#define SRC_MAINVIEW_H_

#include "View.h"

LV_IMG_DECLARE(ui_img_BLEIcon)

/*
 * Si se quieren varias vistas alternativas de fecha y hora para tener diseños distintos, se puede usar un patron estrategia y
 * haciendo esta misma clase abstracta y luego hacer subclases con distintos diseños (p.e. MainViewAnalogic, MainViewDigital, etc)
 */
class TimeController;

class MainView: public View {
public:
	MainView(std::shared_ptr<TimeController> timeController);
	void initView() override;
	static void initViewWrapper();
	void initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay) override;
	virtual ~MainView();
private:
	std::shared_ptr<TimeController> timeController;

	lv_obj_t * ui_MainView;
	lv_obj_t * ui_topContainer;
	lv_obj_t * ui_dayLabel;
	lv_obj_t * ui_monthLabel;
	lv_obj_t * ui_midContainer;
	lv_obj_t * ui_batteryBar;
	lv_obj_t * ui_Panel1;
	lv_obj_t * ui_hourLabel;
	lv_obj_t * ui_colonLabel;
	lv_obj_t * ui_minuteLabel;
	lv_obj_t * ui_BLEIcon;
	lv_obj_t * ui_bottomContainer;
	lv_obj_t * ui_dowLabel;
};

#endif /* SRC_MAINVIEW_H_ */
