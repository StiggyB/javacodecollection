#ifndef _TEST_SENSOR_H_
#define _TEST_SENSOR_H_

/**
 * Test_Sensor
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Tests the sensor system.
 *
 *
 * Inherits: Sensor.h
 */

#include "../Controller/Sensor.h"

class Test_Sensor : public thread::HAWThread {
public:
	Test_Sensor();
	virtual ~Test_Sensor();


};


#endif /* _TEST_SENSOR_H_ */
