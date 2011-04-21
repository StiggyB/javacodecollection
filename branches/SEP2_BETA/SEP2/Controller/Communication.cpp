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
 * symbolic: auskunft für die channelid's
 */

//TODO all... message storage, message exchange

#include "Communication.h"

volatile int Communication::serverChannelId = 0;

Communication::Communication() : lst() {

}

Communication::~Communication() {

}

//sucht chid aus lst raus
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


//holt id vom server (cc)
int Communication::requestChannelIDForObject(CommunicatorType c){
	int coid = ConnectAttach(0, 0, serverChannelId, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach Channel for ID Request\n");
	}
	message * msg_s = (message *) malloc(sizeof(message));
	if (msg_s == NULL) {
		perror("Communication: failed to get Space for Message.");
		return false;
	}
	if (-1 == buildMessage(msg_s, serverChannelId, coid, getIDforCom, c)) {
		perror("Communication: failed to create Message!");
		return false;
	}
	message * r_msg = (message*) malloc(sizeof(message));
	if (r_msg == NULL) {
		perror("Communication: failed to get Space for Receive Message.");
		return false;
	}
	if (-1 == MsgSend(coid, msg_s, sizeof(msg_s), r_msg, sizeof(r_msg))) {
		perror("Communication: failed to send message to server!");
		return false;
	}
	if (-1 == ConnectDetach(coid)) {
		perror("Communication: failed to detach client from server!");
	}
	addCommunicator((*r_msg).chid,0,c);
	//lst.insert(lst.begin(),(new Communicator((*r_msg).chid,c)));
	return true;
}

bool Communication::addCommunicator(int ch, int cod, CommunicatorType ct){
	Communicator *com = new Communicator(ch,cod,ct);
	lst.insert(lst.begin(),*com);
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

bool Communication::setUpChannel(){
	chid =  0;
	std::cout << "trying setUpChannel" << std::endl;
	if ((chid = ChannelCreate(0)) == -1) {
		perror("Communication: failed to create Channel\n");
		return false;
	}
	std::cout << "setUpChannel done" << std::endl;
	return true;
}

bool Communication::registerChannel(){
	int coid = ConnectAttach(0, 0, serverChannelId, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach Channel for Interrupt\n");
	}
	message * msg_s = (message *) malloc(sizeof(message));
	if(msg_s == NULL){
		perror("Communication: failed to get Space for Message.");
		return false;
	}
	if(-1 == buildMessage(msg_s,chid,coid,addToServer,0)){
		perror("Communication: failed to create Message!");
		return false;
	}
	message  *  r_msg =  (message*) malloc(sizeof(message));
	if(r_msg ==  NULL){
		perror("Communication: failed to get Space for Receive Message.");
		return false;
	}
	if(-1 == MsgSend(coid,msg_s,sizeof(msg_s),r_msg,sizeof(r_msg))){
		perror("Communication: failed to send message to server,");
	}
	if(-1  == ConnectDetach(coid)){
		perror("Communication: failed to detach client from server");
	}
	return true;
}

bool Communication::deregisterChannel() {
	int coid = ConnectAttach(0, 0, serverChannelId, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach Channel for Interrupt\n");
	}
	message * msg_s = (message *) malloc(sizeof(message));
	if (msg_s == NULL) {
		perror("Communication: failed to get Space for Message.");
		return false;
	}
	if (-1 == buildMessage(msg_s, chid, coid, removeFromServer, 0)) {
		perror("Communication: failed to create Message!");
		return false;
	}
	message * r_msg = (message*) malloc(sizeof(message));
	if (r_msg == NULL) {
		perror("Communication: failed to get Space for Receive Message.");
		return false;
	}
	if (-1 == MsgSend(coid, msg_s, sizeof(msg_s), r_msg, sizeof(r_msg))) {
		perror("Communication: failed to send message to server,");
	}
	if (-1 == ConnectDetach(coid)) {
		perror("Communication: failed to deregister client from server");
	}
	return true;
}

bool Communication::attachConnection(int id, CommunicatorType c){
	coid = ConnectAttach(0, 0, id, _NTO_SIDE_CHANNEL, 0);
	if (coid == -1) {
		perror("Communication: failed to attach Channel for Interrupt\n");
	}
	message * msg_s = (message *) malloc(sizeof(message));
	if (msg_s == NULL) {
		perror("Communication: failed to get Space for Message.");
		return false;
	}
	if (-1 == buildMessage(msg_s,id, coid, startConnection, c)) {
		perror("Communication: failed to create Message!");
		return false;
	}
	message * r_msg = (message*) malloc(sizeof(message));
	if (r_msg == NULL) {
		perror("Communication: failed to get Space for Receive Message.");
		return false;
	}
	if (-1 == MsgSend(coid, msg_s, sizeof(msg_s), r_msg, sizeof(r_msg))) {
		perror("Communication: failed to send message to server,");
	}
	if (r_msg->ca != OK) {
		perror("Communication: no OK from Receiver!");
		return false;
	}
	std::list<Communicator>::iterator it = getCommunicatorForObject(id,0);
	if(it == NULL){
		return false;
	}else{
		(*it).setConnectID(coid);
		return true;
	}
}

bool Communication::detachConnection(int id,int coid){
	message * msg_s = (message *) malloc(sizeof(message));
	if (msg_s == NULL) {
		perror("Communication: failed to get Space for Message.");
		return false;
	}
	if (-1 == buildMessage(msg_s, id, coid, closeConnection, 0)) {
		perror("Communication: failed to create Message!");
		return false;
	}
	message * r_msg = (message*) malloc(sizeof(message));
	if (r_msg == NULL) {
		perror("Communication: failed to get Space for Receive Message.");
		return false;
	}
	if (-1 == MsgSend(coid,msg_s,sizeof(msg_s),r_msg,sizeof(r_msg))){
		perror("Communication: failed to send message to server,");
	}
	if(r_msg->ca != OK){
		perror("Communication: no OK from Receiver!");
		return false;
	}
	if (ConnectDetach(coid) == -1) {
		perror("Communication: failed to attach Channel for Interrupt\n");
		return false;
	}
	return true;
}

bool Communication::destroyChannel(int id){
	if (ChannelDestroy(id) == -1) {
		perror("Communication: failed to attach Channel for Interrupt\n");
		return false;
	}
	return true;
}

int Communication::buildMessage(void *s, int chid, int coid, MsgType activity,int mw){
	message *m =  (message*) s;
	(*m).chid = chid;
	(*m).coid = coid;
	(*m).ca =  activity;
	(*m).Msg.messwert =  mw;
	return 1;
}

int Communication::buildMessage(void *s, int chid, int coid, MsgType activity,CommunicatorType c){
	message *m =  (message*) s;
	(*m).chid = chid;
	(*m).coid = coid;
	(*m).ca =  activity;
	(*m).Msg.comtype = c;
	return 1;
}
int buildMessage(void *s, int chid, int coid, MsgType activity, struct _pulse p) {
	message *m = (message*) s;
	(*m).chid = chid;
	(*m).coid = coid;
	(*m).ca = activity;
	(*m).Msg.puls = p;
	return 1;
}
