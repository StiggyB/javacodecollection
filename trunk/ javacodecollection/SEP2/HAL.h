/*
 * HAL.h
 *
 *  Created on: 31.03.2011
 *      Author: Administrator
 */

#ifndef HAL_H_
#define HAL_H_

//PORT A:
#define BIT_ENGINE_RIGHT (0x00)
#define BIT_ENGINE_LEFT (1<<1)
#define BIT_ENGINE_SLOW (1<<2)
#define BIT_ENGINE_STOP (1<<3)
#define BIT_ENGINE_S_L (0x05)
#define BIT_ENGINE_S_R (0x06)
#define BIT_SWITCH (1<<4)
#define BIT_LIGHT_YELLOW (0x40)
#define BIT_LIGHT_GREEN (0x20)
#define BIT_LIGHT_RED (0x80)
#define BIT_LIGHT_OFF (0x00)
#define BIT_LIGHTS_ON (0xE0)

//PORT B:
#define BIT_WP_RUN_IN (1<<0)
#define BIT_WP_IN_HEIGHT (1<<1)
#define BIT_HEIGHT_1 (1<<2)
#define BIT_WP_IN_SWITCH (1<<3)
#define BIT_WP_METAL (1<<4)
#define BIT_SWITCH_OPEN (1<<5)
#define BIT_SLIDE_FULL (1<<6)
#define BIT_WP_OUTLET (1<<7)

//PORT C:
#define BIT_LED_START (1<<0)
#define BIT_LED_RESET (1<<1)
#define BIT_LED_Q1 (1<<2)
#define BIT_LED_Q2 (1<<3)
#define BIT_START (1<<4)
#define BIT_STOP (1<<5)
#define BIT_RESET (1<<6)
#define BIT_E_STOP (1<<7)

//PORT ADDRESS
#define PORT_A (D_IOBASE +0x00)
#define PORT_B (D_IOBASE +0x01)
#define PORT_C (D_IOBASE +0x02)
#define PORT_CNTRL (D_IOBASE +0x03)

//CONTROLBITS
#define BIT_PORT_A (0x10)
#define BIT_PORT_B (0x02)
#define BIT_PORT_C (0x09)
#define BIT_PORT_C_LOW (0x08)
#define BIT_PORT_C_HIGH (0x01)

#define BIT_CNTRLS (0x8A) // Standard: 1000 1010 ( D0 - C Low, D1 - B, D3 - C High, D4 - A)

//BASE ADRESS
#define D_IOBASE 0x300 								// Anfangsadresse Ports
#define DIGITAL_CARD_CONTROL (D_IOBASE + 0x03) 		// Adresse von Card Control
#define DIGITAL_CARD_CROUP0_PORTA (D_IOBASE + 0x00) // Adresse von Port A


#include <wrappers.h>
#include "HWaccess.h"

class HAL {
public:
	int controlBits;

	HAL();
	virtual ~HAL();

	int read(int dir);
	void write(int dir, int value);
	void setPortsTo(int cb);
	void resetPortsDirection();
	bool isInput(int dir);
	bool isOutput(int dir);
	int setPortToOutput(int bits);
	int setPortToInput(int bits);
	int getBitsToAdress(int dir);

};

#endif /* HAL_H_ */
