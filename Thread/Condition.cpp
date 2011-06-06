/*
 * Condition.cpp
 *
 *  Created on: 01.05.2011
 *      Author: MQR
 */

#include "Condition.h"

Condition::Condition() : destroyed(false) {
	condvar = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
	if(NULL == condvar){
		perror("Condition: Couldn't get Space for CondVar!");
	}
	if(0 != pthread_cond_init(condvar,NULL)){
		perror("Condition: Couldn't init CondVar!");
	}

}

Condition::~Condition() {
	destroy();
}

void Condition::destroy(){
	if(!destroyed){
		if(0 != pthread_cond_destroy(condvar)){
			perror("Condition: Couldn't destroy condvar!");
		}
		free(condvar);
		destroyed = true;
	}
}

void Condition::setMutex(Mutex *m){
	mut = m;
}

int Condition::wait(){
	int i = 0;
	if(mut == NULL){
		i = -1;
	}else{
		i = pthread_cond_wait(condvar,mut->getMutex());
	}
	return i;
}

int Condition::signal(){
	return pthread_cond_signal(condvar);
}
int Condition::broadcast(){
	return pthread_cond_broadcast(condvar);
}
