/**
 * Core Controller
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Capsulates many functions for the direct
 * in- and output from and to the Festo Transfersystem and
 * with Interrupts using Pulse Messages.
 * Starts the threads. Implements Singleton-Pattern.
 *
 * Upcoming: Other parts can get their necessary ChannelID's.

 * Liste für die channelid's der Prozesse
 * funktion um channelid zu registrieren
 * funktion um channelid zu erfragen
 *
 * Inherits: IHAL.h, HAWThread.h
 */

//TODO inherit Singleton
//TODO capsulate all activities on port variables through CoreController -> HAL

#include "CoreController.h"

Mutex CoreController::singleton;
Mutex CoreController::m;

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

void CoreController::deleteInstance(){
	if( pInstance != NULL ){
		singleton.lock();
		if( pInstance != NULL ){
			delete pInstance;
			pInstance = NULL;
		}
		singleton.unlock();
	}
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
	int rcvid = 0,id = 0;
	Message *m = (Message *) malloc(sizeof(Message));
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}
	if(!setUpChannel()){
		cout << "CC: channel setup failed" << endl;
	}else{
		cout << "CC: channel setup successful" << endl;
	}
	Communication::serverChannelId = chid;
	while(1){
		rcvid = MsgReceive(chid, m, sizeof(Message), NULL);
		cout << "message received"<<endl;
		switch((*m).ca){
		case addToServer:
			addCommunicator((*m).chid,(*m).coid,(*m).Msg.comtype);
			buildMessage(m,(*m).chid,(*m).coid,OK,CORECONTROLLER);
			break;
		case removeFromServer:
			removeCommunicator((*m).chid,(*m).coid,(*m).Msg.comtype);
			buildMessage(m,(*m).chid,(*m).coid,OK,CORECONTROLLER); break;
		case getIDforCom:
			id = getChannelIdForObject((*m).Msg.comtype);
			if(id == -1){
				buildMessage(m,id,(*m).coid,error,CORECONTROLLER); break;
			}else{
				buildMessage(m,id,(*m).coid,OK,CORECONTROLLER); break;
			}
		default: buildMessage(m,(*m).chid,(*m).coid,error,CORECONTROLLER); break;
		}
		MsgReply(rcvid,0,m,sizeof(m));
	}
}

void CoreController::shutdown() {

}

void CoreController::emergencyStop(){
	cout << "CC: emergency Stop ;)" <<endl;
}

void CoreController::stopMachine(){
	engineStop();
	cout << "CC: StopMachine ;)" <<endl;
}

void CoreController::restart(){
	cout << "CC: restart ;)" <<endl;
}

void CoreController::resetAll(){
	cout << "CC: resetAll ;)" <<endl;
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

float CoreController::getHeight(){
	m.lock();
	float ret = (*h).getHeight();
	m.unlock();
	return ret;
}

void CoreController::stopProcess(){

}
