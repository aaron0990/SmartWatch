/*
 * View.cpp
 *
 *  Created on: 15 mar 2024
 *      Author: root
 */

#include "View.h"


View::View(ViewID view_id) : view_id(view_id)
{
	// TODO Auto-generated constructor stub

}

View::~View() {
	// TODO Auto-generated destructor stub
}

ViewID View::getViewID()
{
	return view_id;
}
