
#ifndef IFUNCTOR_H_
#define IFUNCTOR_H_

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
template <typename T, typename R>
class CallInterface {

public:

	/**
	 * Provides a dynamic choose of function pointers.
	 * \return a generic R, represents the return value.
	 */
	virtual R operator()() = 0;

	/**
	 * Provides a dynamic choose of function pointers.
	 * \return a generic R, represents the return value.
	 */
	virtual R call() = 0;

};

#endif /* IFUNCTOR_H_ */
