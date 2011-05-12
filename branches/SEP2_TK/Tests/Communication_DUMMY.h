/*
 * Communication_DUMMY.h
 *
 *  Created on: 12.05.2011
 *      Author: aaw253
 */

#ifndef COMMUNICATION_DUMMY_H_
#define COMMUNICATION_DUMMY_H_

#include "../Thread/HAWThread.h"
#include "Communication.h"


/**
 * Communication_DUMMY
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * DUMMY to test classes which implements Communication and sends pulses
 *
 *
 * Inherits: HAWThread.h
 */

class Communication_DUMMY : public thread::HAWThread, public Communication{

public:
	Communication_DUMMY();
	virtual ~Communication_DUMMY();

protected:
	virtual void execute(void*);
	virtual void shutdown();
	void handlePulsMessage();
	void handleNormalMessage();
private:
	Message *msg;
	int coid, id;
};

#endif /* COMMUNICATION_DUMMY_H_ */
