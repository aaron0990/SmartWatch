/*
 * WeatherController.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_WEATHERCONTROLLER_H_
#define SRC_CONTROLLERS_WEATHERCONTROLLER_H_

#include "Controller.h"
#include "WeatherView.h"
#include "NavigationController.h"

class WeatherController: public Controller {
public:
	WeatherController(std::shared_ptr<NavigationController> navigationController);
	virtual ~WeatherController();
private:

};

#endif /* SRC_CONTROLLERS_WEATHERCONTROLLER_H_ */
