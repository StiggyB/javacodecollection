/*
 * GlobalVariables.cpp
 *
 *  Created on: 21.06.2011
 *      Author: aax691
 */

#include "GlobalVariables.h"

GlobalVariables::GlobalVariables() {
	// TODO Auto-generated constructor stub

}

GlobalVariables::~GlobalVariables() {
	// TODO Auto-generated destructor stub
}

machineType GlobalVariables::getCurrentType() {
	return currentType;
}

void GlobalVariables::setCurrentType(machineType currentType) {
	this->currentType = currentType;
}
