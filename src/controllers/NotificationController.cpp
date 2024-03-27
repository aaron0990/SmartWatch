/*
 * NotificationController.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "NotificationController.h"
#include "NotificationView.h"


NotificationController::NotificationController(std::shared_ptr<NavigationController> navigationController) : Controller(ControllerID::NOTIFICATION_CTRLR, navigationController) {
	// TODO Auto-generated constructor stub

}


NotificationController::~NotificationController() {
	// TODO Auto-generated destructor stub
}

void NotificationController::setNotification(const std::shared_ptr<Notification> &notification) {
	this->notification = notification;
}
