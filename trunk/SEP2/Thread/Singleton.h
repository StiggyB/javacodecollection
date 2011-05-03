
#ifndef SINGLETON_H_
#define SINGLETON_H_

#include "Mutex.h"
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
class Singleton {
public:
	static Singleton* getInstance();
	static void deleteInstance();
protected:
	Singleton();
	virtual ~Singleton();
private:
	/**
	 * for Singleton
	 */
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	/**
	 * Pointer for singleton CoreController
	 */
	static Singleton* pInstance;
	/**
	 * Pointer for singleton CoreController Instance
	 */
	static Mutex singleton;
};

#endif /* SINGLETON_H_ */
