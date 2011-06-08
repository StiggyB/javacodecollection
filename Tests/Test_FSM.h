/*
 * Test_FSM.h
 *
 *  Created on: 14.05.2011
 *      Author: user
 */

#ifndef TEST_FSM_H_
#define TEST_FSM_H_

#include <vector>
#include "Communication.h"
#include "../Thread/HAWThread.h"
#include "../HAL/HALCore.h"
#include "../FSM/Puck_FSM.h"
#include "../FSM/Puck_FSM_1.h"
#include "../FSM/Puck_FSM_2.h"

enum Signal {
	INCOMMING, IN_HEIGHT, IN_METAL, IN_SLIDE, AT_END
};

class Test_FSM : public thread::HAWThread{
public:
	Test_FSM();
	virtual ~Test_FSM();
	void init_tests();
	void handleSignal(int val, int port);
	Puck_FSM actual_fsm;
	HALCore *cc;
	std::vector<Puck_FSM*> wp_list;
	bool aWPendOfMachine;
	int wp_list_index;
	int last_Reg_State_B;
	int last_Reg_State_C;
	bool running;
	std::vector<Puck_FSM*> puck_list;
protected:
	virtual void execute(void*);
	virtual void shutdown();
};

#endif /* TEST_FSM_H_ */
