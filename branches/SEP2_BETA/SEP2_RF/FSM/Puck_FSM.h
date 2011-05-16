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

#include "../Controller/CoreController.h"
#include "../Lampen/Error_State_Lamp.h"

class Puck_FSM {
public:
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
	bool pass_ls_b1;
	bool pass_ls_b3;
	bool pass_ls_b6;
	bool pass_ls_b7;
	bool engine_should_be_started;
	bool hasPocket;
	Error_State_Lamp lamp;
	CoreController *cc;

};

class State
{
  public:
	State();
	virtual ~State();
	/**
	 * first light barrier was passed
	 * \param Pointer to a Puck_FSM
	 */
	virtual void ls_b0(Puck_FSM *);
	/**
	 * second light barrier (for height measure) was passed
	 * \param Pointer to a Puck_FSM
	 */
	virtual void ls_b1(Puck_FSM *);
	/**
	 * third light barrier (for metal measure) was passed
	 * \param Pointer to a Puck_FSM
	 */
	virtual void ls_b3(Puck_FSM *);
	/**
	 * slide light barrier was passed
	 * \param Pointer to a Puck_FSM
	 */
	virtual void ls_b6(Puck_FSM *);
	/**
	 * end light barrier was passed
	 * \param Pointer to a Puck_FSM
	 */
	virtual void ls_b7_in(Puck_FSM *);
	/**
	 * wp was taken from band
	 * \param Pointer to a Puck_FSM
	 */
	virtual void ls_b7_out(Puck_FSM *);
	/**
	 * entry function for state, only internal use
	 * \param Pointer to a Puck_FSM
	 */
	virtual void entry(Puck_FSM *);
	/**
	 * exit function for state, only internal use
	 * \param Pointer to a Puck_FSM
	 */
	virtual void exit(Puck_FSM *);
	/**
	 * general error state
	 * \param Pointer to a Puck_FSM
	 */
	virtual void errorState(Puck_FSM *);
};

#endif /* IPUCK_FSM_H_ */
