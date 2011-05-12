/*
 * CallInterface.h
 *
 *  Created on: 12.05.2011
 *      Author: Tell
 */

#ifndef CALLINTERFACE_H_
#define CALLINTERFACE_H_

namespace call {

class CallInterface {
public:
	CallInterface();
	~CallInterface();
	virtual void callback() = 0;
};
};

#endif /* CALLINTERFACE_H_ */
