/*
 * Semaphore.cpp
 *
 *  Created on: 02.05.2011
 *      Author: Administrator
 */

#include "Semaphor.h"

Semaphor::Semaphor() {
	sema = (sem_t *) malloc(sizeof(sem_t));
	if(sema == NULL){
		perror("Semaphor: Failed to get Space for Semaphor!");
	}
}

Semaphor::~Semaphor() {
	destroy();
}

int Semaphor::init(int value){
	return sem_init(sema,0,value);
}

int Semaphor::wait(){
	return sem_wait(sema);
}

int Semaphor::post(){
	return sem_post(sema);
}

int Semaphor::destroy(){
	return sem_destroy(sema);
}
