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
#include "CoreController.h"

Test_FSM::Test_FSM() {
	cc = CoreController::getInstance();
	last_Reg_State_B = 0xD3;
	last_Reg_State_C = 0x50;
	for(int i=0; i<3; i++) wp_list.push_back( new Puck_FSM_1 );
	for(int i=0; i<3; i++) wp_list.push_back( new Puck_FSM_2 );
	wp_list[3]->hasPocket = 1;
	wp_list[4]->hasPocket = 1;

	wp_list_index = 0;
	cout << "-----Modus 1: Machine One(sort out WP with wrong height)-----" << endl;
	cout << "Test1: please put on a WP with pocket on LS_B0" << endl;
}

Test_FSM::~Test_FSM() {
	// TODO Auto-generated destructor stub
}

void Test_FSM::init_tests(){

}

void Test_FSM::handleSignal(int val, int port){



	switch (port) {
			case INTERRUPT_D_PORT_B:
				if ( !( (val>>WP_RUN_IN) &1) ) {
					//cout << "Test_FSM: in" << endl;
					wp_list[wp_list_index]->ls_b0();
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
				}
				if (( (val>>WP_OUTLET)&1 ) && !( (last_Reg_State_B>>WP_OUTLET)&1)) {
					//cout << "Test_FSM: end of band out" << endl;

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

			if(wp_list_index==0 && wp_list[wp_list_index]->pass_ls_b7){
				cout << "Test 1 passed, wp should lie at end of machine" << endl;
				wp_list_index++;
				cout << "Test2: please take WP from machine and put on a WP without pocket and correct height on LS_B0" << endl;

			} else if(wp_list_index==0 && wp_list[wp_list_index]->pass_ls_b6){
				cout << "Test 1 NOT passed, wp is not at end of machine" << endl;

			} else if(wp_list_index==1 && wp_list[wp_list_index]->pass_ls_b7){
				cout << "Test 2 passed, wp should lie at end of machine" << endl;
				wp_list_index++;
				cout << "Test3: please take WP from machine and put on a WP with wrong height on LS_B0" << endl;

			} else if(wp_list_index==1 && wp_list[wp_list_index]->pass_ls_b6){
				cout << "Test 2 NOT passed, wp is not at end of machine" << endl;

			} else if(wp_list_index==2 && wp_list[wp_list_index]->pass_ls_b6){
				cout << "Test 3 passed, wp should lie in slide" << endl;
				wp_list_index++;
				cout << "-----Modus 2: Machine TWO(sort out WP with Pocket and without Metal)-----" << endl;
				cout << "Test4: please take WP from machine and put on a WP with Pocket and without metal on LS_B0" << endl;

			} else if(wp_list_index==2 && wp_list[wp_list_index]->pass_ls_b7){
				cout << "Test 3 NOT passed, wp is not in slide" << endl;

			} else if(wp_list_index==3 && wp_list[wp_list_index]->pass_ls_b6){
				cout << "Test 4 passed, wp should lie in slide" << endl;
				wp_list_index++;
				cout << "Test5: please take WP from machine and put on a WP with Pocket and metal on LS_B0" << endl;

			} else if(wp_list_index==3 && wp_list[wp_list_index]->pass_ls_b7){
				cout << "Test 4 NOT passed, wp is not in slide" << endl;

			} else if(wp_list_index==4 && wp_list[wp_list_index]->pass_ls_b7){
				cout << "Test 5 passed, wp should lie at end of machine" << endl;
				wp_list_index++;
				cout << "Test6: please take WP from machine and put on a WP without Pocket and correct Height on LS_B0" << endl;

			} else if(wp_list_index==4 && wp_list[wp_list_index]->pass_ls_b6){
				cout << "Test 5 NOT passed, wp is not at end of machine" << endl;

			} else if(wp_list_index==5 && wp_list[wp_list_index]->pass_ls_b7){
				cout << "Test 6 passed, wp should lie at end of machine" << endl;
				wp_list_index++;
				cout << "------------All Tests passed successful----------" << endl;

			} else if(wp_list_index==5 && wp_list[wp_list_index]->pass_ls_b6){
							cout << "Test 6 NOT passed, wp is not at end of machine" << endl;
			}




}
