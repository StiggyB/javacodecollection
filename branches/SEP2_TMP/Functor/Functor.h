/*
 * FunctorSimple.h
 *
 *  Created on: 12.05.2011
 *      Author: Tell
 */

#ifndef FUNCTORSIMPLE_H_
#define FUNCTORSIMPLE_H_

#include "CallInterface.h"

template<typename T, typename R, typename P>
class Functor : public CallInterface<T, R, P>
{

public:
	//Type definition: pointer to a member- function
	typedef R(T:: *pMemFunc)(P);

private:
	T* pMemObj_;
	pMemFunc objFuncp_;

public:
	Functor(T* pMemObj, R(T:: *objFuncp)(P))
	:pMemObj_(pMemObj), objFuncp_(objFuncp)
	{
	}

	R operator()(P param) {
		return (*pMemObj_.*objFuncp_)(param);
	}

	R call(P param) {
		return (*pMemObj_.*objFuncp_)(param);
	}

};


#endif /* FUNCTORSIMPLE_H_ */
