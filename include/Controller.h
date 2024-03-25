/*
 * Controller.h
 *
 *  Created on: 23 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_CONTROLLER_H_
#define SRC_CONTROLLERS_CONTROLLER_H_

#include <memory>
#include "IObserver.h"
#include "NavigationController.h"
#include "View.h"

enum class ControllerID {
	TIME_CTRLR = 0,
	ACTIVITY_CTRLR,
	WEATHER_CTRLR,
	NOTIFICATION_CTRLR
};

class Controller : public IObserver {
public:
	Controller(ControllerID controller_id, std::shared_ptr<NavigationController> navigationController);
	virtual void initView();
	virtual void setView(std::shared_ptr<View> view);
	virtual void initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay);
	ControllerID getControllerID();
	virtual ~Controller();
protected:
	std::shared_ptr<NavigationController> navigationController;
	std::shared_ptr<View> view;

private:
	ControllerID controller_id;
};

#endif /* SRC_CONTROLLERS_CONTROLLER_H_ */
