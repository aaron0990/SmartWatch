/*
 * WeatherController.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "WeatherController.h"

WeatherController::WeatherController(NavigationController &navCtrlr,
		WeatherView &weatherView) : navigationController(navCtrlr), weatherView(weatherView)
{
	// TODO Auto-generated constructor stub

}

void WeatherController::initScreenWithAnim(lv_scr_load_anim_t anim_type,
		uint32_t time, uint32_t delay)
{
	weatherView.initScreenWithAnim(anim_type, time, delay);
}

WeatherController::~WeatherController() {
	// TODO Auto-generated destructor stub
}

