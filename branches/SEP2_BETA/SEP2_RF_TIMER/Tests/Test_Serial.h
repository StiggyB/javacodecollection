
#ifndef TEST_SERIAL_H_
#define TEST_SERIAL_H_
#define DEBUG_SERIAL

#include "../Thread/HAWThread.h"
#include "../Serial/Serial.h"
#include "../Controller/Communication.h"
#include "../HAL/HALCore.h"


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

protected:
	virtual void execute(void*);
	virtual void shutdown();
	void clean();
private:
	Serial *s_0;
	Serial *s_1;
	int msg_test;
	bool test_successful;
};

#endif /* TEST_IRQ_H_ */
