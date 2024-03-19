/*
 * FitnessActivityView.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "FitnessActivityView.h"
#include "FitnessActivityController.h"

FitnessActivityView::FitnessActivityView(FitnessActivityController* fitnessActivityController) : View(ACTIVITY_VIEW), fitnessActivityController(fitnessActivityController)
{
	//initialize member variables
	ui_FitnessActivityView = nullptr;
	ui_stepsStrLabel = nullptr;
	ui_stepsLabel = nullptr;
}

FitnessActivityView::~FitnessActivityView() {
	// TODO Auto-generated destructor stub
}

void FitnessActivityView::initScreenWithAnim(lv_scr_load_anim_t anim_type,
		uint32_t time, uint32_t delay)
{
	if (!ui_FitnessActivityView)
		initView();
    lv_scr_load_anim(ui_FitnessActivityView, anim_type, time, delay, false);

}

void FitnessActivityView::initView()
{
	ui_FitnessActivityView = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_FitnessActivityView, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_flex_flow(ui_FitnessActivityView, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(ui_FitnessActivityView, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	ui_object_set_themeable_style_property(ui_FitnessActivityView, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
										   _ui_theme_color_deep_space);
	ui_object_set_themeable_style_property(ui_FitnessActivityView, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
										   _ui_theme_alpha_deep_space);

	ui_stepsStrLabel = lv_label_create(ui_FitnessActivityView);
	lv_obj_set_width(ui_stepsStrLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_stepsStrLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(ui_stepsStrLabel, 1);
	lv_obj_set_y(ui_stepsStrLabel, -42);
	lv_obj_set_align(ui_stepsStrLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_stepsStrLabel, "Pasos");
	ui_object_set_themeable_style_property(ui_stepsStrLabel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
										   _ui_theme_color_soft_coral);
	ui_object_set_themeable_style_property(ui_stepsStrLabel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
										   _ui_theme_alpha_soft_coral);
	lv_obj_set_style_text_font(ui_stepsStrLabel, &ui_font_QuantifyFont_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_stepsLabel = lv_label_create(ui_FitnessActivityView);
	lv_obj_set_width(ui_stepsLabel, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_stepsLabel, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_stepsLabel, LV_ALIGN_CENTER);
	lv_label_set_text(ui_stepsLabel, "8078");
	ui_object_set_themeable_style_property(ui_stepsLabel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
										   _ui_theme_color_pale_spring);
	ui_object_set_themeable_style_property(ui_stepsLabel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
										   _ui_theme_alpha_pale_spring);
	lv_obj_set_style_text_font(ui_stepsLabel, &ui_font_QuantifyFont_70, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_add_event_cb(ui_FitnessActivityView, fitnessActivityController->event_FitnessActivityView_wrapper, LV_EVENT_ALL, fitnessActivityController);
}
