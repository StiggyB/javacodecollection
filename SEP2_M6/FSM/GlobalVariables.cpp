/*
 * GlobalVariables.cpp
 *
 *  Created on: 21.06.2011
 *      Author: aax691
 */

#include "GlobalVariables.h"

GlobalVariables::GlobalVariables() {

}

GlobalVariables::~GlobalVariables() {

}

machineType GlobalVariables::getCurrentType() {
	return currentType;
}

void GlobalVariables::setCurrentType(machineType currentType) {
	this->currentType = currentType;
}
