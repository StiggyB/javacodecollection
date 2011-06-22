/**
 * Puck_FSM
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Milestone 4: Automatenimplementierung
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 *For global variables, machine type, global timer id's..
 *
 *
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
