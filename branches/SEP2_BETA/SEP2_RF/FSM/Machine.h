/*
 * Machine.h
 *
 *  Created on: 06.05.2011
 *      Author: user
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include "../Controller/CoreController.h"

class Machine {
  class State *current;
  public:
	Machine();
	virtual ~Machine();
    void setCurrent(State *s);
	void ls_b1();
	void ls_b3();
	void ls_b6();
	void ls_b7();
	void wp_after_Switch();
	void entry();
	void exit();
	void errorState();
  private:
	CoreController *cc;

};

class State
{
  public:
	State();
	virtual ~State();
	virtual void ls_b1(Machine *);
	virtual void ls_b3(Machine *);
	virtual void ls_b6(Machine *);
	virtual void ls_b7(Machine *);
	virtual void entry(Machine *);
	virtual void exit(Machine *);
	virtual void wp_after_Switch(Machine *);
	virtual void errorState(Machine *);
	CoreController *cc;
};




class Band1_aufgelegt : public State{
	public:
		void ls_b1(Machine *);
		void exit(Machine *);
		void entry(Machine *);
};

class Band1_hoehenmessung : public State{
	public:
	void entry(Machine *);
	void exit(Machine *);
};



class ausschleusen : public State{
	public:
		void ls_b3(Machine *);
		void entry(Machine *);
		void exit(Machine *);
};


class Weiche_zu : public State{
	public:
		void ls_b6(Machine *);
		void entry(Machine *);
		void exit(Machine *);
};

class WS_im_Schacht : public State{
	public:
	void entry(Machine *);
	void exit(Machine *);

};

class pruef_schacht_voll : public State{
	public:
		void entry(Machine *);
		void exit(Machine *);
};

class durchschleusen : public State{
	public:
		void ls_b3(Machine *);
		void entry(Machine *);
		void exit(Machine *);
		void wp_after_Switch(Machine *);
};

class durchschleusen_bei_LS3 : public State{
	public:
		void ls_b7(Machine *);
		void entry(Machine *);
		void exit(Machine *);
};

class pruef_LS7 : public State{
	public:
		void entry(Machine *);
		void exit(Machine *);

};

class ErrorState : public State{
	public:
		void entry(Machine *);
		void exit(Machine *);

};



#endif /* MACHINE_H_ */
