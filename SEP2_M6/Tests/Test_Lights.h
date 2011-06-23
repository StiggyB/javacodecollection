
#ifndef TEST_LIGHTS_H_
#define TEST_LIGHTS_H_

#include "../HAL/Lampen.h"
#include "../HAL/HALCore.h"
#include "../Thread/HAWThread.h"

/**
 * Testing Class for Lights
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Prepares some Testing stuff for the Lights.
 *
 * Inherits: thread::HAWThread
 */
class Test_Lights : public thread::HAWThread{
public:
	Test_Lights();
	virtual ~Test_Lights();
protected:
	virtual void execute(void*);
	virtual void shutdown();
private:
	HALCore *h;
	Lampen *l;
};

#endif /* TEST_LIGHTS_H_ */
