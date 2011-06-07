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

#include "Test_FSM.h"
#include "../FSM/Puck_FSM.h"
#include "../FSM/Puck_FSM_1.h"
#include "../FSM/Puck_FSM_2.h"
#include "Communication.h"
#include "../HAL/HALCore.h"

Test_FSM::Test_FSM() {
	cc = HALCore::getInstance();
	last_Reg_State_B = 0xD3;
	last_Reg_State_C = 0x50;
	aWPendOfMachine = false;
	for(int i=0; i<3; i++) wp_list.push_back( new Puck_FSM_1(serial, &puck_list) );
	for(int i=0; i<3; i++) wp_list.push_back( new Puck_FSM_2(serial, &puck_list) );
	wp_list[3]->hasPocket = 1;
	wp_list[4]->hasPocket = 1;

	wp_list_index = 0;
	cout << "-------------------------------------------------------------" << endl;
	cout << "-----Modus 1: Machine One(sort out WP with small height)-----" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "Test1: please put on a workpiece with pocket on LS_B0" << endl;
}

Test_FSM::~Test_FSM() {
	// TODO Auto-generated destructor stub
}

void Test_FSM::init_tests(){

}

void Test_FSM::execute(void*){
	running = true;
	while(running && !isStopped())sleep(1);
}

void Test_FSM::shutdown(){

}

void Test_FSM::handleSignal(int val, int port){



	switch (port) {
			case INTERRUPT_D_PORT_B:
				if ( !( (val>>WP_RUN_IN) &1) ) {
					//cout << "Test_FSM: in" << endl;
					if (!aWPendOfMachine) wp_list[wp_list_index]->ls_b0();
				}
				if ( !((val>>WP_IN_HEIGHT)&1) ) {
					//cout << "Test_FSM: in height measure " << endl;
					wp_list[wp_list_index]->ls_b1();
				}
				if ( !((val >> WP_IN_SWITCH)&1) ) {
					//cout << "Test_FSM: in metal measure" << endl;
					wp_list[wp_list_index]->ls_b3();
				}
				if ( !((val>>WP_IN_SLIDE)&1) ) {
					//cout << "Test_FSM: in slide" << endl;
					wp_list[wp_list_index]->ls_b6();
				}
				if (!(( val>>WP_OUTLET)&1 )) {
					//cout << "Test_FSM: end of band in" << endl;
					wp_list[wp_list_index]->ls_b7_in();
					aWPendOfMachine = true;

				}
				if (( (val>>WP_OUTLET)&1 ) && !( (last_Reg_State_B>>WP_OUTLET)&1)) {
					//cout << "Test_FSM: end of band out" << endl;
					aWPendOfMachine = false;

				}
				last_Reg_State_B = val;
				break;
			case INTERRUPT_D_PORT_C_HIGH:
				if (!((val>>WP_E_STOP)&1) && ((last_Reg_State_C>>WP_E_STOP)&1) ) {
					cout << "Test_FSM: E-Stop Button in" << endl;

				}else if (((val>>WP_E_STOP)&1) && !((last_Reg_State_C>>WP_E_STOP)&1) ){
					cout << "Test_FSM: E-Stop Button out" << endl;

				} else if (!((val>>WP_STOP)&1)) {
					cout << "Test_FSM: stop Button" << endl;

				} else if ((val>>WP_START)&1) {
					cout << "Test_FSM: Start Button" << endl;

				} else if ((val>>WP_RESET)&1) {
					cout << "Test_FSM: Reset Button" << endl;

				}
				last_Reg_State_C = val;
				break;
			}

			if(wp_list_index==0 && wp_list[wp_list_index]->location == ON_LAST_LB){
				cout << "Test 1 passed, workpiece should lie at end of machine" << endl;
				wp_list_index++;
				cout << "Test2: please take workpiece from machine and put on a workpiece without pocket and normal height on LS_B0" << endl;

			} else if(wp_list_index==0 && wp_list[wp_list_index]->location == SORT_OUT){
				cout << "Test1: NOT passed, workpiece is not at end of machine" << endl;

			} else if(wp_list_index==1 && wp_list[wp_list_index]->location == ON_LAST_LB){
				cout << "Test2: passed, workpiece should lie at end of machine" << endl;
				wp_list_index++;
				cout << "Test3: please take workpiece from machine and put on a workpiece with plane height on LS_B0" << endl;

			} else if(wp_list_index==1 && wp_list[wp_list_index]->location == SORT_OUT){
				cout << "Test2: NOT passed, workpiece is not at end of machine" << endl;

			} else if(wp_list_index==2 && wp_list[wp_list_index]->location == SORT_OUT){
				cout << "Test3: passed, workpiece should lie in slide" << endl;
				wp_list_index++;
				cout << "--------------------------------------------------------------------------------" << endl;
				cout << "-----Modus 2: Machine TWO(sort out workpiece with Pocket and without Metal)-----" << endl;
				cout << "--------------------------------------------------------------------------------" << endl;
				cout << "Test4: please take workpiece from machine and put on a workpiece with Pocket and without metal on LS_B0" << endl;

			} else if(wp_list_index==2 && wp_list[wp_list_index]->location == ON_LAST_LB){
				cout << "Test3: NOT passed, workpiece is not in slide" << endl;

			} else if(wp_list_index==3 && wp_list[wp_list_index]->location == SORT_OUT){
				cout << "Test4: passed, workpiece should lie in slide" << endl;
				wp_list_index++;
				cout << "Test5: please take workpiece from machine and put on a workpiece with Pocket and metal on LS_B0" << endl;

			} else if(wp_list_index==3 && wp_list[wp_list_index]->location == ON_LAST_LB){
				cout << "Test4: NOT passed, workpiece is not in slide" << endl;

			} else if(wp_list_index==4 && wp_list[wp_list_index]->location == ON_LAST_LB){
				cout << "Test5: passed, workpiece should lie at end of machine" << endl;
				wp_list_index++;
				cout << "Test6: please take workpiece from machine and workpiece on a WP without Pocket and normal Height on LS_B0" << endl;

			} else if(wp_list_index==4 && wp_list[wp_list_index]->location == SORT_OUT){
				cout << "Test5: NOT passed, workpiece is not at end of machine" << endl;

			} else if(wp_list_index==5 && wp_list[wp_list_index]->location == ON_LAST_LB){
				cout << "Test6: passed, workpiece should lie at end of machine" << endl;
				wp_list_index++;
				cout << "------------All Tests passed successful----------" << endl;
				running = false;
			} else if(wp_list_index==5 && wp_list[wp_list_index]->location == SORT_OUT){
				cout << "Test 6 NOT passed, workpiece is not at end of machine" << endl;
				running = false;
			}




}
