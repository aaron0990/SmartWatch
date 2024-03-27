/*
 * FitnessActivityController.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_FITNESSACTIVITYCONTROLLER_H_
#define SRC_CONTROLLERS_FITNESSACTIVITYCONTROLLER_H_

#include "lvgl.h"
#include "Controller.h"
#include "FitnessActivity.h"
#include "FitnessActivityView.h"
#include "NavigationController.h"


class FitnessActivityController: public Controller {
public:
	FitnessActivityController(std::shared_ptr<NavigationController> navigationController);
	virtual ~FitnessActivityController();
	void event_FitnessActivityView(lv_event_t *e);
	void setFitnessActivity(const std::shared_ptr<FitnessActivity> &fitnessActivity);
	static void event_FitnessActivityView_wrapper(lv_event_t *e);
private:
	std::shared_ptr<FitnessActivity> fitnessActivity;

};

#endif /* SRC_CONTROLLERS_FITNESSACTIVITYCONTROLLER_H_ */
