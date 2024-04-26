/*
 * BluetoothDataProcess.h
 *
 *  Created on: 31 mar 2024
 *      Author: root
 */

#ifndef SRC_MODEL_BLUETOOTHDATAPROCESS_H_
#define SRC_MODEL_BLUETOOTHDATAPROCESS_H_

#include "IObserver.h"
#include "Time.h"
#include "FitnessActivity.h"
#include "Weather.h"
#include "Notification.h"
#include <memory>
#include <string>
#include "BluetoothManager.h"

class BluetoothDataProcess: public IObserver {
public:
	BluetoothDataProcess(std::shared_ptr<BluetoothManager> bluetoothManager,
			std::shared_ptr<Time> time,
			std::shared_ptr<FitnessActivity> fitnessActivity,
			std::shared_ptr<Weather> weather,
			std::shared_ptr<Notification> notification);
	virtual ~BluetoothDataProcess();
	void update() override;

private:
	std::shared_ptr<BluetoothManager> bluetoothManager; //Subject to subscribe to
	std::shared_ptr<Time> time;
	std::shared_ptr<FitnessActivity> fitnessActivity;
	std::shared_ptr<Weather> weather;
	std::shared_ptr<Notification> notification;



	// Métodos auxiliares para procesar diferentes tipos de datos
	void _process_TimeData(const std::string &data);
	void _process_FitnessActivityData(const std::string &data);
	void _process_WeatherData(const std::string &data);
	void _process_NotificationData(const std::string &data);
};

#endif /* SRC_MODEL_BLUETOOTHDATAPROCESS_H_ */
