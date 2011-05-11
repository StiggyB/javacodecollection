/*
 * Machine.h
 *
 *  Created on: 06.05.2011
 *      Author: user
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include "../Controller/CoreController.h"

class Machine1 {
  class State_M1 *current;
  public:
	Machine1();
	virtual ~Machine1();
    void setCurrent(State_M1 *s);
    void ls_b0();
	void ls_b1();
	void ls_b3();
	void ls_b6();
	void ls_b7_in();
	void ls_b7_out();
	void wp_after_Switch();
	void entry();
	void exit();
	void errorState();
	bool isOnLS7;
	bool engine_should_be_started;
  private:
	CoreController *cc;

};

class State_M1
{
  public:
	State_M1();
	virtual ~State_M1();
	virtual void ls_b0(Machine1 *);
	virtual void ls_b1(Machine1 *);
	virtual void ls_b3(Machine1 *);
	virtual void ls_b6(Machine1 *);
	virtual void ls_b7_in(Machine1 *);
	virtual void ls_b7_out(Machine1 *);
	virtual void entry(Machine1 *);
	virtual void exit(Machine1 *);
	virtual void wp_after_Switch(Machine1 *);
	virtual void errorState(Machine1 *);
	CoreController *cc;
};

class Start_M1 : public State_M1{
	public:
		void exit(Machine1 *);
		void entry(Machine1 *);
		void ls_b0(Machine1 *);
};

class Band1_aufgelegt : public State_M1{
	public:
		void ls_b1(Machine1 *);
		void exit(Machine1 *);
		void entry(Machine1 *);
};

class Band1_hoehenmessung : public State_M1{
	public:
	void entry(Machine1 *);
	void exit(Machine1 *);
};



class ausschleusen : public State_M1{
	public:
		void ls_b3(Machine1 *);
		void entry(Machine1 *);
		void exit(Machine1 *);
};


class Weiche_zu : public State_M1{
	public:
		void ls_b6(Machine1 *);
		void entry(Machine1 *);
		void exit(Machine1 *);
};

class WS_im_Schacht : public State_M1{
	public:
	void entry(Machine1 *);
	void exit(Machine1 *);

};

class pruef_schacht_voll : public State_M1{
	public:
		void entry(Machine1 *);
		void exit(Machine1 *);
};

class durchschleusen : public State_M1{
	public:
		void ls_b3(Machine1 *);
		void entry(Machine1 *);
		void exit(Machine1 *);
		void wp_after_Switch(Machine1 *);
};

class durchschleusen_bei_LS3 : public State_M1{
	public:
		void ls_b7_in(Machine1 *);
		void entry(Machine1 *);
		void exit(Machine1 *);
};

class pruef_LS7 : public State_M1{
	public:
		void entry(Machine1 *);
		void exit(Machine1 *);
		void ls_b7_out(Machine1 *);
};

class ErrorState : public State_M1{
	public:
		void entry(Machine1 *);
		void exit(Machine1 *);

};



#endif /* MACHINE_H_ */
