
#ifndef CORECONTROLLER_H_
#define CORECONTROLLER_H_


#include "../HAL/HAL.h"
#include "../HAL/IHAL.h"
//#include "InterruptController.h"
#include "../Thread/HAWThread.h"

/**
 * Core Controller
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Capsulates many functions for the direct
 * in- and output from and to the Festo Transfersystem and
 * with Interrupts using Pulse Messages.
 * Starts the threads. Implements Singleton-Pattern.
 *
 * Upcoming: Other parts can get their necessary ChannelID's.

 * Liste für die channelid's der Prozesse
 * funktion um channelid zu registrieren
 * funktion um channelid zu erfragen
 *
 * Inherits: IHAL.h, HAWThread.h
 */
class CoreController : public thread::HAWThread, public IHAL{//, public Communication{
public:
	void stopProcess();
    static CoreController* getInstance();
    static void deleteInstance();
    //IHAL:
	virtual int read(int dir);
	virtual bool isInput(int dir);
	virtual bool isOutput(int dir);
	virtual int write(int dir, int value);
	virtual int reset(int dir, int value);
	virtual bool engineStart(int direction);
	virtual bool openSwitch();
	virtual bool closeSwitch();
	virtual bool setSwitchDirection(bool dir);
	virtual bool engineReset();
	virtual bool engineStop();
	virtual bool engineContinue();
	virtual bool engineRight();
	virtual bool engineLeft();
	virtual bool engineSlowSpeed();
	virtual bool engineNormalSpeed();
	virtual bool engineStopped();
	virtual bool engineSlowSpeed(int dir);
	virtual bool engineSpeed(bool slow);
	virtual bool engineSlowLeft();
	virtual bool engineSlowRight();
	virtual int getSetInterrupt();
	virtual int getInterrupt();
	virtual bool resetAllOutPut();
	virtual bool removeLight(Color col);
	virtual bool addLight(Color col);
	virtual bool shine(Color col);
	virtual float getHeight();

	/**
	 * Performes an emergency stop.
	 */
	void emergencyStop();
	/**
	 * Stops the machine.
	 */
	void stopMachine();
	/**
	 * Restarts the machine.
	 */
	void restart();
	/**
	 * Resets all hardware and software.
	 */
	void resetAll();


private:
	CoreController();
	~CoreController();
	/**
	 * for Singleton
	 */
	CoreController(const CoreController&);
	CoreController& operator=(const CoreController&);
	/**
	 * Pointer for singleton CoreController
	 */
	static CoreController* pInstance;
	/**
	 * Pointer for singleton CoreController Instance
	 */
	static Mutex singleton;
    /**
     * Mutex to ensure threadsafety
     */
	static Mutex m;
	/**
	 *
	 */
	HAL* h;
protected:
    virtual void execute(void*);
    virtual void shutdown();
};

#endif /* CORECONTROLLER_H_ */
