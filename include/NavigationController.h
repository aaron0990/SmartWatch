/*
 * NavigationController.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_NAVIGATIONCONTROLLER_H_
#define SRC_CONTROLLERS_NAVIGATIONCONTROLLER_H_

#include <memory>
#include <map>
#include "IObserver.h"
#include "lvgl.h"
#include "View.h"

class Controller;
enum class ControllerID;

class NavigationController: public IObserver {
public:
	NavigationController() = default;
	virtual ~NavigationController() = default;
	void changeScreen(ViewID view_id, lv_event_code_t event_code, uint8_t direction);
	void addController(std::shared_ptr<Controller> controller);
private:
	std::map<ControllerID, std::shared_ptr<Controller> > ctrl_map;
};

#endif /* SRC_CONTROLLERS_NAVIGATIONCONTROLLER_H_ */
