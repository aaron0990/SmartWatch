/*
 * WeatherView.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_WEATHERVIEW_H_
#define SRC_WEATHERVIEW_H_

#include "View.h"

class WeatherController;

class WeatherView: public View {
public:
	WeatherView(std::shared_ptr<WeatherController> weatherController);
	void initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay) override;
	virtual ~WeatherView();
	void initView() override;
private:
	std::shared_ptr<WeatherController> weatherController;
};

#endif /* SRC_WEATHERVIEW_H_ */
