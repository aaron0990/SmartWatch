/*
 * TimeController.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_TIMECONTROLLER_H_
#define SRC_CONTROLLERS_TIMECONTROLLER_H_

#include "Controller.h"
#include "NavigationController.h"
#include "lvgl.h"
#include "MainView.h"

class TimeController: public Controller {
public:
	TimeController(std::shared_ptr<NavigationController> navCtrl);
	virtual ~TimeController();
	static void event_MainView_wrapper(lv_event_t* e);
	void event_MainView(lv_event_t* e);
private:

};

#endif /* SRC_CONTROLLERS_TIMECONTROLLER_H_ */
