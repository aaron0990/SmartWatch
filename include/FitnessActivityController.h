/*
 * FitnessActivityController.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_FITNESSACTIVITYCONTROLLER_H_
#define SRC_CONTROLLERS_FITNESSACTIVITYCONTROLLER_H_

#include "lvgl.h"
#include "IObserver.h"
#include "FitnessActivityView.h"
#include "NavigationController.h"


class FitnessActivityController: public IObserver {
public:
	FitnessActivityController(NavigationController& navCtrlr, FitnessActivityView& fitnessActivityView);
	virtual ~FitnessActivityController();
	void initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay);
	void event_FitnessActivityView(lv_event_t *e);

	static void event_FitnessActivityView_wrapper(lv_event_t *e);

private:
	NavigationController& navigationController;
	FitnessActivityView& fitnessActivityView;
};

#endif /* SRC_CONTROLLERS_FITNESSACTIVITYCONTROLLER_H_ */
