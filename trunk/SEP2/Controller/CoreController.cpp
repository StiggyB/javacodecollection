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

CoreController::CoreController():stopped(false),emstopped(false){
	h = HAL::getInstance();
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
	}
	resetAllOutPut();
}

CoreController::~CoreController() {
	singleton.~Mutex();
	m.~Mutex();
}

void CoreController::serveAsCommunicationServer(){
	//write(PORT_CNTRL,BIT_PORT_C_HIGH);
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
	addLED(LEDS_ON);
	while(!isStopped()){
		rcvid = MsgReceive(chid, m, sizeof(Message), NULL);
		//cout << "CC: message received. CA: "<<(*m).ca<<endl;
		switch((*m).m.ca){
		case addToServer:
			//cout << "CC: addToServer ->type: "<< (*m).Msg.comtype <<endl;
			addCommunicator((*m).m.chid,(*m).m.coid,(*m).m.comtype);
			buildMessage(m,(*m).m.chid,(*m).m.coid,OK,CORECONTROLLER);
			break;
		case removeFromServer:
			//cout << "CC: removeFromServer"<<endl;
			removeCommunicator((*m).m.chid,(*m).m.coid,(*m).m.comtype);
			buildMessage(m,(*m).m.chid,(*m).m.coid,OK,CORECONTROLLER); break;
		case getIDforCom:
			//cout << "CC: getIDforCom("<<(*m).Msg.comtype<<")"<<endl;
			id = getChannelIdForObject((*m).m.comtype);
			//cout << "CC: ID: " << id <<endl;
			if(id == -1){
				//cout << "CC: BuildMessage -> error"<<endl;
				buildMessage(m,id,(*m).m.coid,error,CORECONTROLLER);
			}else{
				//cout << "CC: BuildMessage -> OK"<<endl;
				buildMessage(m,id,(*m).m.coid,OK,CORECONTROLLER);
			}break;
		default:
			cout << "CoreController: defaultError"<<endl;
			buildMessage(m,(*m).m.chid,(*m).m.coid,error,CORECONTROLLER); break;
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

void CoreController::emergencyStop(){
	(*h).engineStop();
	(*h).closeSwitch();
	(*h).engineReset();
	(*h).shine(RED);
	(*h).removeLED(START_LED);
	emstopped = true;
	stopped = true;
	//TODO EXCEPTION HANDLEN!
	//(*h).engineStop();
	//m.lock();
	//EXCEPTION HANDLER end
	/*cout << "CC: emergency Stop ;)" <<endl;
	while (stopped) {
		if(!(*h).engineStopped()){
			(*h).closeSwitch();
			(*h).engineReset();
			(*h).engineStop();
		}
		sleep(1);
	}
	m.unlock();*/
}

void CoreController::stopMachine(){
	(*h).engineStop();
	(*h).closeSwitch();
	(*h).shine(RED);
	stopped = true;
	// TODO EXCEPTION HANDLEN!!!
	//m.lock();
	//EXCEPTION HANDLER end
	/*cout << "CC: Stop Machine! ;)" <<endl;
	while (stopped) {
		if(!(*h).engineStopped()){
			(*h).engineStop();
			(*h).closeSwitch();
		}
		sleep(1);
	}
	m.unlock();*/
}

void CoreController::restart() {
	if (!emstopped) {
		stopped = false;
		cout << "CC: restart ;)" << endl;
		engineContinue();
		shine(GREEN);
	}
}

void CoreController::resetAll() {
	stopped = false;
	emstopped = false;
	cout << "CC: resetAll ;)" << endl;
	closeSwitch();
	engineReset();
	shine(GREEN);
	shineLED(LEDS_ON);
}

int CoreController::read(int dir) {
	if (!(stopped && emstopped)) {
		m.lock();
		int ret = (*h).read(dir);
		m.unlock();
		return ret;
	}
	return -1;

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
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).write(dir, value);
		m.unlock();
		return ret;
	}
	return -1;
}
int CoreController::reset(int dir, int value) {
	if (!(stopped && emstopped)) {
		m.lock();
		int ret = (*h).reset(dir, value);
		m.unlock();
		return ret;
	}
	return -1;
}
bool CoreController::engineStart(int direction) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineStart(direction);
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::openSwitch() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).openSwitch();
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::closeSwitch() {
	m.lock();
	bool ret = (*h).closeSwitch();
	m.unlock();
	return ret;
}
bool CoreController::setSwitchDirection(bool dir) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).setSwitchDirection(dir);
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineReset() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineReset();
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineStop() {
	m.lock();
	bool ret = (*h).engineStop();
	m.unlock();
	return ret;
}
bool CoreController::engineContinue() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineContinue();
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineRight() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineRight();
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineLeft() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineLeft();
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineSlowSpeed() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineSlowSpeed();
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineNormalSpeed() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineNormalSpeed();
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineStopped() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineStopped();
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineSlowSpeed(int dir) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineSlowSpeed(dir);
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineSpeed(bool slow) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineSpeed(slow);
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineSlowLeft() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineSlowLeft();
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::engineSlowRight() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).engineSlowRight();
		m.unlock();
		return ret;
	}
	return false;
}
int CoreController::getSetInterrupt() {
	if (!(stopped && emstopped)) {
		m.lock();
		int ret = (*h).getSetInterrupt();
		m.unlock();
		return ret;
	}
	return -1;
}
int CoreController::getInterrupt() {
	if (!(stopped && emstopped)) {
		m.lock();
		int ret = (*h).getInterrupt();
		m.unlock();
		return ret;
	}
	return -1;
}
bool CoreController::resetAllOutPut() {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).resetAllOutPut();
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::removeLight(Color col) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).removeLight(col);
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::addLight(Color col) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).addLight(col);
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::shine(Color col) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).shine(col);
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::removeLED(LEDS led) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).removeLED(led);
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::addLED(LEDS led) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).addLED(led);
		m.unlock();
		return ret;
	}
	return false;
}
bool CoreController::shineLED(LEDS led) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).shineLED(led);
		m.unlock();
		return ret;
	}
	return false;
}

bool CoreController::activateInterrupt(int port) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).activateInterrupt(port);
		m.unlock();
		return ret;
	}
	return false;
}

bool CoreController::deactivateInterrupt(int port) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).deactivateInterrupt(port);
		m.unlock();
		return ret;
	}
	return false;
}

bool CoreController::setValueOfPort(int port, int val) {
	if (!(stopped && emstopped)) {
		m.lock();
		bool ret = (*h).setValueOfPort(port, val);
		m.unlock();
		return ret;
	}
	return false;
}
