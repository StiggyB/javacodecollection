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
 * and register/unregister themself.
 *
 */

#include "CommunicationServer.h"


CommunicationServer::CommunicationServer(): id(0){

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
		cleanUp(0, m, r_msg);
		perror("CommunicationServer: failed to get Space for Message!");
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
			MsgReply(rcvid, 0, m, sizeof(m));
		}
		cleanUp(0, m, NULL);
		destroyChannel(chid);
	}else{
		perror("CommunicationServer: SettingUp failed!");
	}
}

void CommunicationServer::handleMessage() {
	MsgType ca  = OK;
	int id = m->m.chid;
	switch (m->m.ca) {
	case addToServer:
		addCommunicator(m->m.chid, m->m.coid, m->m.comtype);
		break;
	case removeFromServer:
		removeCommunicator(m->m.chid, m->m.coid, m->m.comtype);
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
}

void CommunicationServer::shutdown() {

}