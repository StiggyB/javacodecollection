/**
 * Singleton Class - Template Try
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

#include "Singleton_Template.h"

template <class T>
Mutex Singleton_T<T>::singleton;

template <class T>
Singleton_T<T>* Singleton_T<T>::pInstance = NULL;

template <class T>
Singleton_T<T> :: Singleton_T(){

}

template <class T>
Singleton_T<T> :: ~Singleton_T(){

}

template <class T>
T* Singleton_T<T>::getInstance() {
	if (!pInstance) {
		singleton.lock();
		if (!pInstance) {
			pInstance = new Singleton_T<T>;
		}
		singleton.unlock();
	}
	return pInstance;
}
template <class T>
void Singleton_T<T>::deleteInstance(){
	if( pInstance != NULL ){
		singleton.lock();
		if( pInstance != NULL ){
			delete pInstance;
			pInstance = NULL;
		}
		singleton.unlock();
	}
}
