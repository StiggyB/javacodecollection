#ifndef TEST_M1_H_
#define TEST_M1_H_

#include "../Thread/HAWThread.h"
#include "../HAL/HALCore.h"
/**
 * Testing Class for Milestone #1
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Tests the Lights and some other hardware stuff.
 * 1.  Add lights after another.
 * 2.  Turn lights off instantly.
 * 3.  Add lights after another.
 * 4.  Turn off lights one at a time.
 * 5.  Turning on engine in right direction.
 * 6.  Turning on engine in left direction.
 * 7.  Slowing the engine.
 * 8.  Getting back to Normal Speed.
 * 8.  Stopping the engine.
 * 9.  Setting the engine to slow and left direction.
 * 10. Switching to slow in right direction.
 * 11. Opening the switch.
 * 12. Closing the switch.
 * 13. Resetting the hardware.
 *
 * Inherits: thread::HAWThread
 */
class Test_M1 : public thread::HAWThread {
public:
	Test_M1();
	virtual ~Test_M1();
protected:
	virtual void execute(void*);
	virtual void shutdown();
private:
	HALCore *h;
};

#endif /* TEST_M1_H_ */
