/*
 * MasterThread.cpp
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#include "MasterThread.h"

Lampen l;

MasterThread::MasterThread() {

}

MasterThread::~MasterThread() {

}

void MasterThread::execute(void*){
	HAL::getInstance();
	l.start(NULL);
	Sensor s;
	s.start(NULL);
	l.join();
}

void MasterThread::shutdown(){

}

void MasterThread::stopProcess(){
	l.stop();
	HAL* h = HAL::getInstance();
	(*h).resetAllOutPut();
}
