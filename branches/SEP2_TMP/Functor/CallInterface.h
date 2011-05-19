/*
 * IFunctor.h
 *
 *  Created on: 17.05.2011
 *      Author: Tell
 */

#ifndef IFUNCTOR_H_
#define IFUNCTOR_H_

template <typename T, typename R, typename P>
class CallInterface {

public:

	virtual R operator()(P param) = 0;
	virtual R call(P param) = 0;

};

#endif /* IFUNCTOR_H_ */
