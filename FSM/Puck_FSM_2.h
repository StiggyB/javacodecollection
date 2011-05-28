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
 * class for machine 1 - sort out WP with with/without metal
 *
 *
 */
#ifndef PUCK_FSM_2_H_
#define PUCK_FSM_2_H_

#include "Puck_FSM.h"
#include "../HAL/HALCore.h"
#include "iostream.h"
#include <vector>

#define PUCK_FSM_2_DEBUG

class Puck_FSM_2 : public Puck_FSM{
public:
	//Puck_FSM_2();
	Puck_FSM_2(Serial* serial, std::vector<Puck_FSM*>* puck_list);
	virtual ~Puck_FSM_2();
};


class FSM_2_start_state : public State{
	public:
		void exit(Puck_FSM *);
		void entry(Puck_FSM *);
		void ls_b0(Puck_FSM *);
};

class FSM_2_after_ls_b0 : public State{
	public:
		void exit(Puck_FSM *);
		void entry(Puck_FSM *);
		void ls_b1(Puck_FSM *);
};

class FSM_2_after_ls_b1 : public State{
	public:
	void entry(Puck_FSM *);
	void exit(Puck_FSM *);
	void ls_b3(Puck_FSM *);
};



class FSM_2_in_metal_measure : public State{
	public:
		void entry(Puck_FSM *);
		void exit(Puck_FSM *);
};



class FSM_2_after_metal_measure : public State{
	public:
		void ls_b7_in(Puck_FSM *);
		void entry(Puck_FSM *);
		void exit(Puck_FSM *);
};



class FSM_2_end_state : public State{
	public:
		void ls_b7_out(Puck_FSM *);
		void entry(Puck_FSM *);
		void exit(Puck_FSM *);

};


class FSM_2_sort_out : public State{
	public:
		void ls_b6(Puck_FSM *);
		void entry(Puck_FSM *);
		void exit(Puck_FSM *);
};


class FSM_2_in_slide : public State{
	public:
	void entry(Puck_FSM *);
	void exit(Puck_FSM *);

};

class FSM_2_check_slide : public State{
	public:
		void entry(Puck_FSM *);
		void exit(Puck_FSM *);
};

class FSM_2_ErrorState : public State{
	public:
		void entry(Puck_FSM *);
		void exit(Puck_FSM *);

};


#endif /* PUCK_FSM_2_H_ */
