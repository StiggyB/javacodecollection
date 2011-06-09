
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
#include "../Tests/Test_Sensor.h"
#include "../Tests/Test_FSM.h"
#include "../Thread/Singleton_T.h"

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

//#define PUCK_FSM_1
#define PUCK_FSM_2

class Sensor : public thread::HAWThread, public Communication, public Singleton_T<Sensor>{
	friend class Singleton_T<Sensor>;
public:
    void interrupt(int port, int val);
    Sensor();
    virtual ~Sensor();
    bool running_mode;

    #ifdef TEST_SEN
	Test_Sensor *ts;
	#endif
	#ifdef TEST_FSM
	Test_FSM *tests_fsm;
	#endif

protected:
    virtual void execute(void*);
    virtual void shutdown();
    virtual void handlePulsMessage();
    virtual void handleNormalMessage();
    void clean();
private:
    HALCore *h;
    Lampen *l;
    std::vector<Puck_FSM*> wp_list;
    Puck_FSM* dummy_fsm;
	bool request;
    bool settingUpSensor();
    void cleanUpSensor();
    int cnt;
    int last_Reg_State_B;
    int last_Reg_State_C;
    void puck_fsm2_outgoing();
    void delete_unnecessary_wp();
    void starts_engine_if_nessecary();
};

#endif /* SENSOR_H_ */
