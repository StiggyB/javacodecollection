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
 * Implements Singleton-Pattern.
 * Other parts can get their necessary ChannelID's and  register/unregister themself.
 *
 *
 */

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

void CoreController::serveAsCommunicationServer(){
	int rcvid = 0,id = 0;
	if(!setUpChannel()){
		perror("CC: channel setup failed");
		return;
	}else{
		cout << "CC: channel setup successful" << endl;
	}
	Message *m = (Message *) malloc(sizeof(Message));
	if(m == NULL){
		perror("CoreController: failed to get Space for Message!");
		destroyChannel(chid);
		return;
	}
	Communication::serverChannelId = chid;
	while(1){
		rcvid = MsgReceive(chid, m, sizeof(Message), NULL);
		//cout << "CC: message received. CA: "<<(*m).ca<<endl;
		switch((*m).ca){
		case addToServer:
			//cout << "CC: addToServer ->type: "<< (*m).Msg.comtype <<endl;
			addCommunicator((*m).chid,(*m).coid,(*m).Msg.comtype);
			buildMessage(m,(*m).chid,(*m).coid,OK,CORECONTROLLER);
			break;
		case removeFromServer:
			//cout << "CC: removeFromServer"<<endl;
			removeCommunicator((*m).chid,(*m).coid,(*m).Msg.comtype);
			buildMessage(m,(*m).chid,(*m).coid,OK,CORECONTROLLER); break;
		case getIDforCom:
			//cout << "CC: getIDforCom("<<(*m).Msg.comtype<<")"<<endl;
			id = getChannelIdForObject((*m).Msg.comtype);
			//cout << "CC: ID: " << id <<endl;
			if(id == -1){
				//cout << "CC: BuildMessage -> error"<<endl;
				buildMessage(m,id,(*m).coid,error,CORECONTROLLER);
			}else{
				//cout << "CC: BuildMessage -> OK"<<endl;
				buildMessage(m,id,(*m).coid,OK,CORECONTROLLER);
			}break;
		default:
			cout << "CoreController: defaultError"<<endl;
			buildMessage(m,(*m).chid,(*m).coid,error,CORECONTROLLER); break;
		}
		MsgReply(rcvid,0,m,sizeof(m));
	}
	cleanUp(0,m,NULL);
	destroyChannel(chid);
}

void CoreController::execute(void*) {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}
	serveAsCommunicationServer();
}

void CoreController::shutdown() {

}

//TODO implement
void CoreController::stopProcess(){

}

//TODO implement
void CoreController::emergencyStop(){
	cout << "CC: emergency Stop ;)" <<endl;
}
//TODO implement
void CoreController::stopMachine(){
	engineStop();
	cout << "CC: StopMachine ;)" <<endl;
}
//TODO implement
void CoreController::restart(){
	cout << "CC: restart ;)" <<endl;
}
//TODO implement
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
