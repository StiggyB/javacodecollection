/*
 * Sensor.h
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#ifndef INTERRUPTCONTROLLER_H_
#define INTERRUPTCONTROLLER_H_


#include "../HAL/HAL.h"
#include "../Thread/HAWThread.h"

extern volatile struct sigevent event;
extern const struct sigevent *eventptr;

class InterruptController : public thread::HAWThread {
public:

	InterruptController();
	virtual ~InterruptController();

private:
	int interruptId, chid, coid;
	struct _pulse pulse;
	void handlePulseMessages();
	void activateInterrupts();
	void connectToHAL();
	HAL *h;

	/** TODO and questions:
	 * 	module for reading the value from Heightmeasurement
	 *  module for reading/using timer
	 *  setting up a real one core Controller?
	 *  all connections to the Hardware will be established over the controller?
	 *	--> interface will need to be brought all the way through the HAL into the controller
	 *	--> needs to be a singleton!
	 *	--> should the controller wait for messages from every one?
	 *		or should there be one only for Interrupts?
	 *	--> saving in controller all channel ids? so
	 * 		when you need the id of a specific thread you can get it from him.
	 * 		all Threads will send him a message when started.
	 *  --> if there is an thread for only interrupts -> use InterruptWait or MessageReceive?
	 *  --> how to create safepoints for the M-Versions? <--  *
	 */
protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* INTERRUPTCONTROLLER_H_ */
