/*
 * WeatherView.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_WEATHERVIEW_H_
#define SRC_WEATHERVIEW_H_

#include "View.h"

class WeatherView: public View {
public:
	WeatherView();
	void initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay);
	virtual ~WeatherView();
};

#endif /* SRC_WEATHERVIEW_H_ */
