/**
 * Sensor
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Milestone 3: HAL Sensorik
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Class which deals with the interrupts.
 *
 * Inherits: HAWThread.h
 */
#include "Sensor.h"
#include "../FSM/Machine1.h"
#include "../FSM/Machine2.h"
#include "../Lampen/Error_State_Lamp.h"
#include <vector>


/*
 * Reason of (*cc).setValueOfPort(PORT_B,val); at the end of interrupt?
 */

Sensor::Sensor():cnt(0) {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "error for IO Control" << std::endl;
	}
	if (cc == NULL){
		cc = CoreController::getInstance();
	}
	is_Band_has_wp_ls7 = false;
}

Sensor::~Sensor() {

}

void Sensor::execute(void*) {
	settingUpAndWaitingSensor();
}

void Sensor::settingUpAndWaitingSensor(){
	int port = 0,id=0,coid=0,rcvid  = 0;
	int last_Reg_State_B = 0xD3;//defines a standard state of register B
	int last_Reg_State_C = 0x50;//defines a standard state of register C
	cout << "Sensor: Start" << endl;
	/*Machine1 *fsm;
	fsm = new Machine1();
	//fsm->setPocket();*/
	std::vector<Machine2*> wp_list;


	//lamp.start(NULL);


	if (!setUpChannel()) {
		perror("Sensor: channel setup failed!");
		return;
	}
	if (!registerChannel(SENSOR)) {
		perror("Sensor: register channel failed!");
		return;
	}
	if (!requestChannelIDForObject(INTERRUPTCONTROLLER)) {
		perror("Sensor: request failed");
		unregisterChannel(SENSOR);
		return;
	}
	Message * m = (Message *) malloc(sizeof(Message));
	Message * r_msg = (Message*) malloc(sizeof(Message));
	if (r_msg == NULL) {
		perror("Sensor: failed to get Space for Receive Message.");
		unregisterChannel(SENSOR);
		cleanUp(0, NULL,NULL);
		destroyChannel(chid);
		return;
	}
	if (m == NULL) {
		perror("Sensor: failed to get Space for Message.");
		unregisterChannel(SENSOR);
		cleanUp(0,NULL,r_msg);
		destroyChannel(chid);
		return;
	}
	id = getChannelIdForObject(INTERRUPTCONTROLLER);
	if (!attachConnection(id, INTERRUPTCONTROLLER)) {
		perror("Sensor: failed to AttachConnection!");
		unregisterChannel(SENSOR);
		cleanUp(0,m,r_msg);
		destroyChannel(chid);
		return;
	}
	//cout << "Sensor: attached Connection" << endl;
	coid = getConnectIdForObject(INTERRUPTCONTROLLER);
	buildMessage(m, chid, coid, startConnection, SENSOR);
	//cout << "Sensor: message Build" << endl;
	if (-1 == MsgSend(coid, m, sizeof(Message), r_msg, sizeof(Message))) {
		perror("Sensor: failed to send message to IC!");
		unregisterChannel(SENSOR);
		cleanUp(coid,m,r_msg);
		destroyChannel(chid);
		return;
	}//*/
	//cout << "Sensor: message Send successful!" << endl;
	if (-1 == (id = getChannelIdForObject(INTERRUPTCONTROLLER))) {
		perror("Sensor: failed to get ChannelId!");
		unregisterChannel(SENSOR);
		cleanUp(coid,m,r_msg);
		destroyChannel(chid);
		return;
	}
	//cout << "Sensor: Channel id of IC: " << id << endl;#
	while (!isStopped()) {
		rcvid = MsgReceive(chid,r_msg, sizeof(Message), NULL);
		coid = getConnectIdForObject(INTERRUPTCONTROLLER);
		buildMessage(m, (*r_msg).m.chid, coid, OK, SENSOR);

		if (-1 == MsgReply(rcvid, 0, m, sizeof(Message))) {
			perror("Sensor: failed to send reply message to IC!");
		}

		if ((*r_msg).m.ca == react) {
			port = INTERRUPT_D_PORT_B;
		} else {
			port = INTERRUPT_D_PORT_C_HIGH;
		}
		int val = (*r_msg).pulse.value.sival_int;
		//cout << "Interrupt " << "val:" << val << " port "  << (*r_msg).m.ca << endl;

		switch (port) {
		case INTERRUPT_D_PORT_B:
			if ( !(val&1) ) {
				cout << "Sensor: in" << endl;
				int ls7blocked = 0;
				for(unsigned int i=0; i<wp_list.size(); i++){
					if (wp_list[i]->isOnLS7){
						ls7blocked = 1;
					}
				}
				if (ls7blocked == 0 ) wp_list.push_back(new Machine2);
				for(unsigned int i=0; i<wp_list.size(); i++)	wp_list[i]->ls_b0();
			}
			if ( !((val>>1)&1) ) {
				cout << "Sensor: in height measure " << endl;
				for(unsigned int i=0; i<wp_list.size(); i++)	wp_list[i]->ls_b1();

			}
			if ( !((val >> 3)&1) ) {
					cout << "Sensor: in metal measure" << endl;
					for(unsigned int i=0; i<wp_list.size(); i++)	wp_list[i]->ls_b3();

			}
			if ( !((val>>6)&1) ) {
				cout << "Sensor: in slide" << endl;
				for(unsigned int i=0; i<wp_list.size(); i++)	wp_list[i]->ls_b6();
				int active_state = 0;
				for(unsigned int i=0; i<wp_list.size(); i++){
					if (wp_list[i]->engine_should_be_started){
						active_state = 1;
					}
				}
				if (active_state == 1 ){
					(*cc).engineReset();
					(*cc).engineRight();
				}

			}
			if (!(val & BIT_WP_OUTLET)) {
				cout << "Sensor: end of band in" << endl;
				for(unsigned int i=0; i<wp_list.size(); i++)	wp_list[i]->ls_b7_in();

			}
			if ((val & BIT_WP_OUTLET) && !(last_Reg_State_B & BIT_WP_OUTLET)) {
				cout << "Sensor: end of band out" << endl;
				for(unsigned int i=0; i<wp_list.size(); i++)	wp_list[i]->ls_b7_out();

				int active_state = 0;
				for(unsigned int i=0; i<wp_list.size(); i++){
					if (wp_list[i]->engine_should_be_started){
						active_state = 1;
					}
				}
				if (active_state == 1 ){
					(*cc).engineReset();
					(*cc).engineRight();
				}

			}
			last_Reg_State_B = val;
			break;
		case INTERRUPT_D_PORT_C_HIGH:
			if (!(val & BIT_E_STOP) && (last_Reg_State_C & BIT_E_STOP) ) {
				//(*cc).emergencyStop();
				cout << "Sensor: E-Stop Button in" << endl;
			}else if ((val & BIT_E_STOP) && !(last_Reg_State_C & BIT_E_STOP) ){
				cout << "Sensor: E-Stop Button out" << endl;
			} else if (!(val & BIT_STOP)) {
				//(*cc).stopMachine();
				cout << "Sensor: stop Button" << endl;
			} else if (val & BIT_START) {
				cout << "Sensor: Start Button" << endl;
				//cnt = 0;
				//(*cc).restart();
			} else if (val & BIT_RESET) {
				cout << "Sensor: Reset Button" << endl;
				//cnt = 0;
				//(*cc).resetAll();
			}
			//(*cc).setValueOfPort(PORT_C,val);
			last_Reg_State_C = val;
			break;
		}


		#ifndef TEST_SEN
				//interrupt(port,(*r_msg).pulse.value.sival_int);
		#endif

		#ifdef TEST_SEN
				ts.test_sen_interrupt(p, (*r_msg).pulse.value.sival_int);
		#endif



	}//while

	if (!detachConnection(id,coid,SENSOR)) {
		perror("Sensor: failed to detach Channel for Interrupt\n");
		unregisterChannel(SENSOR);
		cleanUp(coid,m,r_msg);
		destroyChannel(chid);
		return;
	}
	if (!unregisterChannel(SENSOR)) {
		perror("Sensor: register channel failed!");
		cleanUp(coid,m,r_msg);
	}
	cleanUp(0,m,r_msg);
	destroyChannel(chid);

}

void Sensor::shutdown() {

}

void Sensor::interrupt(int port, int val) {

	switch (port) {
	case INTERRUPT_D_PORT_B:
		if (!(val & BIT_WP_IN_HEIGHT)) {
			cout << "Sensor: WP_IN_H " << endl;
		}
		if (!(val & BIT_WP_RUN_IN)) {
			(*cc).engineRight();
			cout << "Sensor: BIT_WP_RUN_IN" << endl;
		}

		if (val & BIT_WP_IN_SWITCH) {
			if (val & BIT_SWITCH_STATUS) {
				(*cc).closeSwitch();
				cout << "Sensor: closes switch " << endl;
			}
		} else {
			if (val & BIT_WP_METAL) {
				//cout << " ist metall " << endl;
				if (!(val & BIT_SWITCH_STATUS)) {
					(*cc).openSwitch();
					cout << "Sensor: opens switch " << endl;
				}
				cout << "Sensor: ist Metall :D" << endl;
			}
		}
		if (!(val & BIT_WP_IN_SLIDE)) {
			cnt++;
			if(cnt == 4){
				cnt = 0;
				(*cc).shine(RED);
				(*cc).stopMachine();
			}

		}
		if (!(val & BIT_WP_OUTLET)) {
			//(*cc).engineReset();
			cout << "Sensor: somethings coming out ;)" << endl;
		}
		(*cc).setValueOfPort(PORT_B,val);
		break;
	case INTERRUPT_D_PORT_C_HIGH:
		if (!(val & BIT_E_STOP)) {
			(*cc).emergencyStop();
		} else if (!(val & BIT_STOP)) {
			(*cc).stopMachine();
		} else if (val & BIT_START) {
			cnt = 0;
			(*cc).restart();
		} else if (val & BIT_RESET) {
			cnt = 0;
			(*cc).resetAll();
		}
		(*cc).setValueOfPort(PORT_C,val);
		break;
	}


}

bool Sensor::get_Band_has_wp_ls7(){
 return is_Band_has_wp_ls7;
}

void Sensor::set_Band_has_wp_ls7(bool b){
	is_Band_has_wp_ls7 = b;
}
