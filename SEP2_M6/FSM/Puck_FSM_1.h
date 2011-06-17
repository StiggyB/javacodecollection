#ifndef Puck_FSM_1_H_
#define Puck_FSM_1_H_

#include <vector>
#include <iostream.h>
#include "Puck_FSM.h"

#define PUCK_FSM_1_DEBUG
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
 * class for machine 1 - sort out WP with correct/incorrect height
 *
 *
 */
class Puck_FSM_1: public Puck_FSM {
public:
	Puck_FSM_1(std::vector<Puck_FSM*>* puck_list);
	virtual ~Puck_FSM_1();
};

class FSM_1_start_state: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b0(Puck_FSM * fsm);
	void ls_b7_out(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_1_after_ls_b0: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b1(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_1_height_measure: public State {
public:
	void entry(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_1_sort_out: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b3(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_1_ls_b3_passed_sort_out: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b6(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_1_wp_in_slide: public State {
public:
	void entry(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_1_check_slide: public State {
public:
	void entry(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_1_correct_height: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b3(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_1_ls_b3_passed_correct_height: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b7_in(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_1_end_state: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b7_out(Puck_FSM *);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_1_ErrorState: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b6(Puck_FSM * fsm);
	void reset(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

#endif /* Puck_FSM_H_ */
