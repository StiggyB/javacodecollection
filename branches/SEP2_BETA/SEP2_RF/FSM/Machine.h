/*
 * Machine.h
 *
 *  Created on: 06.05.2011
 *      Author: user
 */

#ifndef MACHINE_H_
#define MACHINE_H_


class Machine {
  class State *current;
  public:
	Machine();
	virtual ~Machine();
    void setCurrent(State *s);
	void LS_B1();
	void LS_B3();
	void LS_B6();
	void LS_B7();
	void entry();
	void exit();

};

class State
{
  public:
	virtual void LS_B1(Machine *);
	virtual void LS_B3(Machine *);
	virtual void LS_B6(Machine *);
	virtual void LS_B7(Machine *);
	virtual void entry(Machine *);
	virtual void exit(Machine *);
};




class Band1_aufgelegt : public State{
	public:
		void LS_B1(Machine *);
		void exit(Machine *);
		void entry(Machine *);
};

class Band1_hoehenmessung : public State{
	public:

};

class durchschleusen : public State{
	public:
		void LS_B3(Machine *);
		void entry(Machine *);
		void exit(Machine *);
};

class ausschleusen : public State{
	public:
		void LS_B3(Machine *);
};

class Weiche_zu : public State{
	public:

};

class durchschleusen_bei_LS3 : public State{
	public:
		void LS_B7(Machine *);
		void entry(Machine *);
		void exit(Machine *);
};

class WS_im_Schacht : public State{
	public:

};

class pruef_schacht_voll : public State{
	public:

};

class pruef_LS7 : public State{
	public:

};

#endif /* MACHINE_H_ */
