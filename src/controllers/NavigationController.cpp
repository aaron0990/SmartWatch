/*
 * NavigationController.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "NavigationController.h"
#include "FitnessActivityController.h"
#include "NotificationController.h"
#include "TimeController.h"
#include "WeatherController.h"

NavigationController::~NavigationController() {
	// TODO Auto-generated destructor stub
}

NavigationController::NavigationController(TimeController &timeController,
		FitnessActivityController &fitnessActivityController,
		NotificationController &notificationController,
		WeatherController &weatherController) :
		timeController(timeController), fitnessActivityController(fitnessActivityController),
		notificationController(notificationController), weatherController(weatherController)
{

}

void NavigationController::changeScreen(uint8_t view_id, lv_event_code_t event_code, uint8_t direction)
{
	//TODO: missing to handle Google Tasks view
	if (view_id == MAIN_VIEW)
	{
		if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_LEFT)
		{ 	//Move to FitnessActivityView
			fitnessActivityController.initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 0);
		}
		else if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_RIGHT)
		{ 	//Move to FitnessActivityView
			notificationController.initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0);
		}
		else if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_TOP)
		{ 	//Move to TasksView
			//notificationController.initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 0);
		}
		else if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_BOTTOM)
		{ 	//Move to WeatherView
			weatherController.initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 100, 0);
		}
	}
	else if (view_id == ACTIVITY_VIEW)
	{
		if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_RIGHT)
		{ //Move to MainView
			timeController.initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0);
		}
	}
	else if (view_id == NOTIFICATION_VIEW)
	{
		if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_LEFT)
		{ //Move to MainView
			timeController.initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_LEFT, 100, 0);
		}
	}
	else if (view_id == WEATHER_VIEW)
	{
		if (event_code == LV_EVENT_GESTURE && direction == LV_DIR_TOP)
		{ //Move to MainView
			timeController.initScreenWithAnim(LV_SCR_LOAD_ANIM_MOVE_TOP, 100, 0);
		}
	}

}
