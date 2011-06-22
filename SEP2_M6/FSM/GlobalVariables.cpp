/*
 * GlobalVariables.cpp
 *
 *  Created on: 21.06.2011
 *      Author: aax691
 */

#include "GlobalVariables.h"

GlobalVariables::GlobalVariables() {
	timer = Timer::getInstance();
	switch_TID = timer->getnextid();
}

GlobalVariables::~GlobalVariables() {

}

machineType GlobalVariables::getCurrentType() {
	return currentType;
}

void GlobalVariables::setCurrentType(machineType currentType) {
	this->currentType = currentType;
}

int GlobalVariables::getSwitch_TID() {
	return switch_TID;
}

void GlobalVariables::setSwitch_TID(int switch_TID) {
	this->switch_TID = switch_TID;
}
