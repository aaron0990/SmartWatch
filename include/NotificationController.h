/*
 * NotificationController.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_NOTIFICATIONCONTROLLER_H_
#define SRC_CONTROLLERS_NOTIFICATIONCONTROLLER_H_

#include "Controller.h"
#include "NavigationController.h"
#include "NotificationView.h"

class NotificationController: public Controller {
public:
	NotificationController(std::shared_ptr<NavigationController> navigationController);
	virtual ~NotificationController();

private:

};

#endif /* SRC_CONTROLLERS_NOTIFICATIONCONTROLLER_H_ */
