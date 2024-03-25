/*
 * Controller.cpp
 *
 *  Created on: 23 mar 2024
 *      Author: root
 */

#include "Controller.h"

Controller::Controller(ControllerID controller_id,
		std::shared_ptr<NavigationController> navigationController) :
		navigationController(navigationController), controller_id(controller_id)
{
}


void Controller::setView(std::shared_ptr<View> view) {
	this->view = view;
}

void Controller::initView() {
	view->initView();
}

ControllerID Controller::getControllerID()
{
	return controller_id;
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

void Controller::initScreenWithAnim(lv_scr_load_anim_t anim_type, uint32_t time,
		uint32_t delay) {
	view->initScreenWithAnim(anim_type, time, delay);
}
