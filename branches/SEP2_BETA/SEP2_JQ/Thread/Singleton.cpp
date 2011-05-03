/**
 * Singleton Class
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * implements the functionality for a threadsafe and erasable singleton pattern
 *
 *
 */
#include "Singleton.h"

Mutex Singleton::singleton;

Singleton* Singleton::pInstance = NULL;

Singleton :: Singleton(){

}

Singleton:: ~Singleton(){

}

Singleton* Singleton::getInstance() {
	if (!pInstance) {
		singleton.lock();
		if (!pInstance) {
			pInstance = new Singleton;
		}
		singleton.unlock();
	}
	return pInstance;
}

void Singleton::deleteInstance(){
	if( pInstance != NULL ){
		singleton.lock();
		if( pInstance != NULL ){
			delete pInstance;
			pInstance = NULL;
		}
		singleton.unlock();
	}
}
