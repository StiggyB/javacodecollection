
#ifndef COMMUNICATION_SERVER_H_
#define COMMUNICATION_SERVER_H_

#include <stdlib.h>
#include "../Thread/Mutex.h"
#include "../Thread/HAWThread.h"
#include "../Thread/Singleton_T.h"
#include "Communication.h"

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
protected:
    virtual void execute(void*);
    virtual void shutdown();
};

#endif /* COMMUNICATION_SERVER_H_ */
