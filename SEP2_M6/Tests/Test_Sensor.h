#ifndef _TEST_SENSOR_H_
#define _TEST_SENSOR_H_
/**
 * Test_Sensor
 *
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Tests the sensor system. React to the pulse messages
 * from the interrupt controller. Additional testing of
 * expected values and included reaction from the light.
 *
 * Tests:
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
 * Tests the start button 		C(4)
 * Tests the stop button		C(5)
 * Tests the reset button 		C(6)
 * Tests the emergency button	C(7)
 *
 * Inherits: string, CoreController.h, HAWThread.h
 */

#include <string>
#include "../HAL/HALCore.h"
#include "../Thread/HAWThread.h"

/**
 * Duration for sleeps between open/closeSwitch.
 */
#define DURATION 1

/**
 * Expected values for the tests from port B.
 */
enum PortBState {
	RUN_IN_STATE_LOW = 0,
	RUN_IN_STATE_HIGH = (1 << 0),
	IN_HEIGHT_STATE_LOW = 0,
	IN_HEIGHT_STATE_HIGH = (1 << 1),
	PLANE_WP_DEFAULT_HEIGHT = PLANE_WP,
	IN_SWITCH_STATE_LOW = 0,
	IN_SWITCH_STATE_HIGH = (1 << 3),
	NO_METAL_STATE = 0,
	IS_METAL_STATE = (1 << 4),
	SWITCH_CLOSED_STATE = 0,
	SWITCH_OPEN_STATE = (1 << 5),
	IN_SLIDE_STATE_LOW = 0,
	IN_SLIDE_STATE_HIGH = (1 << 6),
	OUTLET_STATE_LOW = 0,
	OUTLET_STATE_HIGH = (1 << 7)
};

/**
 * Expected values for the tests from port C.
 */
enum PortCState {
	BIT_START_PUSHED = (1 << 4),
	BIT_STOP_PUSHED = 0x0,
	BIT_RESET_PUSHED = (1<< 6),
	BIT_E_STOP_PUSHED = 0x1,
	BIT_E_STOP_LOST = (1 << 7)
};

class Test_Sensor: public thread::HAWThread {
public:
	Test_Sensor();
	virtual ~Test_Sensor();
	virtual void execute(void*);
	virtual void shutdown();
	/**
	 * This function tests the sensors with interrupts.
	 * \param port actual port from the system
	 * \param value to identify the sensor
	 */
	void test_sen_interrupt(int port, int value);
	/**
	 * This function tests the sensors with polling.
	 * \param port port from the system
	 * \param value to identify the sensor
	 */
	void test_sen_polling(int port, int value);

private:

	/**
	 * This function lets the light shine and print
	 * a test successful text.
	 */
	void test_isSuccessful(bool success);
	/**
	 * This function evaluates the results of a test with
	 * expected values from an enum.
	 * \param sen_no - the serial number as string
	 * \param actual - test result as int
	 * \param state - expected state as int
	 * \result true if actual is equals state, otherwise false
	 */
	bool assert_equals(string sen_no, int actual, int state);
	/**
	 * This function prints a specific test reuslt.
	 * \param sen_no - serial number as string
	 * \param actual - test result as int
	 * \param state - expected state as int
	 */
	void test_print(string sen_no, int actual, int state);
	/**
	 * Instance for HW control.
	 */
	HALCore *hc;
	/**
	 * Defines a standard register status for register B.
	 */
	PortB last_state_B;
	/**
	 * Defines a standard register status for register C.
	 */
	PortCState last_state_C;
	/**
	 * Flag for general success in the Test_Sensor.
	 */
	bool success;
	/**
	 * This attribute defines the actual section in the test.
	 */
	int section;
	/**
	 * This attribute defines the actual height from the work piece.
	 */
	int height;
	/**
	 * Result variable for temporary testing.
	 */
	int res;
};

#endif /* _TEST_SENSOR_H_ */
