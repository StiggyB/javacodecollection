
#ifndef TEST_IRQ_H_
#define TEST_IRQ_H_

#include "../Thread/HAWThread.h"
#include "../Controller/CoreController.h"

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
class Test_IRQ : public thread::HAWThread{
public:
	Test_IRQ();
	virtual ~Test_IRQ();
protected:
	virtual void execute(void*);
	virtual void shutdown();
private:
	CoreController *cc;
};

#endif /* TEST_IRQ_H_ */
