
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
	getIDforCom, react,reactC, information, OK, notAvailable, sendID, error
};

typedef struct message{
	int chid;
	int coid;
	MsgType ca;
	struct sigevent event;
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
	int getConnectIdForObject(CommunicatorType c);
	int requestChannelIDForObject(CommunicatorType c);
	bool addCommunicator(int ch, int cod, CommunicatorType ct);
	bool removeCommunicator(int ch, int cod,  CommunicatorType ct);
	bool setUpChannel();
	bool registerChannel();
	bool destroyChannel(int id);
	bool deregisterChannel();
	bool attachConnection(int id, CommunicatorType c);
	bool detachConnection(int id,int coid);
	int buildMessage(void *s, int chid, int coid, MsgType activity,int mw);
	int buildMessage(void *s, int chid, int coid, MsgType activity,CommunicatorType c);
	int buildMessage(void *s, int chid, int coid, MsgType activity,struct _pulse p);
	/**
	 * CoreController ChannelID
	 */
	static volatile int serverChannelId;

	Communication();
	virtual ~Communication();
private:
	class Communicator {
	public:
		Communicator(int id, int cod, CommunicatorType c) {
			chid = id;
			coid = cod;
			cm = c;
		}
		~Communicator() {
		}
		CommunicatorType getCom() {
			return cm;
		}
		int getChannelID() {
			return chid;
		}
		int getConnectID() {
			return coid;
		}
		void setConnectID(int co) {
			coid = co;
		}
	private:
		int chid;
		int coid;
		CommunicatorType cm;
	};


	std::list<Communicator> lst;
protected:
	int chid, coid;
public:
	std::list<Communicator>::iterator getCommunicatorForObject(int ci,int co);
};

#endif /* COMMUNICATION_H_ */
