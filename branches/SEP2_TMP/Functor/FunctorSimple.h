/*
 * FunctorSimple.h
 *
 *  Created on: 12.05.2011
 *      Author: Tell
 */

#ifndef FUNCTORSIMPLE_H_
#define FUNCTORSIMPLE_H_

template<class T>
class FunctorSimple {
public:
	void operator()();
	FunctorSimple(T& pMemObj, T objFuncp);
	~FunctorSimple();
private:
	T objFuncp;
	T& pMemObj;
};

#endif /* FUNCTORSIMPLE_H_ */
