/*
 * View.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "View.h"


View::View(uint8_t view_id) : view_id(view_id)
{
	// TODO Auto-generated constructor stub

}

View::~View() {
	// TODO Auto-generated destructor stub
}

uint8_t View::get_view_id()
{
	return view_id;
}
