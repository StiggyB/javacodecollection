
#ifndef INTERRUPTCONTROLLER_H_
#define INTERRUPTCONTROLLER_H_


#include "../HAL/HAL.h"
#include "../Thread/Mutex.h"
#include "../Thread/HAWThread.h"
#include "Communication.h"
#include "CoreController.h"

extern Message msg;
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

class InterruptController : public thread::HAWThread, public Communication{//, public Singleton {
public:
	static void deleteInstance();
	static InterruptController* getInstance();

	//InterruptController();
	//virtual ~InterruptController();
private:
	/**
	 * ID's for Interrupt, Channel and Connection.
	 */
	int interruptId;//, chid, coid;
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
	void connectToHAL();
	/**
	 * Gets the Sensor, to send them the interrupts.
	 */
	void getSensor();
protected:
	virtual void execute(void*);
	virtual void shutdown();

private:
	InterruptController();
	virtual ~InterruptController();
	InterruptController(const InterruptController&);
	InterruptController& operator=(const InterruptController&);
	/**
	 * Pointer for singleton CoreController
	 */
	static InterruptController* pInstance;
	/**
	 * Pointer for singleton CoreController Instance
	 */
	static Mutex singleton;
	/**
	 * Direct connection to HAL.
	 */
	HAL *h;
	CoreController *cc;
};

#endif /* INTERRUPTCONTROLLER_H_ */
