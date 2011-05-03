#ifndef HAL_H_
#define HAL_H_

#include <iostream>
#include <unistd.h>
#include "IHAL.h"
#include "HWaccess.h"
#include "../Thread/Mutex.h"
#include "../Controller/Communication.h"

/**
 * Delete a bit
 */
#define BIT_DELETE (false)
/**
 * Set a bit
 */
#define BIT_SET (true)

/**
 * BASE ADRESS for Digital IO
 */
#define D_IOBASE 0x300 								// Anfangsadresse Ports
/**
 * BASE ADRESS for Analog IO
 */
#define A_IOBASE 0x320

/**
 * PORT A:
 */
enum PortA{
	BIT_ENGINE_RIGHT = (1<<0), BIT_ENGINE_LEFT = (1<<1), BIT_ENGINE_SLOW = (1<<2), BIT_ENGINE_STOP = (1<<3),
	BIT_SWITCH = (1<<4),BIT_LIGHT_GREEN = (1<<5),BIT_LIGHT_YELLOW = (1<<6),BIT_LIGHT_RED = (1<<7),
	BIT_ENGINE_S_L = (0x06), BIT_ENGINE_S_R = (0x05), BIT_LIGHT_OFF = (0x00), BIT_LIGHTS_ON = (0xE0)
};

/**
 * PORT B:
 */

enum PortB{
	BIT_WP_RUN_IN = (1<<0),BIT_WP_IN_HEIGHT = (1<<1),BIT_HEIGHT_1 = (1<<2),BIT_WP_IN_SWITCH = (1<<3),
	BIT_WP_METAL = (1<<4),BIT_SWITCH_OPEN = (1<<5),BIT_SLIDE_FULL = (1<<6),BIT_WP_OUTLET = (1<<7)
};

/**
 * PORT C:
 */
enum PortC{
	BIT_LED_START=(1<<0),BIT_LED_RESET=(1<<1),BIT_LED_Q1=(1<<2),BIT_LED_Q2=(1<<3),BIT_START=(1<<4),BIT_STOP=(1<<5),BIT_RESET=(1<<6),BIT_E_STOP=(1<<7),BIT_LEDS_ON=(0x0F)
};

/**
 * PORT ADDRESS:
 */
enum PortAdress{
	PORT_A = (D_IOBASE +0x00), PORT_B = (D_IOBASE +0x01), PORT_C = (D_IOBASE +0x02), PORT_CNTRL = (D_IOBASE +0x03)
};

/**
 * CONTROLBITS:
 */
enum ControlBits {
	BIT_PORT_A = (1<<4),BIT_PORT_B = (1<<1),BIT_PORT_C = ((1<<0) + (1<<3)),BIT_PORT_C_LOW = (1<<0),BIT_PORT_C_HIGH = (1<<3), BIT_CNTRLS = (0x8A)
};

/**
 * Height Measures
 */
enum Height{
	HEIGHT_MEASURE = (A_IOBASE + 0x02), HEIGHT_START_CODE = (0x10)
};

/**
 *  interrupts
 */
enum Interrupts_D{
	INTERRUPT_D_PORT_A = (1<<0),INTERRUPT_D_PORT_B = (1<<1),INTERRUPT_D_PORT_C = (1<<2),INTERRUPT_D_PORT_C_HIGH = (1<<3),
	INTERRUPT_VECTOR_NUMMER_A = 14, INTERRUPT_VECTOR_NUMMER_D = 11,
	INTERRUPT_SET_ADRESS_D = (D_IOBASE + 0xB),INTERRUPT_RESET_ADRESS_D = (D_IOBASE + 0xF),PORT_IRE =(D_IOBASE + 0xB),
	PORT_IRQ = (D_IOBASE + 0xF),PORT_IRQ_AND_RESET = (D_IOBASE + 0x18), IIR_MASK_D = 0xF
};

/**
 * PULS Codes
 */
enum PULSE_CODE{
	LICHTSCHRANKE,HEIGHT
};

/**
 * Interrupt Service Routine
 */
extern const struct sigevent * ISR(void *arg, int id);
/**
 * Port A: contains the byte of Port A
 */
extern volatile int portA;
/**
 * Port B: contains the byte of Port B
 */
extern volatile int portB;
/**
 * Port C: contains the byte of Port C
 */
extern volatile int portC;
/**
 * Port IRE: contains the byte of Port IRE
 */
extern volatile int portIRE;
/**
 * Port IRQ: contains the byte of Port IRQ
 */
extern volatile int portIRQ;
/**
 * Port ControlBits: contains the byte of Port ControlBits
 */
extern volatile int controlBits;

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
 *
 * Inherits: IHAL.h
 */
class HAL: public IHAL {
public:
	/*!
	 * returns a Pointer to the threadsafe Singleton Instance of the Hardware Abstraction Layer (HAL)
	 * \return a Pointer to HAL.
	 */
	static HAL* getInstance();
	/**
	 * deletes the Instance
	 */
	static void deleteInstance();
	/**
	 * activates the light specified by color
	 * \param color an integer, specifying the color.
	 * \return a bool, true if action was successful, false if not.
	 */
	bool shine(int color);
	/**
	 * activates the LED specified by led
	 * \param led an integer, specifying the Led which should be activated.
	 * \return a bool, true if action was successful, false if not.
	 */
	bool shineLED(int led);

	//IHAL:
	virtual int read(int dir);
	virtual bool isInput(int dir);
	virtual bool isOutput(int dir);
	virtual int write(int dir, int value);
	virtual int reset(int dir, int value);
	virtual bool engineStart(int direction);
	virtual bool openSwitch();
	virtual bool closeSwitch();
	virtual bool setSwitchDirection(bool dir);
	virtual bool engineStop();
	virtual bool engineReset();
	virtual bool engineContinue();
	virtual bool engineRight();
	virtual bool engineLeft();
	virtual bool engineSlowSpeed();
	virtual bool engineNormalSpeed();
	virtual bool engineStopped();
	virtual bool engineSlowSpeed(int dir);
	virtual bool engineSpeed(bool slow);
	virtual bool engineSlowLeft();
	virtual bool engineSlowRight();
	virtual int getSetInterrupt();
	virtual int getInterrupt();
	virtual bool deactivateInterrupt(int port);
	virtual bool activateInterrupt(int port);
	virtual bool resetAllOutPut();
	virtual bool removeLight(Color col);
	virtual bool addLight(Color col);
	virtual bool shine(Color col);
	virtual bool removeLED(LEDS led);
	virtual bool addLED(LEDS led);
	virtual bool shineLED(LEDS led);
	virtual bool setValueOfPort(int port,int val);

private:

	/**
	 * Writes to the transfersystem.
	 * \param dir an integer representing the port address
	 * \param value an integer, the bits which should be written or deleted
	 * \param overwrite a bool that indicates if the given bits from value should be overwritten or not.
	 * \returns the new value from the port
	 */
	int write(int dir, int value, bool overwrite);

	/**
	 * Sets ports direction to the specified value.
	 * \param cb an integer, the new status for the ControlBit-Register
	 */
	void setPortsTo(int cb);
	/**
	 * Reset the all ports direction.
	 */
	void resetPortsDirection();
	/**
	 * Set the Ports to Output direction.
	 * \param bits an integer, whose bits will be set to Output direction.
	 * \return an integer
	 */
	int setPortToOutput(int bits);
	/**
	 *	Set the Ports to Input direction.
	 * \param bits an integer, whose bits will be set to Input direction.
	 * \return an integer, true.
	 */
	int setPortToInput(int bits);
	/**
	 * Retrieve the Value of the specified port.
	 * \param dir an integer, the ports Address.
	 * \return an integer, the Value of the port.
	 */
	int getValueFromAdress(int dir);
	/**
	 * Calculate the bit for the specified port.
	 * \param dir an integer, the ports Address.
	 * \return an integer, the bits to the address.
	 */
	int getBitsToAdress(int dir);
	/**
	 *	Checks the Value, which will be written, for problems with other bits.
	 * \param dir an integer, port which will be written to.
	 * \param value an integer, bits which will be changed.
	 * \param set a bool, overwrite or not.
	 * \return an integer, the bits which will need to change.
	 */
	int checkVal(int dir, int value, bool set);
	/**
	 *	Calculate the bit mask for the Color.
	 * \param col of enumtype Color, Color whose mask will be returned.
	 * \return an integer, the bit mask.
	 */
	int getColorCode(Color col);
	int getLEDCode(LEDS led);
	HAL();
	HAL(const HAL&);
	HAL& operator=(const HAL&);
	virtual ~HAL();
	/**
	 * the Singleton Instance of the HAL
	 */
	static HAL* instance;
	/**
	 * Mutex to ensure thread-safety of HAL creation.
	 */
	static Mutex mutEx;
};

#endif /* HAL_H_ */
