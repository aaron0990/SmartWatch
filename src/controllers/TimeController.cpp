/*
 * TimeController.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "TimeController.h"
#include "MainView.h"


TimeController::TimeController(NavigationController &navCtrl, MainView& mainView) :
		mainView(mainView), navigationController(navCtrl)
{

}


void TimeController::event_MainView_wrapper(lv_event_t *e) {
	TimeController* timeController = reinterpret_cast<TimeController*>(e->user_data);
	timeController->event_MainView(e);
}

void TimeController::event_MainView(lv_event_t *e) {
	lv_event_code_t event_code = lv_event_get_code(e);
	lv_obj_t * target = lv_event_get_target(e);
	if(event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
	{
		lv_indev_wait_release(lv_indev_get_act());
		navigationController.changeScreen(mainView.get_view_id(), LV_EVENT_GESTURE, LV_DIR_LEFT);
	}
}

void TimeController::initScreenWithAnim(lv_scr_load_anim_t anim_type,
		uint32_t time, uint32_t delay)
{
	mainView.initScreenWithAnim(anim_type, time, delay);
}
