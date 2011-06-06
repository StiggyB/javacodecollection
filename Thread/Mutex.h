
#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

/**
 * Mutex
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Mutex for a threadsafe implementation.
 *
 */
class Mutex {

public:
	Mutex();
	virtual ~Mutex();
	/**
	 * Locks the Mutex.
	 */
	void lock();
	/**
	 * Unlocks the Mutex.
	 */
	void unlock();
	/**
	 * Get an Pointer to the Mutex
	 */
	pthread_mutex_t* getMutex();
private:
	/**
	 * Pthread-Mutex
	 */
	pthread_mutex_t mutex;
	Mutex (const Mutex &);
	Mutex& operator= (const Mutex&);

};

#endif /* MUTEX_H_ */
