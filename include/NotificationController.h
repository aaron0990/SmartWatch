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
#include "Notification.h"
#include "NotificationView.h"

class NotificationController: public Controller {
public:
	NotificationController(std::shared_ptr<NavigationController> navigationController);
	virtual ~NotificationController();
	void setNotification(const std::shared_ptr<Notification> &notification);

private:
	std::shared_ptr<Notification> notification;

};

#endif /* SRC_CONTROLLERS_NOTIFICATIONCONTROLLER_H_ */
