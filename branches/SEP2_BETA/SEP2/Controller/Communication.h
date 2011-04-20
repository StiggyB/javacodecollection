
#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <list>
#include <iostream>
#include <stdlib.h>
#include "HAL.h"

enum CommunicatorType{
	INTERRUPTCONTROLLER, SENSOR, LIGHTS, ANLAGENSTEUERUNG,CORECONTROLLER
};

enum MsgType{
	addToServer,removeFromServer,closeConnection,startConnection,
	getIDforCom, react, information, OK, notAvailable, sendID, error
};

typedef struct message{
	int chid;
	int coid;
	MsgType ca;
	union msg{
		int messwert;
		CommunicatorType comtype;
		//more can be added here!
	} Msg;
} Message;

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
 *
 * UNDER CONSTRUCTION!!!
 */
class Communication {

public:
	/**
	 * Get the ChannelID of the specified component.
	 * \param c the specified component.
	 * \return ChannelID
	 */
	int getChannelIdForObject(CommunicatorType c);
	int requestChannelIDForObject(CommunicatorType c);
	bool setUpChannel();
	bool registerChannel();
	bool destroyChannel(int id);
	bool deregisterChannel();
	bool attachConnection(int id, CommunicatorType c);
	bool detachConnection(int id);
	bool addCommunicator(int ch, CommunicatorType ct);
	bool removeCommunicator(int ch, CommunicatorType ct);
	int buildMessage(void *s, int chid, int coid, MsgType activity,int mw);
	int buildMessage(void *s, int chid, int coid, MsgType activity,CommunicatorType c);
	/**
	 * CoreController ChannelID
	 */
	static volatile int serverChannelId;

	Communication();
	virtual ~Communication();
private:
	class Communicator{
		public:
			Communicator(int id,CommunicatorType c){
				chid = id;
				cm = c;
			}
			~Communicator(){}
			CommunicatorType getCom(){
				return cm;
			}
			int getChannelID(){
				return chid;
			}
		private:
			int chid;
			CommunicatorType cm;
		};


	std::list<Communicator> lst;
	std::list<int> connections;
protected:
	int chid, coid;
};

#endif /* COMMUNICATION_H_ */
