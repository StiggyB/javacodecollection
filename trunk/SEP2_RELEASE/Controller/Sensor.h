
#ifndef SENSOR_H_
#define SENSOR_H_


#include "../Thread/HAWThread.h"
#include "../HAL/HALCore.h"
#include "../HAL/Lampen.h"
#include "Communication.h"
#include "../Tests/test.h"
#include "../Tests/Test_Sensor.h"
#include "../Tests/Test_FSM.h"
#include "../Thread/HAWThread.h"
#include "../HAL/HALCore.h"
#include <vector>


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
	 * Deal with the Interrupt for given port. ONLY FOR TEST PURPOSES!
	 * \param port an integer representing the port where an interrupt occures.
	 * \param val an integer representing the value of the interrupts.
	 */
	void interrupt(int port, int val);
	Sensor();
	virtual ~Sensor();
	bool is_Band_has_wp_ls7;
//TESTS
#ifdef TEST_SEN
	Test_Sensor *ts;
	void testSen(Test_Sensor *t){ ts = t;}
#endif
#ifdef TEST_FSM
	Test_FSM *tests_fsm;
	void testFSM(Test_FSM *t){ tests_fsm = t;}
#endif

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
	 * pointer to Lampen
	 */
	Lampen *l;
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
	void initPucks();

};

#endif /* SENSOR_H_ */
