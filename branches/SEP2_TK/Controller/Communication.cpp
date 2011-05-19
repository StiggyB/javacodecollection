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

Communication::Communication() : lst(),rcvid(0) {

}

Communication::~Communication() {

}

int Communication::getChannelIdForObject(CommunicatorType c){
	std::list<Communicator>::iterator it;
	for(it  = lst.begin(); it != lst.end();it++){
		if((*it).getCom() == c){
			return (*it).getChannelID();
		}
	}
	return -1;
}

int Communication::getConnectIdForObject(CommunicatorType c){
	std::list<Communicator>::iterator it;
	for(it  = lst.begin(); it != lst.end();it++){
		if((*it).getCom() == c){
			return (*it).getConnectID();
		}
	}
	return -1;
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

bool Communication::requestChannelIDForObject(CommunicatorType c){
	int coid = ConnectAttach(0, 0, serverChannelId, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach Channel for ID Request\n");
		return false;
	}
	Message * msg_s = (Message *) malloc(sizeof(Message));
	if (msg_s == NULL) {
		perror("Communication: failed to get Space for Message.");
		cleanUp(coid,NULL,NULL);
		return false;
	}
	buildMessage(msg_s, serverChannelId, coid, getIDforCom, c);
	Message * r_msg = (Message*) malloc(sizeof(Message));
	if (r_msg == NULL) {
		perror("Communication: failed to get Space for Receive Message.");
		cleanUp(0,msg_s,NULL);
		return false;
	}
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
	addCommunicator((*r_msg).m.chid,0,c);
	cleanUp(0,msg_s,r_msg);
	return true;
}

bool Communication::addCommunicator(int ch, int cod, CommunicatorType ct){
	Communicator *com = new Communicator(ch,cod,ct);
	lst.insert(lst.begin(),*com);
	//printList();
	return true;
}

bool Communication::removeCommunicator(int ch, int cod,  CommunicatorType ct){
	std::list<Communicator>::iterator it;
	for (it = lst.begin(); it != lst.end(); it++) {
		if ((*it).getCom() == ct && (*it).getConnectID() == cod  && (*it).getChannelID() == ch) {
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
		std::cout << "Com: " << (*it).getCom() << " ChID: " <<  (*it).getChannelID() << " CoID: " <<  (*it).getConnectID() << std::endl;
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

bool Communication::registerChannel(CommunicatorType c){
	int coid = ConnectAttach(0, 0, serverChannelId, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach Channel for Interrupt\n");
		cleanUp(coid);
		return false;
	}
	Message * msg_s = (Message *) malloc(sizeof(Message));
	if(msg_s == NULL){
		perror("Communication: failed to get Space for Message.");
		cleanUp(coid);
		return false;
	}
	buildMessage(msg_s,chid,coid,addToServer,c);
	Message  *  r_msg =  (Message*) malloc(sizeof(Message));
	if(r_msg ==  NULL){
		perror("Communication: failed to get Space for Receive Message.");
		cleanUp(coid,msg_s,NULL);
		return false;
	}
	if(-1 == MsgSend(coid,msg_s,sizeof(Message),r_msg,sizeof(Message))){
		perror("Communication: failed to send Message to server,");
		ConnectDetach(coid);
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	if(-1  == ConnectDetach(coid)){
		perror("Communication: failed to detach client from server");
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	cleanUp(coid,msg_s,r_msg);
	return true;
}

bool Communication::unregisterChannel(CommunicatorType c) {
	int coid = ConnectAttach(0, 0, serverChannelId, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach Channel for Interrupt\n");
		cleanUp(coid);
		return false;
	}
	Message * msg_s = (Message *) malloc(sizeof(Message));
	if (msg_s == NULL) {
		perror("Communication: failed to get Space for Message.");
		cleanUp(coid);
		return false;
	}
	buildMessage(msg_s, chid, coid, removeFromServer, c);
	Message * r_msg = (Message*) malloc(sizeof(Message));
	if (r_msg == NULL) {
		perror("Communication: failed to get Space for Receive Message.");
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	if (-1 == MsgSend(coid, msg_s, sizeof(Message), r_msg, sizeof(Message))) {
		perror("Communication: failed to send Message to server,");
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	if (-1 == ConnectDetach(coid)) {
		perror("Communication: failed to unregister client from server");
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	cleanUp(coid,msg_s,r_msg);
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

bool Communication::attachConnection(int id, CommunicatorType c){
	coid = ConnectAttach(0, 0, id, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach Channel for Interrupt\n");
		return false;
	}
	std::cout << "Com_attachConnection done for: " << c << std::endl;
	Message * msg_s = (Message *) malloc(sizeof(Message));
	if (msg_s == NULL) {
		perror("Communication: failed to get Space for Message.");
		cleanUp(coid,msg_s,NULL);
		return false;
	}
	//std::cout << "Com_attachConnection got space 4 Message" << std::endl;
	buildMessage(msg_s,id, coid, startConnection, c);
	//std::cout << "Com_attachConnection build Message done" << std::endl;
	Message * r_msg = (Message*) malloc(sizeof(Message));
	if (r_msg == NULL) {
		perror("Communication: failed to get Space for Receive Message.");
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	std::cout << "coid: "<< msg_s->m.coid << " chid: "<< msg_s->m.chid << endl;
	//std::cout << "Com_attachConnection got Space 4 Receive Message" << std::endl;
	if (-1 == MsgSend(coid, msg_s, sizeof(Message), r_msg, sizeof(Message))) {
		perror("Communication: failed to send Message to server.");
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	std::cout << "Com_attachConnection got answer!" << std::endl;
	if ((*r_msg).m.ca != OK) {
		//std::cout << "ReturnMessageType: " << r_msg->ca << std::endl;
		perror("Communication: no OK from Receiver! ");
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	std::cout << "Com_attachConnection Msg was OK, coid: "<<coid << std::endl;
	cleanUp(0,msg_s,r_msg);
	std::list<Communicator>::iterator it = getCommunicatorForObject(id,0);
	if(it == NULL){
		return false;
	}else{
		(*it).setConnectID(coid);
		return true;
	}

}

bool Communication::detachConnection(int coid,CommunicatorType c){
	int id = getChannelIdForObject(c);
	Message * msg_s = (Message *) malloc(sizeof(Message));
	if (msg_s == NULL) {
		perror("Communication: failed to get Space for Message.");
		return false;
	}
	buildMessage(msg_s, id, coid, closeConnection, c);
	Message * r_msg = (Message*) malloc(sizeof(Message));
	if (r_msg == NULL) {
		perror("Communication: failed to get Space for Receive Message.");
		cleanUp(0,msg_s,NULL);
		return false;
	}
	if (-1 == MsgSend(coid,msg_s,sizeof(Message),r_msg,sizeof(Message))){
		perror("Communication: failed to send Message to server,");
		cleanUp(0,msg_s,r_msg);
	}
	if((*r_msg).m.ca != OK){
		perror("Communication: _Detach_Communication_ no OK from Receiver!");
		cleanUp(0,msg_s,r_msg);
		return false;
	}
	if (ConnectDetach(coid) == -1) {
		perror("Communication: failed to detach Channel for Interrupt\n");
		cleanUp(coid,msg_s,r_msg);
		return false;
	}
	cleanUp(0,msg_s,r_msg);
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
	(*m).m.chid = chid;
	(*m).m.coid = coid;
	(*m).m.ca =  activity;
	(*m).m.comtype = c;
	(*m).m.wert = val;
}

bool Communication::allocMessages() {
	m = (Message *) malloc(sizeof(Message));
	r_msg = (Message*) malloc(sizeof(Message));
	if (r_msg == NULL) {
		perror("Communication: failed to get Space for Receive Message.");
		return false;
	}
	if (m == NULL) {
		perror("Communication: failed to get Space for Message.");
		return false;
	}
	return true;
}

bool Communication::prepareCommunication(CommunicatorType c){
	if (!setUpChannel()) {
		perror("Communication: channel setup failed " + c );
		return false;
	} else {
		cout << "Communication: channel setup successful " << chid << " for "<< c << endl;
	}
	if (!registerChannel(c)) {
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
	//cout <<"0 connectWithCommunicator TYPE " << c << " my: "<< my <<endl;
	int id = getChannelIdForObject(c);
	//cout <<"1 connectWithCommunicator TYPE " << c << " my: "<< my <<endl;
	if (!attachConnection(id, c)) {
		perror("Communication: failed to AttachConnection!");
		return false;
	}
	//cout <<"2 connectWithCommunicator TYPE " << c << " my: "<< my <<endl;
	coid = getConnectIdForObject(c);
	buildMessage(m, chid, coid, startConnection, my);
	if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
		perror("Communication: failed to send message to IC!");
		return false;
	}
	//cout <<"3 connectWithCommunicator TYPE " << c << " my: "<< my <<endl;
	if (-1 == (id = getChannelIdForObject(c))) {
		perror("Communication: failed to get ChannelId!");
		return false;
	}

	return true;
}

bool Communication::sendPulses(CommunicatorType target, int code, int value){
	int coid = 0;
	if(-1 != (coid = getConnectIdForObject(target))){
		if(-1 == MsgSendPulse(coid, 0,code,value)){
			perror("Communication: Failed to send target a pulse!");
			return false;
		}
		cout << "sendPuls: " << coid << endl;
		return true;
	}
	perror("Communication: Failed to getConnect Id for target object pulse!");
	return false;
}

bool Communication::settingUpCommunicatorDevice(CommunicatorType mine, CommunicatorType target){

	cout<<"Communicator mine: "<< mine<<" target: " << target << " aaa 0 settingUpCommunicatorDevice OKAY"<<endl;
	if (prepareCommunication(mine)) {

		cout<<"Communicator mine: "<< mine<<" target: " << target << " aaa 1 settingUpCommunicatorDevice OKAY"<<endl;
		if (target != NONE && !requestChannelIDForObject(target)) {
			perror("Communicator: request failed");
			unregisterChannel(mine);
			return false;
		}

		if (!allocMessages()) {
			perror("Communicator: alloc Messages failed");
			cleanCommunication(mine);
			return false;
		}
		cout<<"3 settingUpCommunicatorDevice OKAY"<<endl;
		if(target != NONE && !connectWithCommunicator(target,mine)){
			perror("Communicator: connect with communicator failed");
			cleanCommunication(mine);
			return false;
		}
	}
	cout<<"Communicator mine: "<< mine<<" target: " << target << " last settingUpCommunicatorDevice OKAY"<<endl;
	return true;
}

void Communication::cleanCommunication(CommunicatorType mine){
	if(mine != COMMUNICATIONCONTROLLER){
		unregisterChannel(mine);
	}
	cleanUp(0, m, r_msg);
	destroyChannel(chid);
}

void Communication::endCommunication(CommunicatorType mine){
	if (!detachConnection(coid, mine)) {
		perror("Communication: failed to detach Channel\n");
		cleanCommunication(mine);
		return;
	}
	if (!unregisterChannel(mine)) {
		perror("Communication: unregister channel failed!");
	}
	cleanCommunication(mine);
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

bool Communication::handleConnectionMessages(CommunicatorType c) {
	if (r_msg->m.ca == startConnection) {
		//cout <<"0 handleConnectionMessages-------------------------\n"<<endl;
		if (addCommunicator(r_msg->m.chid, r_msg->m.coid, r_msg->m.comtype)) {
			buildMessage(m, r_msg->m.chid, r_msg->m.coid, OK, c);
			//cout <<"1 handleConnectionMessages-------------------------\n"<<endl;
			if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
				perror("Communication: failed to send reply message to Communicator!");
			}
			//cout <<"2 handleConnectionMessages-------------------------\n"<<endl;
			if ((coid = ConnectAttach(0, 0, r_msg->m.chid, _NTO_SIDE_CHANNEL, 0)) == -1) {
				perror("Communication: failed to attach Channel to other Instance\n");
			}
			//cout <<"3 handleConnectionMessages-------------------------\n"<<endl;
			getCommunicatorForObject(r_msg->m.chid, r_msg->m.coid)->setConnectID(coid);
		} else {
			perror("Communication: failed to addCommunicator");
		}
	} else if (r_msg->m.ca == closeConnection) {
		if (removeCommunicator(r_msg->m.chid, r_msg->m.coid, r_msg->m.comtype)) {
			perror("Communication: remove Communicator.");
		}
	} else {
		//cout << "Communication: message encountered, but not known..." << endl;
		return false;
	}
	//cout <<"gut handleConnectionMessages-------------------------\n"<<endl;
	return true;
}

