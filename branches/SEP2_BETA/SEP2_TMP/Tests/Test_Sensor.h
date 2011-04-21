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
 * Software-Tests:
 *
 * Tests the light sensor 		B(0)
 * Tests the light sensor 		B(1)
 * Tests the height-measure 	B(2)
 * Tests the light sensor 		B(3)
 * Tests the inductive sensor 	B(4)
 * Tests the magnetic sensor	B(5)
 * Tests the light sensor 		B(6)
 * Tests the light sensor		B(7)
 *
 *
 * Operator-Tests:
 *
 * Tests the height-measure		B(2)
 * Tests the inductive sensor	B(4)
 * Tests the magnetic sensor	B(5)
 *
 *
 *
 * Inherits: Sensor.h
 */

#include "../Controller/Sensor.h"
#include "../Controller/CoreController.h"
#include "../Thread/HAWThread.h"

#define TIME 1

class Test_Sensor : public thread::HAWThread {
public:
	Test_Sensor();
	virtual ~Test_Sensor();
	virtual void execute(void*);
	virtual void shutdown();
	bool test_sen_b0();
	bool test_sen_b1();
	bool test_height_sen_b2();
	bool test_sen_b3();
	bool test_induct_sen_b4();
	bool test_mag_sen_b5();
	bool test_sen_b6();
	bool test_sen_b7();
	void test_Operator_Included();
	void test_Software_Only();
	bool is_correct_state(int sen_no, int res, int port, int state);
	void test_print(int sen_no, int res, const int bit);


private:
	CoreController *cc;
};


#endif /* _TEST_SENSOR_H_ */
