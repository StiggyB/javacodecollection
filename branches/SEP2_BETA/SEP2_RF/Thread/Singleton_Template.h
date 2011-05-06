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

#ifndef SINGLETON_T_H_
#define SINGLETON_T_H_

#include "Mutex.h"
template <class T>
class Singleton_T {
public:
	static T* getInstance();
	static void deleteInstance();
protected:
	Singleton_T();
	virtual ~Singleton_T();
private:
	/**
	 * for Singleton
	 */
	Singleton_T(const Singleton_T&);
	Singleton_T& operator=(const Singleton_T&);
	/**
	 * Pointer for singleton CoreController
	 */
	static Singleton_T* pInstance;
	/**
	 * Pointer for singleton CoreController Instance
	 */
	static Mutex singleton;
};

#endif /* SINGLETON_T_H_ */
