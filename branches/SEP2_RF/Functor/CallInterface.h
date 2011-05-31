/**
 * Interface for the Functor Pattern.
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Encapsulates functions for the Functor Pattern.
 * These functions provide a generic Callback with
 * dynamic object type, return type and parameter type.
 *
 */

#ifndef IFUNCTOR_H_
#define IFUNCTOR_H_

template <typename T, typename R, typename P>
class CallInterface {

public:

	/**
	 * Provides a dynamic choose of function pointers.
	 * \param a generic P, represents the parameter.
	 * \return a generic R, represents the return value.
	 */
	virtual R operator()(P param) = 0;

	/**
	 * Provides a dynamic choose of function pointers.
	 * \param a generic P, represents the parameter.
	 * \return a generic R, represents the return value.
	 */
	virtual R call(P param) = 0;

};

#endif /* IFUNCTOR_H_ */
