/*
 * NotificationView.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "NotificationView.h"

NotificationView::NotificationView(NotificationController* notifCtrl) : View(NOTIFICATION_VIEW), notificationController(notifCtrl)
{

}


void NotificationView::initScreenWithAnim(lv_scr_load_anim_t anim_type,
		uint32_t time, uint32_t delay)
{

}

NotificationView::~NotificationView() {
	// TODO Auto-generated destructor stub
}

