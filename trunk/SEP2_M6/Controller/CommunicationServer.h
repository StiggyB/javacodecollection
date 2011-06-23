
#ifndef COMMUNICATION_SERVER_H_
#define COMMUNICATION_SERVER_H_

#include <stdlib.h>
#include "Communication.h"
#include "../Thread/Mutex.h"
#include "../Thread/HAWThread.h"
#include "../Thread/Singleton_T.h"


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
 * Starts the threads. Implements Singleton-Pattern.
 *
 * Upcoming: Other parts can get their necessary ChannelID's.

 * Liste für die channelid's der Prozesse
 * funktion um channelid zu registrieren
 * funktion um channelid zu erfragen
 *
 */
class CommunicationServer : public thread::HAWThread, public Communication, public Singleton_T <CommunicationServer>{
	friend class Singleton_T<CommunicationServer>;
private:
	CommunicationServer();
	~CommunicationServer();
	/**
	 * Sets up the CommunicationServer as the Communication Server
	 */
	bool settingUpCommunicationServer();
	virtual void handlePulsMessage();
	virtual void handleNormalMessage();
	int id;
protected:
    virtual void execute(void*);
    virtual void shutdown();
};

#endif /* COMMUNICATION_SERVER_H_ */
