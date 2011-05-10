/*
 * Machine2.h
 *
 *  Created on: 10.05.2011
 *      Author: user
 */

#ifndef MACHINE2_H_
#define MACHINE2_H_

#include "../Controller/CoreController.h"



class Machine2 {
  class State_M2 *current;
  public:
	Machine2();
	virtual ~Machine2();
    void setCurrent(State_M2 *s);
	void ls_b1();
	void ls_b3();
	void ls_b6();
	void ls_b7();
	void entry();
	void exit();
	void errorState();
	bool isOnLS7;
  private:
	CoreController *cc;

};

class State_M2
{
  public:
	State_M2();
	virtual ~State_M2();
	virtual void ls_b1(Machine2 *);
	virtual void ls_b3(Machine2 *);
	virtual void ls_b6(Machine2 *);
	virtual void ls_b7(Machine2 *);
	virtual void entry(Machine2 *);
	virtual void exit(Machine2 *);
	virtual void errorState(Machine2 *);
	CoreController *cc;
};

class Band_2_aufgelegt : public State_M2{
	public:
		void exit(Machine2 *);
		void entry(Machine2 *);
		void ls_b1(Machine2 *);
};

class Bei_LS1 : public State_M2{
	public:
	void entry(Machine2 *);
	void exit(Machine2 *);
	void ls_b3(Machine2 *);
};



class In_Metallmessung : public State_M2{
	public:
		void entry(Machine2 *);
		void exit(Machine2 *);
};



class durchschleusen : public State_M2{
	public:
		void ls_b7(Machine2 *);
		void entry(Machine2 *);
		void exit(Machine2 *);
};



class Ende_Band2 : public State_M2{
	public:
		void ls_b7(Machine2 *);
		void entry(Machine2 *);
		void exit(Machine2 *);

};


class ausschleusen : public State_M2{
	public:
		void ls_b3(Machine2 *);
		void entry(Machine2 *);
		void exit(Machine2 *);
};


class WS_im_Schacht : public State_M2{
	public:
	void entry(Machine2 *);
	void exit(Machine2 *);

};

class pruef_schacht_voll : public State_M2{
	public:
		void entry(Machine2 *);
		void exit(Machine2 *);
};

class ErrorState : public State_M2{
	public:
		void entry(Machine2 *);
		void exit(Machine2 *);

};


#endif /* MACHINE2_H_ */
