/**
 * Light Control
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Provides some possibilities to activate the lights.
 *
 * Inherits: HAWThread, Communication
 */

#include "Lampen.h"

Lampen::Lampen() {
	/**
	 * gaining IO privileges
	 */
	if (-1==ThreadCtl(_NTO_TCTL_IO, 0)) {
		std::cout << "Lampen: Error for IO Control" << std::endl;
	}
	/**
	 * Gets a pointer to an instance of the CoreController
	 */
	if(h == NULL) h = HALCore::getInstance();
	running = false;
	for(unsigned int i = 0; i < sizeof(array)/sizeof(struct lights); i++){
		setTime((Color)i,-1,-1,false,false);
	}
}

Lampen::~Lampen() {
	h = NULL;
}

void Lampen::execute(void*) {
	int time = 0;
	int lights = 0;
	while(!isStopped()){
		mlight.lock();
		lights = calcLights();
		//cout << "Lampen: lights:" << lights << endl;
		h->shine(lights);
		time = calcTime();
		//cout << "Lampen: time:" << time << endl;
		mlight.unlock();
		delay(time);
	}
}

void Lampen::shutdown() {

}

void Lampen::flash(int period, Color color) {
	mlight.lock();
	addTime(color, period);
	mlight.unlock();
}

void Lampen::flash(int period, int duration, Color col) {
	mlight.lock();
	addTime(col, period, duration);
	mlight.unlock();
}

void Lampen::addLight(Color col) {
	mlight.lock();
	//cout << "added light " << col << endl;
	addTime(col,-1);
	mlight.unlock();
}

void Lampen::removeLight(Color col) {
	mlight.lock();
	removeTime(col);
	mlight.unlock();
}

void Lampen::shine(Color col) {
	mlight.lock();
	removeAllTime();
	addTime(col,-1);
	mlight.unlock();
}

int Lampen::getNextTime(){
	int a = (array[0].time == -1? 1000 : array[0].time);
	int b = (array[1].time == -1? 1000 : array[1].time);
	int c = (array[2].time == -1? 1000 : array[2].time);
	return getMin(a,b,c);
}

int Lampen::getMin(int a, int b, int c){
	return (a < b)?(a < c ? a : (b < c ? b : c)):(b< c? b : c);
}

bool Lampen::isActiv(Color col){
	return array[col].activ;
}

bool Lampen::hasTime(Color col, int time){
	return array[col].time == time;
}

void Lampen::addTime(Color col, int period, int duration){
	setTime(col,period,duration,true,true);
}

void Lampen::addTime(Color col,int period){
	setTime(col,period,-1,true,true);
}

void Lampen::removeTime(Color col){
	setTime(col,0,0,false,false);
}

void Lampen::setTime(Color col,int period,int duration, bool activity, bool status){
	array[col].col = col;
	array[col].time = period;
	array[col].period = period;
	array[col].duration = duration;
	array[col].activ = activity;
	array[col].on = status;
}

void Lampen::removeAllTime(){
	for(unsigned int i = 0; i < sizeof(array)/sizeof(struct lights); i++){
		removeTime((Color) i);
	}
}

int Lampen::calcLights(){
	int lights = 0;
	for(unsigned int i = 0; i < sizeof(array)/sizeof(struct lights); i++){
		if(array[i].time == 0 && array[i].activ){
			array[i].on = !array[i].on;
			array[i].time = array[i].period;
		}
		if(array[i].on){
			lights |= getBitToColor(array[i].col);
		}
	}
	return lights;
}
int Lampen::getBitToColor(Color col){
	int color = 0;
	switch(col){
	case RED:
		color = BIT_LIGHT_RED;
		break;
	case GREEN:
		color = BIT_LIGHT_GREEN;
		break;
	case YELLOW:
		color = BIT_LIGHT_YELLOW;
		break;
	default:
		color = 0;
		break;
	}
	return color;
}

int Lampen::calcTime(){
	int time = getNextTime();
	time = ( (time > 1000 || time < 0 )? 1000 : time);
	for(unsigned int i = 0; i < sizeof(array)/sizeof(struct lights); i++){
		if(array[i].time != -1) array[i].time -= time; // only if not unlimited duration
		if(array[i].duration != -1){ // only if not unlimited duration
			if(array[i].duration == 0){ // duration exceeded... deactivate
				array[i].activ = false;
				array[i].on = false;
				array[i].time = -1;
				array[i].period = -1;
			}else{
				array[i].duration -= time;
			}
		}
	}
	return time;
}
