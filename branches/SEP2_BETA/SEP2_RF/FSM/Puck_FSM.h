/*
 * IPuck_FSM.h
 *
 *  Created on: 13.05.2011
 *      Author: user
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
	virtual void ls_b0(Puck_FSM *);
	virtual void ls_b1(Puck_FSM *);
	virtual void ls_b3(Puck_FSM *);
	virtual void ls_b6(Puck_FSM *);
	virtual void ls_b7_in(Puck_FSM *);
	virtual void ls_b7_out(Puck_FSM *);
	virtual void entry(Puck_FSM *);
	virtual void exit(Puck_FSM *);
	virtual void errorState(Puck_FSM *);
};

#endif /* IPUCK_FSM_H_ */
