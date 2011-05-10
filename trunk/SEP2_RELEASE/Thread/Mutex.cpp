/**
 * Mutex
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Mutex for a threadsafe implementation.
 *
 */

#include "Mutex.h"

Mutex::Mutex() {
	pthread_mutex_init(&mutex,NULL);
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
