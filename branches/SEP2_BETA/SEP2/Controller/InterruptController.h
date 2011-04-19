
#ifndef INTERRUPTCONTROLLER_H_
#define INTERRUPTCONTROLLER_H_


#include "../HAL/HAL.h"
#include "../Thread/HAWThread.h"
#include "../Thread/Singleton.h"

extern struct sigevent event;
//extern const struct sigevent *eventptr;

/**
 * Interrupt Controller
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Capsules many functions for Interrupts using Pulse Messages.
 *
 *
 * Inherits: HAWThread.h
 */

class InterruptController : public thread::HAWThread, public Singleton {
public:
	//static void deleteInstance();
	//static InterruptController* getInstance();

	InterruptController();
	virtual ~InterruptController();
private:
	/**
	 * ID's for Interrupt, Channel and Connection.
	 */
	int interruptId, chid, coid;
	/**
	 * Pulse which will be send between HAL and InterruptController.
	 */
	struct _pulse pulse;
	/**
	 * Waits for PulseMessages from HAL, sending them to Sensor.
	 */
	void handlePulseMessages();
	/**
		 * Activates all necessary interrupts.
		 */
	void activateInterrupts();
	/**
	 * Connects the InterruptController to the HAL on specified ports.
	 * \param port an integer, the port which should be connected to the ISR.
	 */
	void connectToHAL(int port);
	/**
	 * Gets the Sensor, to send them the interrupts.
	 */
	void getSensor();
	/**
	 * Direct connection to HAL.
	 */
	HAL *h;



protected:
	virtual void execute(void*);
	virtual void shutdown();

private:


};

#endif /* INTERRUPTCONTROLLER_H_ */
