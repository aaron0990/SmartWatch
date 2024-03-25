/*
 * NotificationView.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_NOTIFICATIONVIEW_H_
#define SRC_NOTIFICATIONVIEW_H_

#include "View.h"

class NotificationController;

class NotificationView: public View {
public:
	NotificationView(std::shared_ptr<NotificationController> notifCtrl);
	void initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay) override;
	virtual ~NotificationView();
	void initView() override;

private:
	std::shared_ptr<NotificationController> notificationController;
};

#endif /* SRC_NOTIFICATIONVIEW_H_ */
