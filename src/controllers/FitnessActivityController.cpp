/*
 * FitnessActivityController.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include <esp_log.h>
#include "FitnessActivityController.h"

FitnessActivityController::FitnessActivityController(
		std::shared_ptr<NavigationController> navigationController): Controller(ControllerID::ACTIVITY_CTRLR, navigationController)
{

}

FitnessActivityController::~FitnessActivityController() {
	// TODO Auto-generated destructor stub
}

void FitnessActivityController::event_FitnessActivityView(lv_event_t *e) {
	lv_event_code_t event_code = lv_event_get_code(e);
	lv_obj_t *target = lv_event_get_target(e);
	if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
	{
		ESP_LOGI("FitnessActivityController", "event_FitnessActivityView");
		lv_indev_wait_release(lv_indev_get_act());
		navigationController->changeScreen(view->getViewID(),
				LV_EVENT_GESTURE, LV_DIR_RIGHT);
	}
}


void FitnessActivityController::event_FitnessActivityView_wrapper(
		lv_event_t *e) {
	FitnessActivityController *fitnessActivityController =
			reinterpret_cast<FitnessActivityController*>(e->user_data);
	fitnessActivityController->event_FitnessActivityView(e);
}
