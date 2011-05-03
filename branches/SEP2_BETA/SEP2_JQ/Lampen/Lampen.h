
#ifndef LAMPEN_H_
#define LAMPEN_H_

#include <unistd.h>
#include "../HAL/HALCore.h"
#include "../Thread/HAWThread.h"
#include "../Controller/Communication.h"
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
class Lampen : public thread::HAWThread{
public:
	Lampen();
	virtual ~Lampen();
	/**
	 * Flashes a specified light until stopped.
	 * \param time an integer, half of the flash period.
	 * \param color Color of the Light which should flash.
	 */
	void flash(int time, Color color);
	/**
	 * Flashes a specified light until duration expired.
	 * \param time an integer, half of the flash period.
	 * \param duration an integer, specifies how long the light should flash
	 * \param col Color of the Light which should flash.
	 */
	void flash(int time, int duration, Color col);
	/**
	 * Removes a certain light.
	 * \param col specifies the color of the light.
	 */
	void removeLight(Color col);
	/**
	 * Adds a certain light.
	 * \param col specifies the color of the light.
	 */
	void addLight(Color col);
	/**
	 * Adds a certain light.
	 * Equals void addLight(Color col);
	 * \param col specifies the color of the light.
	 */
	void shine(Color col);
protected:
	virtual void execute(void*);
	virtual void shutdown();
private:
	/**
	 * Bool to ensure the flashing of the Light.
	 */
	bool running;
	HALCore *h;
};

#endif /* LAMPEN_H_ */
