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

/**
 * Actual locations for the work pieces on the system.
 */
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
};

/**
 * Allocated time for the sectors in ms.
 * (note: this are inexact values)
 *
 */
//TODO Set exact values with min/max tolerance.
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
enum ReferenceTime {
	MIN_TIME_B1 = 2000,
	MAX_TIME_B1 = 3000,
	MIN_TIME_B3 = 500,
	MAX_TIME_B3 = 1500,
	MIN_TIME_B6 = 800,
	MAX_TIME_B6 = 1600,
	MIN_TIME_B7 = 1500,
	MAX_TIME_B7 = 2500,
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
	class State *current;
	Puck_FSM();
	virtual ~Puck_FSM();
	void setCurrent(State *s);
	void ls_b0();
	void ls_b1();
	void ls_b3();
	void ls_b6();
	void ls_b7_in();
	void ls_b7_out();
	void entry();
	void exit();
	void errorState();
	void reset();
	void noticed_error_confirmed();
	bool engine_should_be_started;
	bool hasPocket;
	ErrorType errType;
	int maxTimerId;
	int minTimerId;
	int checkSlide_TID;
	bool checked_to_early;
	location_attribut expectedLocation;
	location_attribut location;
	Lampen *lamp;
	HALCore *hc;
	Timer *timer;
	Serial *serial;
	int check_last_lb();
	void delete_unnecessary_wp();
	bool starts_engine_if_nessecary();
	void requestfromMachine1();
	void PuckhasPocket();
	void PuckhasnoPocket();
	void puck_arrived();
	void machine2_free();
	void isSlideFull();
	int setErrorStateTimer(ReferenceTime allocTime);
	int setDummyTimer(ReferenceTime refTime);
	void removeAllLights();
	void checkLocation();
	bool getErrorNoticed();
	void setErrorNoticed(bool errorNoticed);
	void selectErrorType();
	void puck_fsm2_outgoing();
	void start_signal(bool was_serial);
	void stop_signal(bool was_serial);
	void reset_signal(bool was_serial);
	void estop_in_signal(bool was_serial);
	void estop_out_signal(bool was_serial);
	void delete_last_expected_location();
	bool request;
	std::vector<location_attribut> expected_loc_list;
protected:
	std::vector<Puck_FSM*> *puck_list;
private:
	bool errorNoticed;
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
