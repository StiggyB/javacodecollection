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

#define PUCK_FSM_STATE_DEBUG

class Puck_FSM {
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
	void ls_b0(void*);
	/**
	 * second light barrier (for height measure) was passed
	 */
	void ls_b1(void*);
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
	 * is true, if wp has passed first light barrier
	 */
	bool pass_ls_b1;
	/**
	 * is true, if wp has passed second light barrier
	 */
	bool pass_ls_b3;
	/**
	 * is true, if wp has passed the light barrier in slide
	 */
	bool pass_ls_b6;
	/**
	 * is true, if wp has passed the light barrier at the end of machine
	 */
	bool pass_ls_b7;
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
	HALCore *cc;

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
