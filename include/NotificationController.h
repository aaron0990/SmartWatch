/*
 * NotificationController.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_NOTIFICATIONCONTROLLER_H_
#define SRC_CONTROLLERS_NOTIFICATIONCONTROLLER_H_

#include "IObserver.h"
#include "NavigationController.h"

class NotificationView;

class NotificationController: public IObserver {
public:
	NotificationController(NavigationController &navCtrlr,
			NotificationView &notificationView);
	virtual ~NotificationController();
	void initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay);

private:
	NotificationView& notificationView;
	NavigationController& navigationController;

};

#endif /* SRC_CONTROLLERS_NOTIFICATIONCONTROLLER_H_ */
