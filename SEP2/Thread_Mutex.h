/*
 * Mutex.h
 *
 *  Created on: 31.03.2011
 *      Author: Administrator
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

class Mutex {

public:
	Mutex();
	virtual ~Mutex();
	void lock();
	void unlock();
private: pthread_mutex_t mutex;
	//Mutex (const Mutex &);
	//void operator= (const Mutex &);
};

#endif /* MUTEX_H_ */
