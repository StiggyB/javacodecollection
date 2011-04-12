/*
 * MasterThread.cpp
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#include "CoreController.h"

Lampen l;
Mutex CoreController::singleton;
Mutex CoreController::m;
HAL* h;
CoreController* cc;

/**
 * Liste für die channelid's der Prozesse
 * funktion um channelid zu registrieren
 * funktion um channelid zu erfragen
 *
 */



CoreController* CoreController::pInstance = NULL;

CoreController* CoreController::getInstance() {
	if (!pInstance) {
		singleton.lock();
		if (!pInstance) {
			pInstance = new CoreController;
		}
		singleton.unlock();
	}
	return pInstance;
}

CoreController::CoreController() {
	h = HAL::getInstance();
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}
	out8(PORT_CNTRL, 0x82);
	resetAllOutPut();
}

CoreController::~CoreController() {
	singleton.~Mutex();
	m.~Mutex();
}

void CoreController::execute(void*) {
	InterruptController ic;
	ic.start(NULL);
	Test_HAL th;
	cout << "starting HAL-Tests" << endl;
	th.start(NULL);
	cout << "waiting for HAL-Tests" << endl;
	th.join();
	Test_M1 tm;
	cout << "starting M1-Tests" << endl;
	tm.start(NULL);
	cout << "waiting for M1-Tests" << endl;
	tm.join();
}

void CoreController::shutdown() {

}

void CoreController::emergencyStop(){
	cout << "CC: emergency Stop ;)" <<endl;
}

void CoreController::stopMachine(){
	cout << "CC: StopMachine ;)" <<endl;
}

void CoreController::restart(){
	cout << "CC: restart ;)" <<endl;
}

void CoreController::resetAll(){
	cout << "CC: resetAll ;)" <<endl;
}

void CoreController::stopProcess() {
	l.stop();
	resetAllOutPut();
}

int CoreController::read(int dir) {
	m.lock();
	int ret = (*h).read(dir);
	m.unlock();
	return ret;

}
bool CoreController::isInput(int dir) {
	m.lock();
	bool ret = (*h).isInput(dir);
	m.unlock();
	return ret;
}
bool CoreController::isOutput(int dir) {
	m.lock();
	bool ret = (*h).isOutput(dir);
	m.unlock();
	return ret;
}
int CoreController::write(int dir, int value) {
	m.lock();
	bool ret = (*h).write(dir, value);
	m.unlock();
	return ret;
}
int CoreController::reset(int dir, int value) {
	m.lock();
	int ret = (*h).reset(dir, value);
	m.unlock();
	return ret;
}
bool CoreController::engineStart(int direction) {
	m.lock();
	bool ret = (*h).engineStart(direction);
	m.unlock();
	return ret;
}
bool CoreController::openSwitch() {
	m.lock();
	bool ret = (*h).openSwitch();
	m.unlock();
	return ret;
}
bool CoreController::closeSwitch() {
	m.lock();
	bool ret = (*h).closeSwitch();
	m.unlock();
	return ret;
}
bool CoreController::setSwitchDirection(bool dir) {
	m.lock();
	bool ret = (*h).setSwitchDirection(dir);
	m.unlock();
	return ret;
}
bool CoreController::engineReset() {
	m.lock();
	bool ret = (*h).engineReset();
	m.unlock();
	return ret;
}
bool CoreController::engineStop() {
	m.lock();
	bool ret = (*h).engineStop();
	m.unlock();
	return ret;
}
bool CoreController::engineContinue() {
	m.lock();
	bool ret = (*h).engineContinue();
	m.unlock();
	return ret;
}
bool CoreController::engineRight() {
	m.lock();
	bool ret = (*h).engineRight();
	m.unlock();
	return ret;
}
bool CoreController::engineLeft() {
	m.lock();
	bool ret = (*h).engineLeft();
	m.unlock();
	return ret;
}
bool CoreController::engineSlowSpeed() {
	m.lock();
	bool ret = (*h).engineSlowSpeed();
	m.unlock();
	return ret;
}
bool CoreController::engineNormalSpeed() {
	m.lock();
	bool ret = (*h).engineNormalSpeed();
	m.unlock();
	return ret;
}
bool CoreController::engineStopped() {
	m.lock();
	bool ret = (*h).engineStopped();
	m.unlock();
	return ret;
}
bool CoreController::engineSlowSpeed(int dir) {
	m.lock();
	bool ret = (*h).engineSlowSpeed(dir);
	m.unlock();
	return ret;
}
bool CoreController::engineSpeed(bool slow) {
	m.lock();
	bool ret = (*h).engineSpeed(slow);
	m.unlock();
	return ret;
}
bool CoreController::engineSlowLeft() {
	m.lock();
	bool ret = (*h).engineSlowLeft();
	m.unlock();
	return ret;
}
bool CoreController::engineSlowRight() {
	m.lock();
	bool ret = (*h).engineSlowRight();
	m.unlock();
	return ret;
}
bool CoreController::attachISR(void * arg) {
	m.lock();
	bool ret = (*h).attachISR(arg);
	m.unlock();
	return ret;
}
int CoreController::getSetInterrupt() {
	m.lock();
	int ret = (*h).getSetInterrupt();
	m.unlock();
	return ret;
}
int CoreController::getInterrupt() {
	m.lock();
	int ret = (*h).getInterrupt();
	m.unlock();
	return ret;
}
bool CoreController::resetAllOutPut() {
	m.lock();
	bool ret = (*h).resetAllOutPut();
	m.unlock();
	return ret;
}
bool CoreController::removeLight(Color col) {
	m.lock();
	bool ret = (*h).removeLight(col);
	m.unlock();
	return ret;
}
bool CoreController::addLight(Color col) {
	m.lock();
	bool ret = (*h).addLight(col);
	m.unlock();
	return ret;
}
bool CoreController::shine(Color col) {
	m.lock();
	bool ret = (*h).shine(col);
	m.unlock();
	return ret;
}
