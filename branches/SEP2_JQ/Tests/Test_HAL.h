
#ifndef TEST_HAL_H_
#define TEST_HAL_H_

#include "../Thread/HAWThread.h"
#include "../HAL/HALCore.h"

/**
 * Testing Class for Milestone #2 - HAL
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Tests the Lights and some other hardware stuff.
 * 1.  Testing the Direction of the Ports.
 * 2.  Turning on engine in right direction.
 * 3.  Ask engine direction.
 * 4.  Turning on engine in left direction.
 * 5.  Turning on engine in right direction.
 * 6.  Turning on engine in left direction.
 * 7.  Turn off lights one at a time.
 * 8.  Slowing the engine.
 * 9.  Getting back to Normal Speed.
 * 10.  Slowing the engine.
 * 11.  Getting back to Normal Speed.
 * 12.  Turning on engine in right direction.
 * 13.  Turning on engine in left direction.
 * 14.  Slowing the engine.
 * 15.  Getting back to Normal Speed.
 * 16.  Stopping the engine.
 * 17.  Starting the engine again.
 * 18.  Setting the engine to slow and left direction.
 * 19. Switching to slow in right direction.
 * 20. Resetting the engine.
 * 21. Opening the switch.
 * 22. Closing the switch.
 * 23. Opening the switch.
 * 24. Closing the switch.
 * 25. Resetting the hardware.
 *
 * Inherits: thread::HAWThread
 */

class Test_HAL : public thread::HAWThread {
public:
	Test_HAL();
	virtual ~Test_HAL();
protected:
	virtual void execute(void*);
	virtual void shutdown();
private:
	HALCore *h;
};

#endif /* TEST_HAL_H_ */
