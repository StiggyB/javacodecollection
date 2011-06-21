/*
 * GlobalVariables.h
 *
 *  Created on: 21.06.2011
 *      Author: aax691
 */

#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_

#include "../Thread/Singleton_T.h"

enum machineType {
	PUCK_FSM_1_,
	PUCK_FSM_2_
};

class GlobalVariables : public Singleton_T<GlobalVariables>{
	friend class Singleton_T<GlobalVariables>;
public:
	GlobalVariables();
	virtual ~GlobalVariables();
    machineType getCurrentType();
    void setCurrentType(machineType currentType);

private:
	machineType currentType;

};

#endif /* GLOBALVARIABLES_H_ */
