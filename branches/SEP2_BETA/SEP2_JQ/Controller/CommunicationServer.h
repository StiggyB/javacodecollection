
#ifndef COMMUNICATION_SERVER_H_
#define COMMUNICATION_SERVER_H_

#include <stdlib.h>
#include "../Thread/Mutex.h"
#include "../Thread/HAWThread.h"
#include "../Thread/Singleton_T.h"
#include "Communication.h"

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
//public:
	//static CommunicationServer* getInstance();
    //static void deleteInstance();
private:
	CommunicationServer();
	~CommunicationServer();
	/**
	 * for Singleton
	 */
	//CommunicationServer(const CommunicationServer&);
	//CommunicationServer& operator=(const CommunicationServer&);
	/**
	 * Pointer for singleton CommunicationServer
	 */
	//static CommunicationServer* pInstance;
	/**
	 * Pointer for Mutex to keep singleton threadsafe
	 */
	//static Mutex singleton;
	/**
	 * Sets up the CommunicationServer as the Communication Server
	 */
	void serveAsCommunicationServer();
protected:
    virtual void execute(void*);
    virtual void shutdown();
};

#endif /* COMMUNICATION_SERVER_H_ */
