/**
 * Puck_FSM
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Milestone 4: Automatenimplementierung
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 *For global variables, machine type, global timer id's..
 *
 *
 */

#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_

#include "../Timer/Timer.h"
#include "../Thread/Singleton_T.h"

/*
 * this enum descibe the Type of Machine
 */
enum machineType {
	PUCK_FSM_1_,
	PUCK_FSM_2_
};

class GlobalVariables : public Singleton_T<GlobalVariables>{
	friend class Singleton_T<GlobalVariables>;
public:
	GlobalVariables();
	virtual ~GlobalVariables();
	/**
	 * return the current Type - PUCK_FSM_1_ or PUCK_FSM_2_
	 */
    machineType getCurrentType();
	/**
	 * sets the current Type - PUCK_FSM_1_ or PUCK_FSM_2_
	 */
    void setCurrentType(machineType currentType);
    /**
     * return the global Timer ID for the switch - to avoid "kicking pucks"
     */
    int getSwitch_TID();
    /**
     * sets the global Timer ID for the switch - to avoid "kicking pucks"
     */
    void setSwitch_TID(int switch_TID);
    /**
     * needs a Timer object to get a ID for the switch
     */
    Timer *timer;

private:
    /**
     * contains the Machine type (1 or 2)
     */
	machineType currentType;
	/**
	 * contains the global Timer ID for the switch
	 */
	int switch_TID;

};

#endif /* GLOBALVARIABLES_H_ */
