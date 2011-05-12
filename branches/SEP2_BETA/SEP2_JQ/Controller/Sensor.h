
#ifndef SENSOR_H_
#define SENSOR_H_


#include "../Thread/HAWThread.h"
#include "../HAL/HALCore.h"
#include "Communication.h"
/**
 * Sensor
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Milestone 3: HAL Sensorik
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Class which deals with the interrupts.
 *
 */

class Sensor : public thread::HAWThread, public Communication{
public:
	/**
	 * Deal with the Interrupt for given port.
	 * \param port an integer representing the port where an interrupt occures.
	 * \param val an integer representing the value of the interrupts.
	 */
	void interrupt(int port, int val);
	Sensor();
	virtual ~Sensor();
protected:
	virtual void execute(void*);
	virtual void shutdown();
	virtual void handlePulsMessage();
	virtual void handleNormalMessage();
	void clean();
private:
	/**
	 * Pointer to the Singleton Core Controller
	 */
	HALCore *h;
	/**
	 *  Sets up the Communication to IC and waits for Messages from it.
	 */
	bool settingUpSensor();
	/**
	 *  Sets up the Communication to IC and waits for Messages from it.
	 */
	void cleanUpSensor();
	//DEBUG
	int cnt;
	int p,id,coid;
};

#endif /* SENSOR_H_ */
