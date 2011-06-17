#ifndef PUCK_FSM_2_H_
#define PUCK_FSM_2_H_

#include <vector>
#include <iostream.h>
#include "Puck_FSM.h"
#include "../HAL/HALCore.h"

#define PUCK_FSM_2_DEBUG

/**
 * Puck_FSM_2
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
 * class for machine 1 - sort out WP with with/without metal
 *
 *
 */
class Puck_FSM_2: public Puck_FSM {
public:
	Puck_FSM_2(std::vector<Puck_FSM*>* puck_list);
	virtual ~Puck_FSM_2();
};

class FSM_2_start_state: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b0(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_2_after_ls_b0: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b1(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_2_after_ls_b1: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b3(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_2_in_metal_measure: public State {
public:
	void entry(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_2_after_metal_measure_uncorrect_wp: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b6(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_2_wp_in_slide: public State {
public:
	void entry(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_2_check_slide: public State {
public:
	void entry(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};
class FSM_2_after_metal_measure_correct_wp: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b7_in(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_2_end_state: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b7_out(Puck_FSM * fsm);
	void errorState(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

class FSM_2_ErrorState: public State {
public:
	void entry(Puck_FSM * fsm);
	void ls_b6(Puck_FSM * fsm);
	void reset(Puck_FSM * fsm);
	void exit(Puck_FSM * fsm);
};

#endif /* PUCK_FSM_2_H_ */
