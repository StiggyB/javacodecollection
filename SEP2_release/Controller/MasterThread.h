/*
 * MasterThread.h
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#ifndef MASTERTHREAD_H_
#define MASTERTHREAD_H_



#include "../HAL/HAL.h"
#include "../Lampen/Lampen.h"
#include "../Thread/HAWThread.h"
#include "../Controller/Sensor.h"

class MasterThread : public thread::HAWThread{
public:
	MasterThread();
	virtual ~MasterThread();
	void stopProcess();
    virtual void execute(void*);
    virtual void shutdown();

};

#endif /* MASTERTHREAD_H_ */
