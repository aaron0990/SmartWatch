/*
 * WeatherView.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "WeatherView.h"

WeatherView::WeatherView(std::shared_ptr<WeatherController> weatherController) :
		View(ViewID::WEATHER_VIEW), weatherController(weatherController)
{
	//initialize member variables

}

void WeatherView::initScreenWithAnim(lv_scr_load_anim_t anim_type,
		uint32_t time, uint32_t delay)
{/*
	if (!ui_MainView)
		initView();
	lv_scr_load_anim(ui_MainView, anim_type, time, delay, false); */
}

WeatherView::~WeatherView() {
	// TODO Auto-generated destructor stub
}

void WeatherView::initView()
{
}
