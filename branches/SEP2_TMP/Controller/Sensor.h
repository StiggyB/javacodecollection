
#ifndef SENSOR_H_
#define SENSOR_H_


#include "../Thread/HAWThread.h"
#include "../HAL/HALCore.h"
#include "../HAL/Lampen.h"
#include "../Serial/Serial.h"
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

#define PUCK_FSM_1
//#define PUCK_FSM_2

class Sensor : public thread::HAWThread, public Communication{
public:
    void interrupt(int port, int val);
    Sensor();
    virtual ~Sensor();
    bool is_Band_has_wp_ls7;
protected:
    virtual void execute(void*);
    virtual void shutdown();
    virtual void handlePulsMessage();
    virtual void handleNormalMessage();
    void clean();
private:
    HALCore *h;
    Lampen *l;
    Serial *s;
    std::vector<Puck_FSM*> wp_list;
    bool settingUpSensor();
    void cleanUpSensor();
    int cnt;
    int last_Reg_State_B;
    int last_Reg_State_C;
    void delete_unnecessary_wp();
    void starts_engine_if_nessecary();

	void initPucks();

};

#endif /* SENSOR_H_ */
