/**
 * Communication
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Capsulates many functions for the direct
 * connection of components via Messages.
 * symbolic: auskunft f�r die channelid's
 */

#include "Communication.h"


//TODO Destroy Com-Singleton correctly

Communication::Communication() : vc(10) {

}

Communication::~Communication() {

}

int Communication::getComObject(Com c){
	int chid = 0;
	return chid;
}