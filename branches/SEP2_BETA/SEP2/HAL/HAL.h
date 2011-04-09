/*
 * HAL.h
 *
 *  Created on: 08.04.2011
 *      Author: Administrator
 */

#ifndef HAL_H_
#define HAL_H_

#include <iostream>
#include <unistd.h>
#include "HWaccess.h"
#include "../Thread/Mutex.h"

//PORT A:
#define BIT_ENGINE_RIGHT (1<<0)
#define BIT_ENGINE_LEFT (1<<1)
#define BIT_ENGINE_SLOW (1<<2)
#define BIT_ENGINE_STOP (1<<3)
#define BIT_ENGINE_S_L (0x06)
#define BIT_ENGINE_S_R (0x05)
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
#define BIT_PORT_A (1<<4)
#define BIT_PORT_B (1<<1)
#define BIT_PORT_C (BIT_PORT_C_LOW + BIT_PORT_C_HIGH)
#define BIT_PORT_C_LOW (1<<0)
#define BIT_PORT_C_HIGH (1<<3)

#define BIT_CNTRLS (0x82) // Standard: 1000 1010 ( D0 - C Low, D1 - B, D3 - C High, D4 - A)
#define BIT_DELETE (false)
#define BIT_SET (true)
//BASE ADRESS
#define D_IOBASE 0x300 								// Anfangsadresse Ports
#define DIGITAL_CARD_CONTROL (D_IOBASE + 0x03) 		// Adresse von Card Control
#define DIGITAL_CARD_CROUP0_PORTA (D_IOBASE + 0x00) // Adresse von Port A
#define INTERRUPT_SET_ADRESS (D_IOBASE + 0xB)
#define INTERRUPT_RESET_ADRESS (D_IOBASE + 0xF)
#define PORT_IRE INTERRUPT_SET_ADRESS
#define PORT_IRQ INTERRUPT_RESET_ADRESS
#define PORT_IRQ_AND_RESET (D_IOBASE + 0x18)
#define IIR_MASK 0x7

// Interrupts
#define INTERRUPT_PORT_A (1<<0)
#define INTERRUPT_PORT_B (1<<1)
#define INTERRUPT_PORT_C (1<<2)
#define INTERRUPT_PORT_C_HIGH (1<<3)
#define INTERRUPT_VECTOR_NUMMER (11)
#define SENSOR_PULSE_CODE 0x01

//Variablen
extern const struct sigevent * ISR(void *arg, int id);
extern volatile int portA;
extern volatile int portB;
extern volatile int portC;
extern volatile int portIRE;
extern volatile int portIRQ;
extern volatile int controlBits;

//Farben Enum
enum Color {
	RED, GREEN, YELLOW, OFF
};

/**
 * Hardware Abstraction Layer for Aktorik and Sensorik.
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Milestone 2: HAL Aktorik
 * Milestone 3: HAL Sensorik
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Capsulates many functions for the direct
 * in- and output from and to the Festo Transfersystem and
 * with Interrupts using Pulse Messages.
 */
class HAL {

public:
	static HAL* getInstance();
	int read(int dir);
	int write(int dir, int value, bool overwrite);
	void setPortsTo(int cb);
	void resetPortsDirection();
	bool isInput(int dir);
	bool isOutput(int dir);
	int setPortToOutput(int bits);
	int setPortToInput(int bits);
	int getValueToAdress(int dir);
	int getBitsToAdress(int dir);
	int write(int dir, int value);
	int reset(int dir, int value);
	int checkVal(int dir, int value, bool set);
	void engineStart(int direction);
	void openSwitch();
	void closeSwitch();
	void setSwitchDirection(bool dir);
	void engineReset();
	void engineStop();
	void engineContinue();
	void engineRight();
	void engineLeft();
	void engineSlowSpeed();
	void engineNormalSpeed();
	bool engineStopped();
	void engineSlowSpeed(int dir);
	void engineSpeed(bool slow);
	void engineSlowLeft();
	void engineSlowRight();
	void activateInterrupt(int port);
	void deactivateInterrupt(int port);
	void attachISR(void * arg);
	int getSetInterrupt();
	int getInterrupt();
	void resetAllOutPut();

	int getColorCode(Color col);
	void removeLight(Color col);
	void addLight(Color col);
	void shine(Color col);
	void shine(int color);

private:
	HAL();
	virtual ~HAL();
	static HAL* instance;
	static Mutex mutEx;
};

#endif /* HAL_H_ */