/*
 * Mutex.cpp
 *
 *  Created on: 31.03.2011
 *      Author: Administrator
 */

#include "Mutex.h"

Mutex::Mutex() {
	//mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&mutex,NULL);
	//Mutex(&mutex);
}

Mutex::~Mutex() {
	pthread_mutex_destroy(&mutex);
}

void Mutex::lock(){
	pthread_mutex_lock(&mutex);
}

void Mutex::unlock(){
	pthread_mutex_unlock(&mutex);
}

/*Mutex::Mutex (const Mutex &m){
	pthread_mutex_init(m,NULL);
}*/
