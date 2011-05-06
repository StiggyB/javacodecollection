
#ifndef SENSOR_H_
#define SENSOR_H_


#include "Communication.h"
#include "CoreController.h"

#include "../Tests/test.h"
#include "../Tests/Test_Sensor.h"
#include "../Thread/HAWThread.h"


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
 * Inherits: HAWThread.h
 */

class Sensor : public thread::HAWThread, public Communication{
public:
	/**
	 * Deal with the Interrupt for given port.
	 * \param port an integer representing the port where an interrupt occures.
	 */
	void interrupt(int port, int val);
	Sensor();
	virtual ~Sensor();
protected:
	virtual void execute(void*);
	virtual void shutdown();
private:
	/**
	 * Pointer to the Singleton Core Controller
	 */
	CoreController *cc;
	/**
	 *  Sets up the Communication to IC and waits for Messages from it.
	 */
	void settingUpAndWaitingSensor();
	int cnt;

#ifdef TEST_SEN
	Test_Sensor ts;
#endif

};

#endif /* SENSOR_H_ */
