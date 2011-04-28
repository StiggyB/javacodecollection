
#ifndef SENSOR_H_
#define SENSOR_H_


#include "CoreController.h"
//#include "InterruptController.h"
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
//class CoreController;

class Sensor : public thread::HAWThread{
public:
	/**
	 * Deal with the Interrupt for given port.
	 * \param port an integer representing the given port.
	 */
	void interrupt(int port);
	Sensor();
	virtual ~Sensor();
protected:
	virtual void execute(void*);
	virtual void shutdown();
private:
	CoreController *cc;
#ifdef TEST_SEN
	//cout << "ts" << endl;
	Test_Sensor ts;
#endif

};

#endif /* SENSOR_H_ */
