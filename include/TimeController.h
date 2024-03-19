/*
 * TimeController.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_TIMECONTROLLER_H_
#define SRC_CONTROLLERS_TIMECONTROLLER_H_

#include "NavigationController.h"
#include "lvgl.h"

class MainView;

class TimeController: public IObserver {
public:
	TimeController(NavigationController& navCtrl, MainView& mainView);
	virtual ~TimeController();
	static void event_MainView_wrapper(lv_event_t* e);
	void event_MainView(lv_event_t* e);
	void initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay);
private:
	MainView& mainView;
	NavigationController& navigationController;
};

#endif /* SRC_CONTROLLERS_TIMECONTROLLER_H_ */
