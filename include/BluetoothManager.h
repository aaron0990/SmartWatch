/*
 * BluetoothManager.h
 *
 *  Created on: 16 mar 2024
 *      Author: root
 */

#ifndef SRC_MODEL_BLUETOOTHMANAGER_H_
#define SRC_MODEL_BLUETOOTHMANAGER_H_

#include "ISubject.h"

class BluetoothManager: public ISubject {
public:
	BluetoothManager();
	virtual ~BluetoothManager();
};

#endif /* SRC_MODEL_BLUETOOTHMANAGER_H_ */
