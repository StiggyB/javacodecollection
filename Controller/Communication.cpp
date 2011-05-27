/**
 * Communication
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Capsulates many functions for the direct
 * connection of components via Messages.
 */

#include "Communication.h"

volatile int Communication::serverChannelId = 0;
int Communication::uniqueIDCounter = 1;

Communication::Communication() : lst(),rcvid(0) {
	uniqueID = uniqueIDCounter++;
}

Communication::~Communication() {

}

int Communication::getChannelIdForObject(CommunicatorType c){
	return getChannelIdForObject(c,0);
}

int Communication::getChannelIdForObject(CommunicatorType c, int number) {
	return getIdForObject(c,number,CHANNEL);
}

int Communication::getIdForObject(CommunicatorType c, int number,int mode) {
	std::list<Communicator>::iterator it;
	for (it = lst.begin(); it != lst.end(); it++) {
		if ((*it).getCom() == c) {
			if (number == 0) {
				switch(mode){
					case CHANNEL: return (*it).getChannelID();break;
					case CONNECT: return (*it).getConnectID();break;
					case UNIQUE: return (*it).getUniqueID();break;
					default: return -1;break;
				}
			} else {
				number--;
			}
		}
	}
	return -1;
}


int Communication::getConnectIdForObject(CommunicatorType c){
	return getConnectIdForObject(c,0);
}

int Communication::getConnectIdForObject(CommunicatorType c, int number) {
	return getIdForObject(c,number,CONNECT);
}

int Communication::getUniqueIdForObject(CommunicatorType c){
	return getUniqueIdForObject(c,0);
}

int Communication::getUniqueIdForObject(CommunicatorType c, int number){
	return getIdForObject(c,number,UNIQUE);
}

std::list<Communication::Communicator>::iterator Communication::getCommunicatorForObject(int ci,int co){
	std::list<Communicator>::iterator it;
	for(it  = lst.begin(); it != lst.end();it++){
		if((*it).getChannelID() == ci && (*it).getConnectID() == co ){
			return it;
		}
	}
	return NULL;
}

std::list<Communication::Communicator>::iterator Communication::getCommunicatorForObject(int uni){
	std::list<Communicator>::iterator it;
	for(it  = lst.begin(); it != lst.end();it++){
		if((*it).getUniqueID() == uni){
			return it;
		}
	}
	return NULL;
}

bool Communication::requestChannelIDForObject(CommunicatorType c){
	return requestChannelIDForObject(c,0);
}

bool Communication::addCommunicator(int ch, int cod, int uni, CommunicatorType ct){
	Communicator *com = new Communicator(ch,cod,uni,ct);
	lst.insert(lst.begin(),*com);
	return true;
}

bool Communication::removeCommunicator(int uni){
	std::list<Communicator>::iterator it;
	for (it = lst.begin(); it != lst.end(); it++) {
		if ((*it).getUniqueID() == uni) {
			lst.erase(it);
			return true;
		}
	}
	return false;
}

void Communication::printList(){
	std::list<Communicator>::iterator it;
	std::cout << "List begin:" << std::endl;
	for (it = lst.begin(); it != lst.end(); it++) {
		std::cout << "UID: " << (*it).getUniqueID() << "Com: " << (*it).getCom() << " ChID: " <<  (*it).getChannelID() << " CoID: " <<  (*it).getConnectID() << std::endl;
	}
}

bool Communication::setUpChannel(){
	//std::cout << "trying setUpChannel" << std::endl;
	chid = ChannelCreate(0);
	//std::cout << "setUpChannel: chid: "<< chid << std::endl;
	if (chid == -1) {
		perror("Communication: failed to create Channel\n");
		return false;
	}
	//std::cout << "setUpChannel done" << std::endl;
	return true;
}


bool Communication::cleanUp(int coid){
	return cleanUp(coid,NULL,NULL);
}

bool Communication::cleanUp(int coid,Message *m,Message *r){
	if(m != NULL) free(m);
	if(r != NULL) free(r);
	if(coid != 0 && coid != -1){ return (-1 != ConnectDetach(coid));}
	return true;
}



bool Communication::destroyChannel(int id){
	if (ChannelDestroy(id) == -1) {
		perror("Communication: failed to destroy Channel\n");
		return false;
	}
	return true;
}

void Communication::buildMessage(void *s, int chid, int coid, MsgType activity,CommunicatorType c){
	buildMessage(s,chid,coid,activity,c,0);
}

void Communication::buildMessage(void *s, int chid, int coid, MsgType activity,CommunicatorType c, int val){
	Message *m =  (Message*) s;
	m->m.chid = chid;
	m->m.coid = coid;
	m->m.ca =  activity;
	m->m.comtype = c;
	m->m.wert = val;
}

bool Communication::allocMessages() {
	return allocMessages((void**)&m, (void**)&r_msg);
}

bool Communication::allocMessages(void ** msg, void ** rmsg) {
	Message * ms = ( Message *) malloc(sizeof(Message));
	Message * rm = ( Message *) malloc(sizeof(Message));
	if (rm == NULL) {
		perror("Communication: failed to get Space for Receive Message.");
		free(ms);
		return false;
	}
	if (ms == NULL) {
		perror("Communication: failed to get Space for Message.");
		free(rm);
		return false;
	}
	(*rmsg) = rm;
	(*msg) = ms;
	return true;
}

bool Communication::prepareCommunication(CommunicatorType c){
	if (!setUpChannel()) {
		perror("Communication: channel setup failed " + c );
		return false;
	} else {
		cout << "Communication: channel setup successful " << chid << " for "<< c << endl;
	}
	if (!registerChannel(c,uniqueID)) {
		perror("Communication: register channel failed" + c);
		destroyChannel(chid);
		return false;
	} else {
		cout << "Communication: register channel successful : " << c << endl;
	}
	return true;
}

void Communication::handleMessage() {
	switch (rcvid) {
	case 0:
		handlePulsMessage();
		break;
	case -1:
		perror("Communication: failed to get Message\n");
		break;
	default:
		handleNormalMessage();
		break;
	}
}

bool Communication::connectWithCommunicator(CommunicatorType c, CommunicatorType my){
	return connectWithCommunicator(c,0,my);
}

bool Communication::connectWithCommunicator(CommunicatorType c, int number, CommunicatorType my){
	int id = getChannelIdForObject(c,number);
	if ( -1 == id ) {
		perror("Communication: failed to get ChannelId!");
		return false;
	}
	if (!attachConnection(id, c)) {
		perror("Communication: failed to AttachConnection!");
		return false;
	}
	if(c != my){
		coid = getConnectIdForObject(c,number);
		buildMessage(m, chid, coid, startConnection, my,uniqueID);
		if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
			perror("Communication: failed to send message to Communicator!");
			return false;
		}
	}
	return true;
}

bool Communication::sendPulses(CommunicatorType target, int code, int value){
	return sendPulses(target,0,code,value);
}

bool Communication::sendPulses(CommunicatorType target, int number, int code, int value){
	int coid = 0;
	if(-1 != (coid = getConnectIdForObject(target,number))){
		if(-1 == MsgSendPulse(coid, PULSE_MIN_PRIO, code, value)){
			perror("Communication: Failed to send target a pulse!");
			return false;
		}
		return true;
	}
	perror("Communication: Failed to getConnect Id for target object pulse!");
	return false;
}

bool Communication::settingUpCommunicatorDevice(CommunicatorType target){
	if (prepareCommunication(mine)) {
		if (target != NONE && !requestChannelIDForObject(target)) {
			perror("Communicator: request failed");
			unregisterChannel(mine,uniqueID);
			return false;
		}
		if (!allocMessages()) {
			perror("Communicator: alloc Messages failed");
			cleanCommunication();
			return false;
		}
		if(target != NONE && !connectWithCommunicator(target,mine)){
			perror("Communicator: connect with communicator failed");
			cleanCommunication();
			return false;
		}
	}
	return true;
}

void Communication::cleanCommunication(){
	if(mine != COMMUNICATIONCONTROLLER){
		unregisterChannel(mine,uniqueID);
	}
	cleanUp(0, m, r_msg);
	destroyChannel(chid);
}

void Communication::endCommunication(){
	if (!detachConnection(coid, mine,uniqueID)) {
		perror("Communication: failed to detach Channel\n");
		cleanCommunication();
		return;
	}
	if (!unregisterChannel(mine,uniqueID)) {
		perror("Communication: unregister channel failed!");
	}
	cleanCommunication();
}

int Communication::getCodeFromPulse(Message *ptr){
	return ptr->pulse.code;
}

int Communication::getValueFromPulse(Message *ptr){
	return ptr->pulse.value.sival_int;
}


int Communication::getCodeFromReceivePulse(){
	return getCodeFromPulse(r_msg);
}

int Communication::getValueFromReceivePulse(){
	return getValueFromPulse(r_msg);
}

bool Communication::handleConnectionMessage() {
	if (r_msg->m.ca == startConnection) {
		getConnectionAttached();
	} else if (r_msg->m.ca == closeConnection) {
		if (removeCommunicator( r_msg->m.wert)) {
			perror("Communication: remove Communicator.");
		}
	} else {
		return false;
	}
	return true;
}

void Communication::getConnectionAttached(){
	if (addCommunicator(r_msg->m.chid, r_msg->m.coid, r_msg->m.wert, r_msg->m.comtype)) {
		buildMessage(m, r_msg->m.chid, r_msg->m.coid, OK, mine,uniqueID);
		if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
			perror("Communication: failed to send reply message to Communicator!");
		}
		if ((coid = ConnectAttach(0, 0, r_msg->m.chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
			perror("Communication: failed to attach Channel to other Instance\n");
		}
		getCommunicatorForObject(r_msg->m.wert)->setConnectID(coid);
	} else {
		perror("Communication: failed to addCommunicator");
	}
}

bool Communication::requestChannelIDForObject(CommunicatorType c,int number){
	int coid = ConnectAttach(0, 0, serverChannelId, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach Channel for ID Request\n");
		return false;
	}
	Message * msg_s, *r_msg;
	if (!allocMessages((void**) &msg_s,(void**) &r_msg)) {
		perror("Communication: failed to get Space for Message.");
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	buildMessage(msg_s, serverChannelId, coid, getIDforCom, c, number);
	if (-1 == MsgSend(coid, msg_s, sizeof(Message), r_msg, sizeof(Message))) {
		perror("Communication: failed to send Message to server!");
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	if (-1 == ConnectDetach(coid)) {
		perror("Communication: failed to detach client from server!");
		cleanUp(0,msg_s,r_msg);
		return false;
	}
	addCommunicator(r_msg->m.chid,0,r_msg->m.wert,c);
	cleanUp(0,msg_s,r_msg);
	return true;
}

bool Communication::attachConnection(int id, CommunicatorType c){
	coid = ConnectAttach(0, 0, id, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach Channel.");
		return false;
	}
	if(c != mine){
		Message * msg_s, * r_msg;
		if(!allocMessages((void**)&msg_s,(void**)&r_msg)){
			ConnectDetach(coid);
			return false;
		}
		buildMessage(msg_s,id, coid, startConnection, c,uniqueID);
		if (-1 == MsgSend(coid, msg_s, sizeof(Message), r_msg, sizeof(Message))) {
			perror("Communication: failed to send Message to server.");
			cleanUp(coid,msg_s,r_msg);
			return false;
		}
		if (r_msg->m.ca != OK) {
			perror("Communication: no OK from Receiver! ");
			cleanUp(coid,msg_s,r_msg);
			return false;
		}
		cleanUp(0,msg_s,r_msg);
	}
	std::list<Communicator>::iterator it = getCommunicatorForObject(id,0);
	return (it == NULL ? false : (*it).setConnectID(coid));
}

bool Communication::detachConnection(int coid,CommunicatorType c,int unique){
	Message ** msg_s=NULL, **r_msg=NULL;
	int id = getChannelIdForObject(c,unique);
	if(!doInternalExchange(msg_s,r_msg,c, coid, id, unique, closeConnection)){
		perror("Communication: failed to do internal exchange\n");
		cleanUp(coid);
		return false;
	}
	if((*r_msg)->m.ca != OK){
		perror("Communication: _Detach_Communication_ no OK from Receiver!");
		cleanUp(0,*msg_s,*r_msg);
		return false;
	}
	cleanUp(0,*msg_s,*r_msg);
	return true;
}

bool Communication::registerChannel(CommunicatorType c, int unique){
	return regEditChannel(c,unique,addToServer);
}

bool Communication::unregisterChannel(CommunicatorType c, int unique) {
	return regEditChannel(c,unique,removeFromServer);
}
bool Communication::regEditChannel(CommunicatorType c, int unique, MsgType m){
	Message * msg_s, *r_msg;
	int coid = ConnectAttach(0, 0, serverChannelId, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach channel\n");
		cleanUp(coid);
		return false;
	}
	if(!doInternalExchange(&msg_s,&r_msg,c, coid, chid, unique, m)){
		perror("Communication: failed to do internal exchange\n");
		cleanUp(coid);
		return false;
	}
	cleanUp(coid, msg_s, r_msg);
	return true;
}

bool Communication::doInternalExchange(Message ** ptrM,Message ** ptrR,
		CommunicatorType c, int coid, int chid, int unique, MsgType m) {
	Message * msg_s, *r_msg;
	if (!allocMessages((void**) &msg_s, (void**) &r_msg)) {
		perror("Communication: failed to get Space for Message.");
		cleanUp(coid, msg_s, r_msg);
		return false;
	}
	(*ptrM) = msg_s;(*ptrR) = r_msg;
	buildMessage(msg_s, chid, coid, m, c, unique);
	if (-1 == MsgSend(coid, msg_s, sizeof(Message), r_msg, sizeof(Message))) {
		perror("Communication: failed to send Message to server,");
		cleanUp(coid, msg_s, r_msg);
		return false;
	}
	if (-1 == ConnectDetach(coid)) {
		perror("Communication: failed to unregister client from server");
		cleanUp(coid, msg_s, r_msg);
		return false;
	}
	return true;
}
