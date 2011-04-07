/*
 * HW_test.h
 *
 *  Created on: 31.03.2011
 *      Author: aaw323
 */

#ifndef HW_TEST_H_
#define HW_TEST_H_

#include <unistd.h>
#include "HAWThread.h"
#include <HAL.h>
#include "Lampen.h"

#define D_IOBASE 0x300 								// Anfangsadresse Ports
#define DIGITAL_CARD_CONTROL (D_IOBASE + 0x03) 		// Adresse von Card Control
#define DIGITAL_CARD_CROUP0_PORTA (D_IOBASE + 0x00) // Adresse von Port A

class HW_test : public thread::HAWThread {
public:
	HW_test();
	virtual ~HW_test();
	HAL h;
protected:
	virtual void execute(void*);
	virtual void shutdown();
};


#endif /* HW_TEST_H_ */
