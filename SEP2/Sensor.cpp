/*
 * Sensor.cpp
 *
 *  Created on: 05.04.2011
 *      Author: MQR
 */

#include "Sensor.h"
#include "HAL.h"

volatile struct sigevent event;
const struct sigevent *eventptr = (const struct sigevent*) &event;


Sensor::Sensor() {
	h = HAL::getInstance();
	activateInterrupts();
}

Sensor::~Sensor() {

}

void Sensor::activateInterrupts(){
	(*h).activateInterrupt(PORT_B);
}

void Sensor::connectToHAL(){
	chid = ChannelCreate(0);
	if(chid == -1){
		perror("Sensor: failed to create Channel for Interrupt\n");
		shutdown();
	}
	coid = ConnectAttach(0,0,chid, _NTO_SIDE_CHANNEL,0);
	//const struct sigevent volatile *evptr = &event;
	SIGEV_PULSE_INIT(&event,coid,SIGEV_PULSE_PRIO_INHERIT,SENSOR_PULSE_CODE,0);
	ThreadCtl(_NTO_TCTL_IO,0);
	cout << "Sensor: Interrupt will be attached." << endl;
	interruptId = InterruptAttach(HW_SERIAL_IRQ,ISR,eventptr,sizeof(event),0);
	if(interruptId == -1 ){
		perror("Sensor: failed to create ISR coupling\n");
		shutdown();
	}
	cout << "Sensor: Interrupt Attached to event with coid="<<coid << endl;
}
void Sensor::execute(void*){
	connectToHAL();
	handlePulseMessages();
}

void Sensor::handlePulseMessages(){
	int rcvid;
	while(1){
		cout << "Sensor: waiting for Pulse"<<endl;
		rcvid = MsgReceivePulse(chid,&pulse,sizeof(pulse),NULL);
		cout << "Sensor: Pulse received"<<endl;
		if(rcvid == -1){
			perror("Sensor: failed to get MsgPulse\n");
			shutdown();
		}
		cout << "Sensor: pulse code: " << pulse.code << endl;
	}
}

void Sensor::shutdown(){

}
