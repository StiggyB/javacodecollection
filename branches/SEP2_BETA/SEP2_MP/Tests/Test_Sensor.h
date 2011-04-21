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
#include "../Controller/CoreController.h"
#include "../Thread/HAWThread.h"

class Test_Sensor : public thread::HAWThread {
public:
	Test_Sensor();
	virtual ~Test_Sensor();
	virtual void execute(void*);
	virtual void shutdown();
	void test_Software_Only();
	void test_Operator_Included();
	bool test_print(int sen_no, int res, int port, int state);


private:
	CoreController *cc;
};


#endif /* _TEST_SENSOR_H_ */
