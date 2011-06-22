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
#include "FSM/GlobalVariables.h"

#define PUCK_FSM_STATE_DEBUG

/**
 * Actual locations for the work pieces on the system.
 */
enum LocationAttribut {
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
	WP_UNKOWN_B7,
	WP_DISAPPEARED_FSM2
};

/**
 * Allocated time for the sectors in ms.
 * (note: this are inexact values)
 *
 */
//enum ReferenceTime {
//	MIN_TIME_B1 = 2000,
//	MAX_TIME_B1 = 3500,
//	MIN_TIME_B3 = 800,
//	MAX_TIME_B3 = 2000,
//	MIN_TIME_B6 = 800,
//	MAX_TIME_B6 = 3000,
//	MIN_TIME_B7 = 2000,
//	MAX_TIME_B7 = 3000,
//	MAX_TIME_IN_SLIDE = 2000
//};

/**
 * Allocated time for the sectors in ms.
 *
 */
enum ReferenceTime {
	MIN_TIME_B1 = 2000,
	MAX_TIME_B1 = 3200,
	MIN_TIME_B3 = 500,
	MAX_TIME_B3 = 1700,
	MIN_TIME_B6 = 800,
	MAX_TIME_B6 = 2000,
	MIN_TIME_B7 = 1500,
	MAX_TIME_B7 = 3000,
	MAX_TIME_IN_SLIDE = 2000,
	MAX_TIME_FSM2 = 2000
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
 * Interface for the finite state machine's
 *
 *
 */
class Puck_FSM: public CallBackThrower {
public:
	/**
	 * Pointer to actual state
	 */
	class State *current;
	/**
	 * set new state
	 * \param a State, which will be the new acutal state of fsm
	 */
	void setCurrent(State *s);
	Puck_FSM();
	virtual ~Puck_FSM();
	/**
	 * Getter for attribute errorNoticed.
	 */
	bool getErrorNoticed();
	/**
	 * Setter for attribute errorNoticed.
	 */
	void setErrorNoticed(bool errorNoticed);
	/**
	 * This function starts synchronous with FSM_1
	 * and FSM_2.
	 * \param true if the signal came from serial
	 */
	void start_signal(bool was_serial);
	/**
	 * This function checks the actual position.
	 * \return -1 if the one of the work pieces
	 * has the location ON_LAST_LB.
	 */
	int check_last_lb();
	/**
	 * This function stops synchronous FSM_1
	 * and FSM_2.
	 * \param true if the signal came from serial
	 */
	void stop_signal(bool was_serial);
	/**
	 * This function resets synchronous FSM_1
	 * and FSM_2.
	 * \param true if the signal came from serial
	 */
	void reset_signal(bool was_serial);
	/**
	 * This function calls the emergency stop
	 * synchronous FSM_1 and FSM_2 if the
	 * emergency stop is pushed.
	 * \param true if the signal came from serial
	 */
	void estop_in_signal(bool was_serial);
	/**
	 * This function calls the emergency stop
	 * synchronous FSM_1 and FSM_2 if the
	 * emergency stop is pulled.
	 * \param true if the signal came from serial
	 */
	void estop_out_signal(bool was_serial);
	/**
	 *
	 */
	void error_arrived_serial();
	/**
	 *
	 */
	void error_solved_serial();
	/**
	 * This function starts the system.
	 */
	void machine2_free();
	/**
	 * This function deletes the work piece on FSM_1 if it
	 * is arrived and sends the properties of the work piece.
	 */
	void puck_arrived();
	/**
	 * This function sends a request from FSM_1
	 * to FSM_2 if FSM_2 is free send MACHINE2_FREE.
	 */
	void requestfromMachine1();
	/**
	 * This function sets the hasPocket flag.
	 */
	void PuckhasPocket();
	/**
	 * This function deletes the hasPocket flag.
	 */
	void PuckhasnoPocket();
	/**
	 * This function sends MACHINE2_FREE to FSM_1
	 * if there was a request.
	 */
	void puck_fsm2_outgoing();
	/**
	 * This function deletes all work pieces with
	 * the location SORT_OUT or AFTER_LAST_LB.
	 */
	void delete_unnecessary_wp();
	/**
	 * This function starts the engine if
	 * some work pieces needs it.
	 * \return false if a work piece has a error
	 */
	bool starts_engine_if_nessecary();
	/**
	 * This function checks the slide if it is
	 * full call errorState otherwise delete work piece.
	 */
	void isSlideFull();
	/**
	 *
	 */
	void deletePucksInLocation(LocationAttribut location);
	/*
	 * This function wraps the dummyFunction callback.
	 */
	int setDummyTimer(ReferenceTime refTime);
	/*
	 * This function wraps the errorState callback.
	 */
	int setErrorStateTimer(ReferenceTime allocTime);
	/**
	 * This function removes all lights as a wrapper.
	 */
	void removeAllLights();
	/**
	 * This function selects the error type from
	 * and prints the operation information for
	 * a specific error.
	 */
	void selectErrorType();
	/**
	 * function to confirm a error as noticed error
	 */
	void noticed_error_confirmed();
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
	 * reset function to reset the errorState
	 */
	void reset();
	/**
	 * entry function for state, only internal use
	 */
	void entry();
	/**
	 * exit function for state, only internal use
	 */
	void exit();
	/**
	 * general error state function
	 */
	void errorState();
	/**
	 *
	 */
	LocationAttribut location_backup;
	/**
	 * Instance for lamp in error state
	 */
	Lampen *lamp;
	/**
	 * Instance for HW control
	 */
	HALCore *hc;
	/**
	 * Instance for Timer
	 */
	Timer *timer;
	/**
	 * Instance for the Serial
	 */
	Serial *serial;
	/**
	 * Actual location on the system
	 */
	LocationAttribut location;
	/**
	 * Actual ErrorType of the work piece
	 */
	ErrorType errType;
	/**
	 * is true, if wp need transport for finite state input
	 */
	bool engine_should_be_started;
	/**
	 * is true, if wp has pocket (for second machine)
	 */
	bool hasPocket;
	/**
	 * Flag is true if the work piece is to early
	 */
	bool checked_to_early;
	/**
	 * Flag is true if there was a request and
	 * a work piece on system FSM_2
	 */
	bool request;
	/**
	 * Timer Id from the maxTimer callback
	 */
	int maxTimerId;
	/**
	 * Timer Id from the minTimer callback
	 */
	int minTimerId;
	/**
	 * Timer Id from the checkSlide callback
	 */
	int checkSlide_TID;
	/**
	 * Timer Id from the closeSwitch callback
	 */
	int closeSwitch_TID;
	/**
	 *
	 */
	GlobalVariables* gv;
	/**
	 *
	 */
	bool setGlobalUnstoppable;

protected:

	/**
	 * This vector list is a collection over all
	 * work pieces.
	 */
	std::vector<Puck_FSM*> *puck_list;

private:

	/**
	 * Flag is true if the error is noticed.
	 */
	bool errorNoticed;
	/**
	 * This function provides a dummy callback
	 * for the minTimer exceptions.
	 */
	void dummyFunction();
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
