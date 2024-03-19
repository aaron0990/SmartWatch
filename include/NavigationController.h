/*
 * NavigationController.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_NAVIGATIONCONTROLLER_H_
#define SRC_CONTROLLERS_NAVIGATIONCONTROLLER_H_

#include "IObserver.h"
#include "lvgl.h"

class TimeController;
class FitnessActivityController;
class NotificationController;
class WeatherController;

class NavigationController: public IObserver {
public:
	NavigationController(TimeController &timeController,
			FitnessActivityController &fitnessActivityController,
			NotificationController &notificationController,
			WeatherController &weatherController);
	virtual ~NavigationController();
	void changeScreen(uint8_t view_id, lv_event_code_t event_code, uint8_t direction);
private:
	TimeController &timeController;
	FitnessActivityController &fitnessActivityController;
	NotificationController &notificationController;
	WeatherController &weatherController;
};

#endif /* SRC_CONTROLLERS_NAVIGATIONCONTROLLER_H_ */
