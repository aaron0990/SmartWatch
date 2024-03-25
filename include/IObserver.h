/*
 * IObserver.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_IOBSERVER_H_
#define SRC_IOBSERVER_H_

class IObserver {
public:
	IObserver();
	virtual void update() = 0;
	virtual ~IObserver();
};

#endif /* SRC_IOBSERVER_H_ */
