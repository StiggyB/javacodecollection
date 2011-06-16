#ifndef IPUCK_FSM_H_
#define IPUCK_FSM_H_

#include <vector>
#include "../HAL/HALCore.h"
#include "../HAL/Lampen.h"
#include "../Serial/Serial.h"
#include "../Timer/Timer.h"
#include "../Functor/Functor.h"
#include "../Functor/FunctorMaker.h"
#include "../Functor/CallInterface.h"
#include "../Functor/CallBackThrower.h"

#define PUCK_FSM_STATE_DEBUG

//TODO Test the reference timer then implement the rest!
enum location_attribut {
	ON_FIRST_LB,
	AFTER_FIRST_LB,
	AFTER_HEIGH_MEASURE,
	AFTER_METAL_SENSOR,
	SORT_OUT,
	AFTER_METAL_SENSOR_FORWARD,
	ON_LAST_LB,
	AFTER_LAST_LB
};

/**
 * Faults while normal running in the Festo System.
 */
enum ErrorType {
	NO_ERROR,
	WP_DISAPPEARED_B1,
	WP_UNKOWN_B1,
	WP_DISAPPEARED_B3,
	WP_UNKOWN_B3,
	WP_DISAPPEARED_B6,
	WP_UNKOWN_B6,
	SLIDE_FULL_B6,
	WP_DISAPPEARED_B7,
	WP_UNKOWN_B7
/*...*/
};

/**
 * Allocated time for the sectors in ms.
 * (note: this are inexact values)
 *
 */
//TODO Set exact values with min/max tolerance.
enum ReferenceTime {
	MIN_TIME_B1 = 2000,
	MAX_TIME_B1 = 3000,
	MIN_TIME_B3 = 800,
	MAX_TIME_B3 = 2000,
	MIN_TIME_B6 = 2500,
	MAX_TIME_B6 = 2500,
	MIN_TIME_B7 = 3000,
	MAX_TIME_B7 = 3000,
	MAX_TIME_IN_SLIDE = 2000
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
 * interface for the finite state machine's
 *
 *
 */
class Puck_FSM: public CallBackThrower {
public:
	/**
	 * Pointer to actual state
	 */
	class State *current;
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
	 *
	 */
	void reset();
	/**
	 * function to leave error state
	 */
	void noticed_error_confirmed();
	/**
	 * is true, if wp need transport for finite state input
	 */
	bool engine_should_be_started;
	/**
	 * is true, if wp has pocket (for second machine)
	 */
	bool hasPocket;
	/**
	 * Actual error type
	 */
	ErrorType errType;
	/**
	 * Actual max timer id
	 */
	int maxTimerId;
	/**
	 * Actual min timer id
	 */
	int minTimerId;
	/**
	 * Used as a compare variable for expected location
	 */
	location_attribut expectedLocation;
	/**
	 * Flag is true if a work piece arrives to early
	 */
	bool checked_to_early;
	/**
	 * Instance for lamp in error state
	 */
	Lampen *lamp;
	/**
	 * Instance for HW control
	 */
	HALCore *hc;
	/**
	 * Instance for the Timer
	 */
	Timer *timer;
	/**
	 * Instance for the Serial interface
	 */
	Serial* serial;
	/**
	 *
	 */
	location_attribut location;

	int check_last_lb();
	void delete_unnecessary_wp();
	void starts_engine_if_nessecary();
	void requestfromMachine1();
	void PuckhasPocket();
	void PuckhasnoPocket();
	void puck_arrived();
	void machine2_free();
	void isSlideFull();
	int setErrorStateTimer(ReferenceTime allocTime);
	int setCheckLocationTimer(ReferenceTime refTime);
	void removeAllLights();
	void checkLocation();
	bool getErrorNoticed();
	void setErrorNoticed(bool errorNoticed);
	void selectErrorState();
	void puck_fsm2_outgoing();
	void start_signal(bool was_serial);
	void stop_signal(bool was_serial);
	void reset_signal(bool was_serial);
	void estop_in_signal(bool was_serial);
	void estop_out_signal(bool was_serial);
	bool request;
	std::vector<location_attribut> expected_loc_list;
protected:
	std::vector<Puck_FSM*>* puck_list;
private:
	/**
	 * Error is noticed or unnoticed
	 */
	bool errorNoticed;
};

class State {
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
	/**
	 * error noticed with reset button
	 * \param fsm Pointer to a Puck_FSM
	 */
	virtual void reset(Puck_FSM * fsm);
};

#endif /* IPUCK_FSM_H_ */
