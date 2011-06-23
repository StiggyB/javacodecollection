
#ifndef INTERRUPTCONTROLLER_H_
#define INTERRUPTCONTROLLER_H_

#include "Communication.h"
#include "../HAL/Lampen.h"
#include "../HAL/HALCore.h"
#include "../Thread/Mutex.h"
#include "../Thread/HAWThread.h"
#include "../Thread/Singleton_T.h"


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
class InterruptController : public thread::HAWThread, public Communication, public Singleton_T<InterruptController> {
	friend class Singleton_T<InterruptController>;
private:
	/**
	 * ID's for Interrupt, Channel and Connection.
	 */
	int interruptId,interruptChannelId,interruptCoid;
	/**
	 * Pulse which will be send between HAL and InterruptController.
	 */
	struct _pulse pulse;
	/**
	 * Activates all necessary interrupts.
	 */
	void activateInterrupts();
	/**
	 * Connects the InterruptController to the HAL and the ISR.
	 */
	void connectToHAL();
	/**
	 * Disconnects the InterruptController from the HAL and the ISR.
	 */
	void disconnectFromHAL();
protected:
	virtual void execute(void*);
	virtual void shutdown();
	virtual void handlePulsMessage();
	virtual void handleNormalMessage();
private:
	InterruptController();
	virtual ~InterruptController();
	InterruptController(const InterruptController&);
	InterruptController& operator=(const InterruptController&);
	/**
	 * Direct connection to HALCore.
	 */
	HALCore *h;
	/**
	 * pointer to the ISR message
	 */
	Message *msg;
	/**
	 * Connection Id´s for the message passing.
	 */
	int coid, id;
};

#endif /* INTERRUPTCONTROLLER_H_ */
