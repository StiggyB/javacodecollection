

#ifndef SENSOR_H_
#define SENSOR_H_


#include <vector>
#include "Communication.h"
#include "../HAL/HALCore.h"
#include "../HAL/Lampen.h"
#include "../FSM/Puck_FSM.h"
#include "../FSM/Puck_FSM_1.h"
#include "../FSM/Puck_FSM_2.h"
#include "../Serial/Serial.h"
#include "../Thread/HAWThread.h"
#include "../Tests/test.h"
#include "../Timer/Timer.h"
#include "../Tests/Test_Sensor.h"
#include "../Tests/Test_FSM.h"
#include "../Thread/Singleton_T.h"
#include "../Functor/CallBackThrower.h"

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

#define PUCK_FSM_1
//#define PUCK_FSM_2

class Sensor : public thread::HAWThread, public Communication, public Singleton_T<Sensor>, public CallBackThrower {
	friend class Singleton_T<Sensor>;
public:
    Sensor();
    virtual ~Sensor();
    /**
     * This flag is true if the system is running
     * otherwise false to manage the buttons actuating.
     */
    bool running_mode;

    #ifdef TEST_SEN
    /**
     * Instance from the Test_Sensor
     */
	Test_Sensor *ts;
	#endif
	#ifdef TEST_FSM
	/**
	 * Instance from the Test_FSM
	 */
	Test_FSM *tests_fsm;
	#endif

protected:
    virtual void execute(void*);
    virtual void shutdown();
	/**
	 * handles all pulse messages received
	 */
    virtual void handlePulsMessage();
	/**
	 * handles all normal messages received
	 */
    virtual void handleNormalMessage();

private:
	/**
	 * This function provides a dummy callback
	 * for the minTimer exceptions.
	 */
    void dummyFunction();
    /**
     * Instance from the HALCore
     */
    HALCore *h;
    /**
     * Instance from the Light.
     */
    Lampen *l;
    /**
     * Instance from the Timer.
     */
    Timer* timer;
    /**
     * List of work pieces on the system.
     */
    std::vector<Puck_FSM*> wp_list;
    /**
     * Pointer on the dummy callback.
     */
    CallInterface<CallBackThrower, void>* callDummyFunction;
    /**
     * Dummy work piece for button actuating.
     */
    Puck_FSM* dummy_fsm;
	/**
	 * Defines a standard register status for register B.
	 */
    int last_Reg_State_B;
	/**
	 * Defines a standard register status for register C.
	 */
    int last_Reg_State_C;
    /**
     * This is the actual timer ID for work piece income.
     */
    int input_TID;
};

#endif /* SENSOR_H_ */
