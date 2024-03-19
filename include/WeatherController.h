/*
 * WeatherController.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_CONTROLLERS_WEATHERCONTROLLER_H_
#define SRC_CONTROLLERS_WEATHERCONTROLLER_H_

#include "IObserver.h"
#include "WeatherView.h"
#include "NavigationController.h"

class WeatherController: public IObserver {
public:
	WeatherController(NavigationController &navCtrlr,
			WeatherView &weatherView);
	void initScreenWithAnim(lv_scr_load_anim_t anim_type,
			uint32_t time, uint32_t delay);
	virtual ~WeatherController();
private:
	NavigationController &navigationController;
	WeatherView &weatherView;
};

#endif /* SRC_CONTROLLERS_WEATHERCONTROLLER_H_ */
