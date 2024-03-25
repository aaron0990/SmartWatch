/*
 * BluetoothManager.h
 *
 *  Created on: 16 mar 2024
 *      Author: root
 */

#ifndef SRC_MODEL_BLUETOOTHMANAGER_H_
#define SRC_MODEL_BLUETOOTHMANAGER_H_

#include <list>
#include "ISubject.h"

class BluetoothManager: public ISubject {
public:
	BluetoothManager();
	virtual ~BluetoothManager();
	void notify() override;
	void attach(IObserver *observer) override;
	void detach(IObserver *observer) override;
private:
	std::list<IObserver *> list_observer;

};

#endif /* SRC_MODEL_BLUETOOTHMANAGER_H_ */
