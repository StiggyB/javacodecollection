
#ifndef TEST_SERIAL_H_
#define TEST_SERIAL_H_
#define DEBUG_SERIAL

#include "../Serial/Serial.h"
#include "../Thread/HAWThread.h"
#include "../Controller/Communication.h"

/**
 * Testing Class for IRQ
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Prepares some Testing stuff for the Interrupts.
 *
 * Inherits: thread::HAWThread
 */

class Test_Serial : public thread::HAWThread, public Communication{
public:
	Test_Serial();
	virtual ~Test_Serial();

	void handlePulsMessage();
	void handleNormalMessage();
	Serial *serial;

protected:
	virtual void execute(void*);
	virtual void shutdown();
	void clean();
private:
	int msg_test;
	bool testSuccessful;
	int testCnt;
	bool isStopped;
};

#endif /* TEST_IRQ_H_ */
