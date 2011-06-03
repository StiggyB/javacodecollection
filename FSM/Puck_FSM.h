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
 * interface for the finite state machine's
 *
 *
 */

#ifndef IPUCK_FSM_H_
#define IPUCK_FSM_H_

#include "../HAL/HALCore.h"
#include "../HAL/Lampen.h"
#include <vector>
#include "../Serial/Serial.h"
#include "../Timer/Timer.h"
#include "../Functor/Functor.h"
#include "../Functor/FunctorMaker.h"
#include "../Functor/CallInterface.h"

//#define PUCK_FSM_STATE_DEBUG

enum location_attribut {
	ON_FIRST_LB, AFTER_FIRST_LB, AFTER_HEIGH_MEASURE, AFTER_METAL_SENSOR_SORT_OUT, SORT_OUT,
	AFTER_METAL_SENSOR_FORWARD, ON_LAST_LB, AFTER_LAST_LB
};

class Puck_FSM {
public:
	/**
	 * Pointer to actual state
	 */
	class State *current;
	//Puck_FSM();
	Puck_FSM();
	virtual ~Puck_FSM();
	/**
	 * set new state
	 * \param a State, which will be the new acutal state of fsm
	 */
	void setCurrent(State *s);
	/**
	 * first light barrier was passed
	 */
	void ls_b0();
	/**
	 * second light barrier (for height measure) was passed
	 */
	void ls_b1();
	/**
	 * third light barrier (for metal measure) was passed
	 */
	void ls_b3();
	/**
	 * slide light barrier was passed
	 */
	void ls_b6();
	/**
	 * end light barrier was passed
	 */
	void ls_b7_in();
	/**
	 * wp was taken from band
	 */
	void ls_b7_out();
	/**
	 * entry function for state, only internal use
	 */
	void entry();
	/**
	 * exit function for state, only internal use
	 */
	void exit();
	/**
	 * general error state
	 */
	void errorState();
	/**
	 * is true, if wp need transport for finite state input
	 */
	bool engine_should_be_started;
	/**
	 * is true, if wp has pocket (for second machine)
	 */
	bool hasPocket;
	/**
	 * Instance for lamp in error state
	 */
	Lampen *lamp;
	/**
	 * Instance for HW control
	 */
	HALCore *hc;

	Timer *timer;
	location_attribut location;
    int check_last_lb();
    void delete_unnecessary_wp();
    void starts_engine_if_nessecary();
	void requestfromMachine1();
	void PuckhasPocket();
	void PuckhasnoPocket();
	void puck_arrived();
	void machine2_free();
	void puck_fsm2_outgoing();

	void start_signal(bool was_serial);
	void stop_signal(bool was_serial);
	void reset_signal(bool was_serial);
	void estop_in_signal(bool was_serial);
	void estop_out_signal(bool was_serial);
	bool request;
	Serial* serial;

protected:
    std::vector<Puck_FSM*>* puck_list;

};

class State
{
  public:
	State();
	virtual ~State();
	/**
	 * first light barrier was passed
	 * \param fsm Pointer to a Puck_FSM
	 */
	virtual void ls_b0(Puck_FSM *fsm);
	/**
	 * second light barrier (for height measure) was passed
	 * \param fsm Pointer to a Puck_FSM
	 */
	virtual void ls_b1(Puck_FSM *fsm);
	/**
	 * third light barrier (for metal measure) was passed
	 * \param fsm Pointer to a Puck_FSM
	 */
	virtual void ls_b3(Puck_FSM *fsm);
	/**
	 * slide light barrier was passed
	 * \param fsm Pointer to a Puck_FSM
	 */
	virtual void ls_b6(Puck_FSM *fsm);
	/**
	 * end light barrier was passed
	 * \param fsm Pointer to a Puck_FSM
	 */
	virtual void ls_b7_in(Puck_FSM *fsm);
	/**
	 * wp was taken from band
	 * \param fsm Pointer to a Puck_FSM
	 */
	virtual void ls_b7_out(Puck_FSM *fsm);
	/**
	 * entry function for state, only internal use
	 * \param fsm Pointer to a Puck_FSM
	 */
	virtual void entry(Puck_FSM *fsm);
	/**
	 * exit function for state, only internal use
	 * \param fsm Pointer to a Puck_FSM
	 */
	virtual void exit(Puck_FSM *fsm);
	/**
	 * general error state
	 * \param fsm Pointer to a Puck_FSM
	 */
	virtual void errorState(Puck_FSM *fsm);
};

#endif /* IPUCK_FSM_H_ */
