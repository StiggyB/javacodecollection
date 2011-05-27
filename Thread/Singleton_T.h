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
 */

#ifndef SINGLETON_T_H_
#define SINGLETON_T_H_

#include "Mutex.h"


template <class T>
class Singleton_T {
protected:
	Singleton_T() {}
	//virtual ~Singleton_T();
private:
	/**
	 * for Singleton
	 */
	Singleton_T(const Singleton_T&);
	Singleton_T& operator=(const Singleton_T&);
	/**
	 * Pointer for singleton CoreController
	 */
	static T* pInstance;
	/**
	 * Pointer for singleton CoreController Instance
	 */
	static Mutex singleton;
public:
	static T* getInstance();
	static void deleteInstance();
};
template <class T>
Mutex Singleton_T<T>::singleton;

template <class T>
T* Singleton_T<T>::pInstance = NULL;


template <class T>
T* Singleton_T<T>::getInstance() {
	if (!pInstance) {
		singleton.lock();
		if (!pInstance) {
			pInstance = new T();
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

#endif /* SINGLETON_T_H_ */
