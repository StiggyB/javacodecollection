/*
 * Test_FSM.h
 *
 *  Created on: 14.05.2011
 *      Author: user
 */

#ifndef TEST_FSM_H_
#define TEST_FSM_H_

#include "Communication.h"
#include "CoreController.h"
#include "../FSM/Puck_FSM.h"
#include "../FSM/Puck_FSM_1.h"
#include "../FSM/Puck_FSM_2.h"
#include <vector>

enum Signal {
	INCOMMING=0, IN_HEIGHT=1, IN_METAL = 2, IN_SLIDE=3, AT_END = 4
};

class Test_FSM {
public:
	Test_FSM();
	virtual ~Test_FSM();
	void init_tests();
	void handleSignal(int val, int port);
	Puck_FSM actual_fsm;
	CoreController *cc;
	std::vector<Puck_FSM*> wp_list;
	bool aWPendOfMachine;
	int wp_list_index;
	int last_Reg_State_B;
	int last_Reg_State_C;
};

#endif /* TEST_FSM_H_ */
