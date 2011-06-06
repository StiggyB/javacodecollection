/*
 * Condition.h
 *
 *  Created on: 01.05.2011
 *      Author: MQR
 */

#ifndef CONDITION_H_
#define CONDITION_H_
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Mutex.h"

class Condition {
public:
	Condition();
	virtual ~Condition();
	void destroy();
	void setMutex(Mutex *m);
	int wait();
	int signal();
	int broadcast();
private:
	pthread_cond_t *condvar;
	bool destroyed;
	Mutex *mut;
};

#endif /* CONDITION_H_ */
