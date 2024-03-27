/*
 * WeatherController.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "WeatherController.h"

WeatherController::WeatherController(std::shared_ptr<NavigationController> navigationController) : Controller(ControllerID::WEATHER_CTRLR, navigationController)
{
	// TODO Auto-generated constructor stub

}

WeatherController::~WeatherController() {
	// TODO Auto-generated destructor stub
}

void WeatherController::setWeather(const std::shared_ptr<Weather> &weather) {
	this->weather = weather;
}
