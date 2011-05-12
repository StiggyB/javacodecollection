
#ifndef TEST_SERIAL_H_
#define TEST_SERIAL_H_
#define DEBUG_SERIAL

#include "../Thread/HAWThread.h"
#include "../Serial/Serial.h"
#include "Communication_DUMMY.h"

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
class Test_Serial : public thread::HAWThread{
public:
	Test_Serial();
	virtual ~Test_Serial();

protected:
	virtual void execute(void*);
	virtual void shutdown();

private:
	Serial *s_0;
	Serial *s_1;
	Communication_DUMMY *dummy;

};

#endif /* TEST_IRQ_H_ */
