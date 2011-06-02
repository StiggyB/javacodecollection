/*
 * Semaphore.h
 *
 *  Created on: 02.05.2011
 *      Author: Administrator
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

#include <semaphore.h>
#include <malloc.h>
#include <stdio.h>

class Semaphor {
public:
	Semaphor();
	virtual ~Semaphor();
	int init(int value);
	int wait();
	int post();
	int destroy();
private:
	sem_t * sema;
};

#endif /* SEMAPHOR_H_ */
