
#ifndef TEST_FSM_H_
#define TEST_FSM_H_

#include <vector>
#include "Communication.h"
#include "../HAL/HALCore.h"
#include "../FSM/Puck_FSM.h"
#include "../FSM/Puck_FSM_1.h"
#include "../FSM/Puck_FSM_2.h"
#include "../Thread/HAWThread.h"
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
 *For testing FSM, includes machine 1 and 2
 *
 *
 */
class Test_FSM : public thread::HAWThread{
public:
	Test_FSM();
	virtual ~Test_FSM();
	std::vector<Puck_FSM*> working_list;
	/**
	 * prepare an internal list for the 6 test cases
	 */
	void handleSignal(int val, int port);
	/**
	 * actual object for test case
	 */
	Puck_FSM actual_fsm;
	/**
	 * reference to HAL
	 */
	HALCore *cc;
	/**
	 *this list contains the 6 test cases
	 */
	std::vector<Puck_FSM*> wp_test_list;
	/**
	 * markers, if a wp is on last light barrier
	 */
	bool aWPendOfMachine;
	/**
	 *	markers the actual index for test case list
	 */
	int wp_list_index;
	/**
	 * defines a standard register status for register B
	 */
	int last_Reg_State_B;
	/**
	 * defines a standard register status for register C
	 */
	int last_Reg_State_C;
	/**
	 * in test mode this bool is true
	 */
	bool running;
	/**
	 * empty list for testing - only one wp in one test
	 */
	std::vector<Puck_FSM*> dummy_puck_list;
protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* TEST_FSM_H_ */
