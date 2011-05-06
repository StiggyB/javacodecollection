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

#include "CommunicationServer.h"

/*Mutex CommunicationServer::singleton;

CommunicationServer* CommunicationServer::pInstance = NULL;

CommunicationServer* CommunicationServer::getInstance() {
	if (!pInstance) {
		singleton.lock();
		if (!pInstance) {
			pInstance = new CommunicationServer;
		}
		singleton.unlock();
	}
	return pInstance;
}

void CommunicationServer::deleteInstance(){
	if( pInstance != NULL ){
		singleton.lock();
		if( pInstance != NULL ){
			delete pInstance;
			pInstance = NULL;
		}
		singleton.unlock();
	}
}
*/
CommunicationServer::CommunicationServer(){
}

CommunicationServer::~CommunicationServer() {
	//singleton.~Mutex();
}

void CommunicationServer::serveAsCommunicationServer(){
	int rcvid = 0,id = 0;
	if(!setUpChannel()){
		perror("CC: channel setup failed");
		return;
	}else{
		cout << "CC: channel setup successful" << endl;
	}
	Message *m = (Message *) malloc(sizeof(Message));
	if(m == NULL){
		perror("CommunicationServer: failed to get Space for Message!");
		destroyChannel(chid);
		return;
	}
	Communication::serverChannelId = chid;
	//TODO: Schleife ausgliedern
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
			cout << "CommunicationServer: defaultError"<<endl;
			buildMessage(m,(*m).m.chid,(*m).m.coid,error,CORECONTROLLER); break;
		}
		MsgReply(rcvid,0,m,sizeof(m));
	}
	cleanUp(0,m,NULL);
	destroyChannel(chid);
}

void CommunicationServer::execute(void*) {
	serveAsCommunicationServer();
}

void CommunicationServer::shutdown() {

}
