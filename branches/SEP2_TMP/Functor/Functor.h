/**
 * Functor Pattern.
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Contains functions which provide a generic Callback with
 * dynamic object type, return type and parameter type.
 *
 */

#ifndef FUNCTORSIMPLE_H_
#define FUNCTORSIMPLE_H_

#include "CallInterface.h"

template<typename T, typename R, typename P>
class Functor: public CallInterface<T, R, P> {

public:
	/**
	 * Type definition: pMemFunc is a pointer to a member- function.
	 */
	typedef R(T::*pMemFunc)(P);

private:
	/**
	 * Pointer on an object from type T.
	 */
	T* pMemObj_;
	/**
	 * Function pointer on a member function from type pMemFunc.
	 */
	pMemFunc objFuncp_;

public:
	/**
	 * Constructor from the class Functor which
	 * initialize the attributes pMemObj and objFuncp
	 * \param pMemObj is a pointer on a instance from type T.
	 * \param objFuncp is a function pointer from
	 * 	type T with param P and return type R.
	 */
	Functor(T* pMemObj, R(T::*objFuncp)(P)) :
		pMemObj_(pMemObj), objFuncp_(objFuncp) {
	}

	/**
	 * Provides a dynamic choose of function pointers.
	 * \param a generic P, represents the parameter.
	 * \return a generic R, represents the return value.
	 */
	R operator()(P param) {
		return (*pMemObj_.*objFuncp_)(param);
	}

	/**
	 * Provides a dynamic choose of function pointers.
	 * \param a generic P, represents the parameter.
	 * \return a generic R, represents the return value.
	 */
	R call(P param) {
		return (*pMemObj_.*objFuncp_)(param);
	}

};

#endif /* FUNCTORSIMPLE_H_ */
