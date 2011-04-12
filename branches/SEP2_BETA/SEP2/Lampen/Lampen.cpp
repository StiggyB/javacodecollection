/**
 * Light Control
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Provides some possibilities to activate the lights.
 *
 * Inherits: HAWThread, Communication
 */

#include "Lampen.h"

extern CoreController* cc;

Lampen::Lampen() {
	/**
	 * gaining IO privileges
	 */
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "Lampen: Error for IO Control" << std::endl;
	}
	/**
	 * gets a pointer to an instance of the CoreController
	 */
	if(cc == NULL) cc = CoreController::getInstance();
	running = false;
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

/**
 * Flashes a specified light until stopped.
 * \param time an integer, half of the flash period.
 * \param color Color of the Light which should flash.
 */
void Lampen::flash(int time, Color color) {
	running = true;
	while(running){
		(*cc).addLight(color);
		sleep(time);
		(*cc).removeLight(color);
		sleep(time);
	}
}

/**
 * Flashes a specified light until duration expired.
 * \param time an integer, half of the flash period.
 * \param duration an integer, specifies how long the light should flash
 * \param col Color of the Light which should flash.
 */
void Lampen::flash(int time, int duration, Color col) {
	if(time > 0 && duration > 0){
	int elapsedTime = 0;
		running = true;
		while (running && elapsedTime < duration) {
			(*cc).addLight(col);
			elapsedTime += time;
			sleep(time);
			(*cc).removeLight(col);
			elapsedTime += time;
			sleep(time);
		}
	}
}

/**
 * Adds a certain light.
 * \param col specifies the color of the light.
 */
void Lampen::addLight(Color col) {
	(*cc).addLight(col);
}

/**
 * Removes a certain light.
 * \param col specifies the color of the light.
 */
void Lampen::removeLight(Color col) {
	(*cc).removeLight(col);
}

/**
 * Adds a certain light.
 * Equals void Lampen::addLight(Color col);
 * \param col specifies the color of the light.
 */
void Lampen::shine(Color col) {
	(*cc).shine(col);
}

