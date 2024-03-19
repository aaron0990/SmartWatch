/*
 * NotificationController.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "NotificationController.h"
#include "NotificationView.h"


NotificationController::NotificationController(NavigationController &navCtrlr,
		NotificationView &notificationView) : notificationView(notificationView), navigationController(navCtrlr) {
	// TODO Auto-generated constructor stub

}

void NotificationController::initScreenWithAnim(lv_scr_load_anim_t anim_type,
		uint32_t time, uint32_t delay) {
	notificationView.initScreenWithAnim(anim_type, time, delay);
}

NotificationController::~NotificationController() {
	// TODO Auto-generated destructor stub
}
