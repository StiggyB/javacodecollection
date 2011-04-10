/*
 * Lampen.cpp
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#include "Lampen.h"

extern CoreController* cc;

Lampen::Lampen() {
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "Lampen: Error for IO Control" << std::endl;
	}
	cc = CoreController::getInstance();
}

Lampen::~Lampen() {
	cc = NULL;
}

void Lampen::execute(void*) {
	//TODO
}


void Lampen::shutdown() {
	cout << "Test beendet" << endl;
}

void Lampen::flash(int time, Color color) {
	//TODO
}

void Lampen::flash(int time, int duration, Color col) {
	//TODO
}

void Lampen::addLight(Color col) {
	(*cc).addLight(col);
}

void Lampen::removeLight(Color col) {
	(*cc).removeLight(col);
}
void Lampen::shine(Color col) {
	(*cc).shine(col);
}

