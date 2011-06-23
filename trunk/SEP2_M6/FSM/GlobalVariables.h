
#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_

#include "../Timer/Timer.h"
#include "../Thread/Singleton_T.h"

/*
 * This enum describe the type of machine
 */
enum machineType {
	PUCK_FSM_1_,
	PUCK_FSM_2_
};

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
 * For global variables, machine type, global timer id's..
 *
 *
 */
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
	 * \param currentType is the new machineType to set.
	 */
    void setCurrentType(machineType currentType);
    /**
     * \return the global Timer ID for the switch - to avoid "kicking pucks"
     */
    int getSwitch_TID();
    /**
     * sets the global Timer ID for the switch - to avoid "kicking pucks"
     */
    void setSwitch_TID(int switch_TID);
    /**
     * needs a Timer object to get a ID for the switch
     * \param switch_TID is the actual timer ID
     */
    Timer *timer;

private:
    /**
     * contains the machine type (1 or 2)
     */
	machineType currentType;
	/**
	 * contains the global Timer ID for the switch
	 */
	int switch_TID;

};

#endif /* GLOBALVARIABLES_H_ */
