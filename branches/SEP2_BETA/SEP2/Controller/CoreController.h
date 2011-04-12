/*
 * MasterThread.h
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#ifndef CORECONTROLLER_H_
#define CORECONTROLLER_H_


#include "../HAL/HAL.h"
#include "../HAL/IHAL.h"
#include "../Lampen/Lampen.h"
#include "../Tests/Test_HAL.h"
#include "../Tests/Test_M1.h"
#include "../Thread/HAWThread.h"
#include "InterruptController.h"

class CoreController : public thread::HAWThread, public IHAL{
public:
	void stopProcess();
    static CoreController* getInstance();

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
	virtual bool attachISR(void * arg);
	virtual int getSetInterrupt();
	virtual int getInterrupt();
	virtual bool resetAllOutPut();
	virtual bool removeLight(Color col);
	virtual bool addLight(Color col);
	virtual bool shine(Color col);

	void emergencyStop();
	void stopMachine();
	void restart();
	void resetAll();


private:
	CoreController();
	~CoreController();
	CoreController(const CoreController&);
	CoreController& operator=(const CoreController&);
	static CoreController* pInstance;
	static Mutex singleton;
    static Mutex m;
protected:
    virtual void execute(void*);
    virtual void shutdown();
};

#endif /* CORECONTROLLER_H_ */
