/*
 * BluetoothDataProcess.cpp
 *
 *  Created on: 31 mar 2024
 *      Author: root
 */

#include "BluetoothDataProcess.h"

BluetoothDataProcess::BluetoothDataProcess(
		std::shared_ptr<BluetoothManager> bluetoothManager,
		std::shared_ptr<Time> time,
		std::shared_ptr<FitnessActivity> fitnessActivity,
		std::shared_ptr<Weather> weather,
		std::shared_ptr<Notification> notification) :
		bluetoothManager(bluetoothManager), time(time), fitnessActivity(
				fitnessActivity), weather(weather), notification(notification)
{
	bluetoothManager->attach(this);
}

BluetoothDataProcess::~BluetoothDataProcess() {
	// TODO Auto-generated destructor stub
}

void BluetoothDataProcess::update() {
}

void BluetoothDataProcess::_process_TimeData(const std::string &data) {
}

void BluetoothDataProcess::_process_FitnessActivityData(
		const std::string &data) {
}

void BluetoothDataProcess::_process_WeatherData(const std::string &data) {
}

void BluetoothDataProcess::_process_NotificationData(const std::string &data) {
}
