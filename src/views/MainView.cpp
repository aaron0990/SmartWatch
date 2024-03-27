/*
 * MainView.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "MainView.h"
#include "TimeController.h"


MainView::MainView(std::shared_ptr<TimeController> timeController) : View(ViewID::MAIN_VIEW), timeController(timeController)
{
	//initialize member variables
	ui_MainView = nullptr;
	ui_topContainer = nullptr;
	ui_dayLabel = nullptr;
	ui_monthLabel = nullptr;
	ui_midContainer = nullptr;
	ui_batteryBar = nullptr;
	ui_Panel1 = nullptr;
	ui_hourLabel = nullptr;
	ui_colonLabel = nullptr;
	ui_minuteLabel = nullptr;
	ui_BLEIcon = nullptr;
	ui_bottomContainer = nullptr;
	ui_dowLabel = nullptr;
}

MainView::~MainView() {
	// TODO Auto-generated destructor stub
}

void MainView::initScreenWithAnim(lv_scr_load_anim_t anim_type,
		uint32_t time, uint32_t delay)
{
	if (!ui_MainView)
		initView();
	lv_scr_load_anim(ui_MainView, anim_type, time, delay, false);
}

void MainView::initView() {
		ui_MainView = lv_obj_create(NULL);
	    lv_obj_clear_flag(ui_MainView, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	    lv_obj_set_flex_flow(ui_MainView, LV_FLEX_FLOW_COLUMN);
	    lv_obj_set_flex_align(ui_MainView, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	    ui_object_set_themeable_style_property(ui_MainView, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
	                                           _ui_theme_color_deep_space);
	    ui_object_set_themeable_style_property(ui_MainView, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
	                                           _ui_theme_alpha_deep_space);
	    lv_obj_set_style_pad_left(ui_MainView, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_pad_right(ui_MainView, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_pad_top(ui_MainView, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_pad_bottom(ui_MainView, 25, LV_PART_MAIN | LV_STATE_DEFAULT);

	    ui_topContainer = lv_obj_create(ui_MainView);
	    lv_obj_remove_style_all(ui_topContainer);
	    lv_obj_set_width(ui_topContainer, lv_pct(70));
	    lv_obj_set_height(ui_topContainer, lv_pct(20));
	    lv_obj_set_align(ui_topContainer, LV_ALIGN_CENTER);
	    lv_obj_set_flex_flow(ui_topContainer, LV_FLEX_FLOW_ROW);
	    lv_obj_set_flex_align(ui_topContainer, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	    lv_obj_clear_flag(ui_topContainer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	    ui_dayLabel = lv_label_create(ui_topContainer);
	    lv_obj_set_width(ui_dayLabel, LV_SIZE_CONTENT);   /// 1
	    lv_obj_set_height(ui_dayLabel, LV_SIZE_CONTENT);    /// 1
	    lv_obj_set_align(ui_dayLabel, LV_ALIGN_CENTER);
	    lv_label_set_text(ui_dayLabel, "30");
	    ui_object_set_themeable_style_property(ui_dayLabel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
	                                           _ui_theme_color_sunset_glow);
	    ui_object_set_themeable_style_property(ui_dayLabel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
	                                           _ui_theme_alpha_sunset_glow);
	    lv_obj_set_style_text_font(ui_dayLabel, &ui_font_QuantifyFont_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	    ui_monthLabel = lv_label_create(ui_topContainer);
	    lv_obj_set_width(ui_monthLabel, LV_SIZE_CONTENT);   /// 1
	    lv_obj_set_height(ui_monthLabel, LV_SIZE_CONTENT);    /// 1
	    lv_obj_set_align(ui_monthLabel, LV_ALIGN_CENTER);
	    lv_label_set_text(ui_monthLabel, "Septiembre");
	    ui_object_set_themeable_style_property(ui_monthLabel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
	                                           _ui_theme_color_sunset_glow);
	    ui_object_set_themeable_style_property(ui_monthLabel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
	                                           _ui_theme_alpha_sunset_glow);
	    lv_obj_set_style_text_font(ui_monthLabel, &ui_font_QuantifyFont_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	    ui_midContainer = lv_obj_create(ui_MainView);
	    lv_obj_remove_style_all(ui_midContainer);
	    lv_obj_set_width(ui_midContainer, lv_pct(100));
	    lv_obj_set_height(ui_midContainer, lv_pct(40));
	    lv_obj_set_align(ui_midContainer, LV_ALIGN_CENTER);
	    lv_obj_set_flex_flow(ui_midContainer, LV_FLEX_FLOW_ROW);
	    lv_obj_set_flex_align(ui_midContainer, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	    lv_obj_clear_flag(ui_midContainer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	    ui_batteryBar = lv_bar_create(ui_midContainer);
	    lv_bar_set_value(ui_batteryBar, 75, LV_ANIM_OFF);
	    lv_bar_set_start_value(ui_batteryBar, 0, LV_ANIM_OFF);
	    lv_obj_set_width(ui_batteryBar, 21);
	    lv_obj_set_height(ui_batteryBar, 10);
	    lv_obj_set_align(ui_batteryBar, LV_ALIGN_CENTER);
	    lv_obj_clear_flag(ui_batteryBar, LV_OBJ_FLAG_CLICK_FOCUSABLE);      /// Flags
	    ui_object_set_themeable_style_property(ui_batteryBar, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
	                                           _ui_theme_color_deep_space);
	    ui_object_set_themeable_style_property(ui_batteryBar, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
	                                           _ui_theme_alpha_deep_space);
	    ui_object_set_themeable_style_property(ui_batteryBar, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
	                                           _ui_theme_color_sunset_glow);
	    ui_object_set_themeable_style_property(ui_batteryBar, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
	                                           _ui_theme_alpha_sunset_glow);
	    lv_obj_set_style_border_width(ui_batteryBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_border_side(ui_batteryBar, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_pad_left(ui_batteryBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_pad_right(ui_batteryBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_pad_top(ui_batteryBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_pad_bottom(ui_batteryBar, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

	    ui_object_set_themeable_style_property(ui_batteryBar, LV_PART_INDICATOR | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
	                                           _ui_theme_color_pale_spring);
	    ui_object_set_themeable_style_property(ui_batteryBar, LV_PART_INDICATOR | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
	                                           _ui_theme_alpha_pale_spring);
	    lv_obj_set_style_border_width(ui_batteryBar, 1, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	    lv_obj_set_style_border_side(ui_batteryBar, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR | LV_STATE_DEFAULT);

	    ui_Panel1 = lv_obj_create(ui_midContainer);
	    lv_obj_set_width(ui_Panel1, lv_pct(73));
	    lv_obj_set_height(ui_Panel1, lv_pct(90));
	    lv_obj_set_x(ui_Panel1, -4);
	    lv_obj_set_y(ui_Panel1, -17);
	    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
	    lv_obj_set_flex_flow(ui_Panel1, LV_FLEX_FLOW_ROW);
	    lv_obj_set_flex_align(ui_Panel1, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	    ui_object_set_themeable_style_property(ui_Panel1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
	                                           _ui_theme_color_electric_rose);
	    ui_object_set_themeable_style_property(ui_Panel1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
	                                           _ui_theme_alpha_electric_rose);
	    lv_obj_set_style_pad_left(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_pad_right(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_pad_top(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_set_style_pad_bottom(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	    ui_object_set_themeable_style_property(ui_Panel1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
	                                           _ui_theme_color_pale_spring);
	    ui_object_set_themeable_style_property(ui_Panel1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
	                                           _ui_theme_alpha_pale_spring);
	    lv_obj_set_style_text_font(ui_Panel1, &ui_font_QuantifyFont_70, LV_PART_MAIN | LV_STATE_DEFAULT);

	    ui_hourLabel = lv_label_create(ui_Panel1);
	    lv_obj_set_width(ui_hourLabel, LV_SIZE_CONTENT);   /// 48
	    lv_obj_set_height(ui_hourLabel, LV_SIZE_CONTENT);    /// 56
	    lv_obj_set_align(ui_hourLabel, LV_ALIGN_CENTER);
	    lv_label_set_text(ui_hourLabel, "09");

	    ui_colonLabel = lv_label_create(ui_Panel1);
	    lv_obj_set_width(ui_colonLabel, LV_SIZE_CONTENT);   /// 9
	    lv_obj_set_height(ui_colonLabel, LV_SIZE_CONTENT);    /// 48
	    lv_obj_set_align(ui_colonLabel, LV_ALIGN_CENTER);
	    lv_label_set_text(ui_colonLabel, ":");

	    ui_minuteLabel = lv_label_create(ui_Panel1);
	    lv_obj_set_width(ui_minuteLabel, LV_SIZE_CONTENT);   /// 1
	    lv_obj_set_height(ui_minuteLabel, LV_SIZE_CONTENT);    /// 50
	    lv_obj_set_align(ui_minuteLabel, LV_ALIGN_CENTER);
	    lv_label_set_text(ui_minuteLabel, "57");

	    ui_BLEIcon = lv_img_create(ui_midContainer);
	    lv_img_set_src(ui_BLEIcon, &ui_img_BLEIcon);
	    lv_obj_set_width(ui_BLEIcon, LV_SIZE_CONTENT);   /// 9
	    lv_obj_set_height(ui_BLEIcon, LV_SIZE_CONTENT);    /// 14
	    lv_obj_set_x(ui_BLEIcon, 15);
	    lv_obj_set_y(ui_BLEIcon, -24);
	    lv_obj_set_align(ui_BLEIcon, LV_ALIGN_CENTER);
	    lv_obj_add_flag(ui_BLEIcon, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
	    lv_obj_clear_flag(ui_BLEIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	    ui_bottomContainer = lv_obj_create(ui_MainView);
	    lv_obj_remove_style_all(ui_bottomContainer);
	    lv_obj_set_width(ui_bottomContainer, lv_pct(41));
	    lv_obj_set_height(ui_bottomContainer, lv_pct(20));
	    lv_obj_set_align(ui_bottomContainer, LV_ALIGN_CENTER);
	    lv_obj_set_flex_flow(ui_bottomContainer, LV_FLEX_FLOW_ROW);
	    lv_obj_set_flex_align(ui_bottomContainer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	    lv_obj_clear_flag(ui_bottomContainer, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	    ui_dowLabel = lv_label_create(ui_bottomContainer);
	    lv_obj_set_width(ui_dowLabel, LV_SIZE_CONTENT);   /// 1
	    lv_obj_set_height(ui_dowLabel, LV_SIZE_CONTENT);    /// 1
	    lv_obj_set_align(ui_dowLabel, LV_ALIGN_CENTER);
	    lv_label_set_text(ui_dowLabel, "Miercoles");
	    ui_object_set_themeable_style_property(ui_dowLabel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
	                                           _ui_theme_color_sunset_glow);
	    ui_object_set_themeable_style_property(ui_dowLabel, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
	                                           _ui_theme_alpha_sunset_glow);
	    lv_obj_set_style_text_font(ui_dowLabel, &ui_font_QuantifyFont_16, LV_PART_MAIN | LV_STATE_DEFAULT);
	    lv_obj_add_event_cb(ui_MainView, timeController->event_MainView_wrapper, LV_EVENT_ALL, timeController.get());
	    lv_disp_load_scr(ui_MainView);
}

