/**
 * CommunicationServer
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Other parts can get their necessary ChannelID's
 * and register/unregister themselves.
 *
 */

#include "CommunicationServer.h"


CommunicationServer::CommunicationServer(): id(0){
	mine = COMMUNICATIONCONTROLLER;
}

CommunicationServer::~CommunicationServer() {

}

bool CommunicationServer::settingUpCommunicationServer(){
	if(!setUpChannel()){
		perror("CommunicationServer: channel setup failed");
		return false;
	}else{
		cout << "CommunicationServer: channel setup successful" << endl;
	}
	if (!allocMessages()) {
		perror("CommunicationServer: failed to get Space for Message!");
		cleanUp(0, m, r_msg);
		destroyChannel(chid);
		return false;
	}
	Communication::serverChannelId = chid;
	return true;
}

void CommunicationServer::execute(void*) {
	if (settingUpCommunicationServer()) {
		while (!isStopped()) {
			rcvid = MsgReceive(chid, m, sizeof(Message), NULL);
			handleMessage();
		}
		cleanUp(0, m, NULL);
		destroyChannel(chid);
	}else{
		perror("CommunicationServer: SettingUp failed!");
	}
}
void CommunicationServer::handlePulsMessage(){
	std::cout << "CommunicationSeerver: received a Pulse Message but doesn't know what to do!"<<std::endl;
}

void CommunicationServer::handleNormalMessage() {
	MsgType ca  = OK;
	int id = m->m.chid;
	switch (m->m.ca) {
	case addToServer:
		addCommunicator(m->m.chid, m->m.coid, m->m.wert,m->m.comtype);
		break;
	case removeFromServer:
		removeCommunicator(m->m.wert);
		break;
	case getIDforCom:
		if ((id = getChannelIdForObject(m->m.comtype)) == -1) {
			ca = error;
		}
		break;
	default:
		cout << "CommunicationServer: defaultError" << endl;
		ca = error;
		break;
	}
	buildMessage(m, id, m->m.coid, ca, COMMUNICATIONCONTROLLER);
	MsgReply(rcvid, 0, m, sizeof(m));
}

void CommunicationServer::shutdown() {
	cleanCommunication();
}
