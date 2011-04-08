/*
 * MasterThread.h
 *
 *  Created on: 07.04.2011
 *      Author: Administrator
 */

#ifndef MASTERTHREAD_H_
#define MASTERTHREAD_H_

#include "Thread_HAWThread.h"

class MasterThread: public thread::HAWThread {
public:
	MasterThread();
	virtual ~MasterThread();
};

#endif /* MASTERTHREAD_H_ */
