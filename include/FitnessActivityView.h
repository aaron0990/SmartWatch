/*
 * FitnessActivityView.h
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#ifndef SRC_FITNESSACTIVITYVIEW_H_
#define SRC_FITNESSACTIVITYVIEW_H_

#include "View.h"

class FitnessActivityController;

class FitnessActivityView: public View {
public:
	FitnessActivityView(std::shared_ptr<FitnessActivityController> fitnessActivityController);
	virtual ~FitnessActivityView();
	void initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay) override;
	void initView() override;
	static void initViewWrapper();

private:
	std::shared_ptr<FitnessActivityController> fitnessActivityController;
	lv_obj_t * ui_FitnessActivityView;
	lv_obj_t * ui_stepsStrLabel;
	lv_obj_t * ui_stepsLabel;
};

#endif /* SRC_FITNESSACTIVITYVIEW_H_ */
