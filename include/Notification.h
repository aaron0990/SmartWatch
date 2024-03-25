/*
 * Notification.h
 *
 *  Created on: 16 mar 2024
 *      Author: root
 */

#ifndef SRC_MODEL_NOTIFICATION_H_
#define SRC_MODEL_NOTIFICATION_H_

#include "ISubject.h"
#include <list>

class Notification : public ISubject{
public:
	Notification();
	virtual ~Notification();
	void notify() override;
	void attach(IObserver *observer) override;
	void detach(IObserver *observer) override;
private:
	std::list<IObserver *> list_observer;
};

#endif /* SRC_MODEL_NOTIFICATION_H_ */
