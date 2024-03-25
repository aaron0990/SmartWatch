/*
 * NavigationController.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include <esp_log.h>
#include "NavigationController.h"
#include "FitnessActivityController.h"
#include "NotificationController.h"
#include "TimeController.h"
#include "WeatherController.h"


void NavigationController::changeScreen(ViewID view_id, lv_event_code_t event_code, uint8_t direction)
{
	//TODO: missing to handle Google Tasks view
	if (view_id == ViewID::MAIN_VIEW)
	{
		if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_LEFT)
		{ 	//Move to FitnessActivityView
			ctrl_map[ControllerID::ACTIVITY_CTRLR]->initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 0);
		}
		else if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_RIGHT)
		{ 	//Move to NotificationView
			ctrl_map[ControllerID::NOTIFICATION_CTRLR]->initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0);
		}
		else if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_TOP)
		{ 	//Move to TasksView
			//notificationController.initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 0);
		}
		else if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_BOTTOM)
		{ 	//Move to WeatherView
			ctrl_map[ControllerID::WEATHER_CTRLR]->initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 0);
		}
	}
	else if (view_id == ViewID::ACTIVITY_VIEW)
	{
		if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_RIGHT)
		{ //Move to MainView
			ESP_LOGI("NavigationController", "changeScreen->ACTIVITY_VIEW->MAIN_VIEW");
			ctrl_map[ControllerID::TIME_CTRLR]->initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0);
		}
	}
	else if (view_id == ViewID::NOTIFICATION_VIEW)
	{
		if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_LEFT)
		{ //Move to MainView
			ctrl_map[ControllerID::TIME_CTRLR]->initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 0);
		}
	}
	else if (view_id == ViewID::WEATHER_VIEW)
	{
		if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_TOP)
		{ //Move to MainView
			ctrl_map[ControllerID::TIME_CTRLR]->initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 0);
		}
	}

}

void NavigationController::addController(std::shared_ptr<Controller> controller)
{
	ctrl_map[controller->getControllerID()] = controller;
}
