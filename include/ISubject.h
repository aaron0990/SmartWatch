/*
 * ISubject.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_ISUBJECT_H_
#define SRC_ISUBJECT_H_

#include "IObserver.h"

class ISubject {
public:
	ISubject();
	virtual void attach(IObserver *observer) = 0;
	virtual void detach(IObserver *observer) = 0;
	virtual void notify() = 0;
	virtual ~ISubject();
};

#endif /* SRC_ISUBJECT_H_ */
