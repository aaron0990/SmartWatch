/*
 * NotificationView.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "NotificationView.h"

NotificationView::NotificationView(std::shared_ptr<NotificationController> notifCtrl) : View(ViewID::NOTIFICATION_VIEW), notificationController(notifCtrl)
{

}


void NotificationView::initScreenWithAnim(lv_scr_load_anim_t anim_type,
		uint32_t time, uint32_t delay)
{
	/*if (!ui_MainView)
		initView();
	lv_scr_load_anim(ui_MainView, anim_type, time, delay, false);*/

}

NotificationView::~NotificationView() {
	// TODO Auto-generated destructor stub
}

void NotificationView::initView()
{
}
