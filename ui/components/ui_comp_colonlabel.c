// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SmartWatch_ui

#include "../ui.h"


// COMPONENT colonLabel

lv_obj_t * ui_colonLabel_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_colonLabel;
    cui_colonLabel = lv_label_create(comp_parent);
    lv_obj_set_width(cui_colonLabel, lv_pct(9));
    lv_obj_set_height(cui_colonLabel, lv_pct(50));
    lv_obj_set_align(cui_colonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(cui_colonLabel, ":");

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_COLONLABEL_NUM);
    children[UI_COMP_COLONLABEL_COLONLABEL] = cui_colonLabel;
    lv_obj_add_event_cb(cui_colonLabel, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_colonLabel, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_colonLabel_create_hook(cui_colonLabel);
    return cui_colonLabel;
}
