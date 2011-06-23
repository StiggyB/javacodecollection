#ifndef HALCore_H_
#define HALCore_H_

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include "HWaccess.h"
#include "../Thread/Mutex.h"
#include "../Thread/HAWThread.h"
#include "../Thread/Semaphor.h"
#include "../Thread/Condition.h"
#include "../Thread/Singleton_T.h"
#include "../Timer/Timer.h"
#include "../Functor/CallBackThrower.h"

#define CONDOR
//#define SEMAP

/**
 * Delete a bit
 */
#define BIT_DELETE (false)
/**
 * Set a bit
 */
#define BIT_SET (true)
/**
 * BASE ADDRESS for Digital IO
 */
#define D_IOBASE 0x300 	// start address Ports
/**
 * BASE ADDRESS for Analog IO
 */
#define A_IOBASE 0x320
/**
 * tolerance range plane and normal work piece
 */
#define TOLERANCE_NORMAL 75
/**
 * tolerance range work piece with a pocket
 */
#define TOLERANCE_POCKET 100
/**
 * 12Bit-Mask for the height measure
 */
#define HEIGHT_MASK 0xFFF

/**
 * PORT A:
 */
enum PortA {
	BIT_ENGINE_RIGHT = (1 << 0),
	BIT_ENGINE_LEFT = (1 << 1),
	BIT_ENGINE_SLOW = (1 << 2),
	BIT_ENGINE_STOP = (1 << 3),
	BIT_SWITCH = (1 << 4),
	BIT_LIGHT_GREEN = (1 << 5),
	BIT_LIGHT_YELLOW = (1 << 6),
	BIT_LIGHT_RED = (1 << 7),
	BIT_ENGINE_S_L = (0x06),
	BIT_ENGINE_S_R = (0x05),
	BIT_LIGHT_OFF = (0x00),
	BIT_LIGHTS_ON = (0xE0)
};

/**
 * PORT B:
 */
enum PortB {
	BIT_WP_OUT = 0,
	BIT_WP_RUN_IN = (1 << 0),
	BIT_WP_IN_HEIGHT = (1 << 1),
	BIT_HEIGHT_1 = (1 << 2),
	BIT_WP_IN_SWITCH = (1 << 3),
	BIT_WP_METAL = (1 << 4),
	BIT_SWITCH_STATUS = (1 << 5),
	BIT_WP_IN_SLIDE = (1 << 6),
	BIT_WP_OUTLET = (1 << 7)
};

/**
 * PORT B Bits:
 */
enum PortB_Bit{
	WP_RUN_IN = 0,WP_IN_HEIGHT = 1,WP_HEIGHT_STATUS = 2,WP_IN_SWITCH = 3,
	WP_METAL = 4,WP_WITCH_STATUS = 5, WP_IN_SLIDE = 6, WP_OUTLET = 7
};

/**
 * PORT C:
 */
enum PortC {
	BIT_LED_START = (1 << 0),
	BIT_LED_RESET = (1 << 1),
	BIT_LED_Q1 = (1 << 2),
	BIT_LED_Q2 = (1 << 3),
	BIT_START = (1 << 4),
	BIT_STOP = (1 << 5),
	BIT_RESET = (1 << 6),
	BIT_E_STOP = (1 << 7),
	BIT_LEDS_ON = (0x0F)
};

/**
 * Bits for PORT C
 */
enum PortC_Bit{
	WP_LED_START=0, WP_LED_RESET=1, WP_LED_Q1=2, WP_LED_Q2=3,
	WP_START=4, WP_STOP=5, WP_RESET=6, WP_E_STOP=7
};

/**
 * PORT ADDRESS:
 */
enum PortAdress {
	PORT_A = (D_IOBASE + 0x00), PORT_B = (D_IOBASE + 0x01), PORT_C = (D_IOBASE
			+ 0x02), PORT_CNTRL = (D_IOBASE + 0x03)
};

/**
 * CONTROLBITS:
 */
enum ControlBits {
	BIT_PORT_A = (1 << 4),
	BIT_PORT_B = (1 << 1),
	BIT_PORT_C = ((1 << 0) + (1 << 3)),
	BIT_PORT_C_LOW = (1 << 0),
	BIT_PORT_C_HIGH = (1 << 3),
	BIT_CNTRLS = (0x8A)
};

/**
 * Height Measures
 */
enum Height {
	HEIGHT_MEASURE_STATUS = (A_IOBASE + 0x00),
	HEIGHT_REGISTER_PART1 = (A_IOBASE + 0x02),
	HEIGHT_REGISTER_PART2 = (A_IOBASE + 0x03),
	HEIGHT_START_CODE = (0x10)
};

/**
 *
 */
enum WPHeight{
	PLANE_WP = 0xa9b , NORMAL_WP = 0x9a8, POCKET_WP = 0xdba
};

/**
 * Enumeration for Colors
 */
enum Color {
	RED, GREEN, YELLOW, OFF
};
/**
 * Enumeration for LEDS
 */
enum LEDS {
	START_LED, RESET_LED, Q1_LED, Q2_LED, LEDS_OFF, LEDS_ON
};

/**
 *  interrupts
 */
enum Interrupts_D {
	INTERRUPT_D_PORT_A = (1 << 0),
	INTERRUPT_D_PORT_B = (1 << 1),
	INTERRUPT_D_PORT_C = (1 << 2),
	INTERRUPT_D_PORT_C_HIGH = (1 << 3),
	INTERRUPT_D_SERIAL = (1 << 4),
	INTERRUPT_VECTOR_NUMMER_A = 14,
	INTERRUPT_VECTOR_NUMMER_D = 11,
	INTERRUPT_SET_ADRESS_D = (D_IOBASE + 0xB),
	INTERRUPT_RESET_ADRESS_D = (D_IOBASE + 0xF),
	PORT_IRE = (D_IOBASE + 0xB),
	PORT_IRQ = (D_IOBASE + 0xF),
	PORT_IRQ_AND_RESET = (D_IOBASE + 0x18),
	IIR_MASK_D = 0xF
};

/**
 * Index to pointer to functions WRITE and RESET
 */
enum Function{
	WRITE=0,RESET=1
};

/**
 * PULS Codes
 */
enum PULSE_CODE {
	LICHTSCHRANKE, HEIGHT
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
 * Emergency Stop pushed!
 */
extern volatile bool emstopped;

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
class HALCore: public thread::HAWThread, public CallBackThrower, public Singleton_T<HALCore>{
	friend class Singleton_T<HALCore>;
public:
	/**
	 * Retrieve the running status of the engine.
	 * \returns an bool, true if engine is running.
	 */
	bool isEngineRunning();
	/**
	 * Reads from a port.
	 * \param dir an integer, specifying the Port.
	 * \return an integer, the value read.
	 */
	int read(int dir);
	/**
	 * Checks if a port is set to Input.
	 * \param dir an integer, specifying the Port.
	 * \return true if port is set to Input.
	 */
	bool isInput(int dir);
	/**
	 * Checks if a port is set to Output.
	 * \param dir an integer, specifying the Port.
	 * \return true if port is set to Output.
	 */
	bool isOutput(int dir);
	/**
	 * Writing to a port.
	 * \param dir an integer, specifying the port.
	 * \param value an integer. The position, where the bits will be set to one.
	 * \return an integer, the actual value of the port.
	 */
	void write(int dir, int value);
	void write(void *ptr);
	/**
	 * Reseting specified bit position on a port.
	 * \param dir an integer, specifying the port.
	 * \param value an integer. The position, where the bits will be reset to zero.
	 * \return an integer, the actual value of the port.
	 */
	void reset(int dir, int value);
	void reset(void *ptr);
	/**
	 * Starting the Engine into a given direction.
	 * \param direction an integer, specifying the direction (LEFT (BIT_ENGINE_LEFT),
	 *  RIGHT (BIT_ENGINE_RIGHT)).
	 * \return a bool, true if engine started.
	 */
	void engineStart(int direction);
	/**
	 * Opens the Switch.
	 * \return a bool, true if switch is open.
	 */
	void openSwitch();
	/**
	 * Closes the Switch.
	 * \return a bool, true if switch is closed.
	 */
	void closeSwitch();
	/**
	 * Sets the Switch to open or closed.
	 * \param dir a bool,
	 * \return a bool, true action succeeded.
	 */
	void setSwitchDirection(bool dir);
	/**
	 * Resets the engine. (Resetting port A Bit 0 to 3)
	 * \return a bool, true action succeeded.
	 */
	void engineReset();
	/**
	 * Stops the engine through setting the stopbit.
	 * \return a bool, true action succeeded.
	 */
	void engineStop();
	/**
	 * Continues the engine through resetting the stopbit.
	 * \return a bool, true action succeeded.
	 */
	void engineContinue();
	/**
	 * Sets the engine direction to the right, if not stopped.
	 * \return a bool, true action succeeded.
	 */
	void engineRight();
	/**
	 * Sets the engine direction to the left, if not stopped.
	 * \return a bool, true action succeeded.
	 */
	void engineLeft();
	/**
	 * Sets the engine to slow speed.
	 * \return a bool, true action succeeded.
	 */
	void engineSlowSpeed();
	/**
	 * Sets the engine to slow speed.
	 * \param dir an integer, BIT_ENGINE_LEFT, BIT_ENGINE_S_L, else it will be slowed.
	 * \return a bool, true action succeeded.
	 */
	void engineSlowSpeed(int dir);/**
	 * Sets the engine to normal speed.
	 * \return a bool, true action succeeded.
	 */
	void engineNormalSpeed();
	/**
	 * Retrieves if the engine has stopped (stop bit set).
	 * \return a bool, true if stop bit set.
	 */
	bool engineStopped();
	/**
	 * Sets the engine to slow speed.
	 * \param slow a bool. If true, the engine will be set to slow speed,
	 * false will continue.
	 * \return a bool, true action succeeded.
	 */
	void engineSpeed(bool slow);
	/**
	 * Sets the engine to slow speed and left direction.
	 * \return a bool, true action succeeded.
	 */
	void engineSlowLeft();
	/**
	 * Sets the engine to slow speed and right direction.
	 * \return a bool, true action succeeded.
	 */
	void engineSlowRight();
	/**
	 * Retrieves the set interrupts.
	 * \return an integer, set interrupts
	 */
	int getSetInterrupt();
	/**
	 * Retrieves the triggered interrupts.
	 * \return an integer, triggered interrupts
	 */
	int getInterrupt();
	/**
	 * activates the Interrupt to a certain
	 * \param port an integer, specifying the Port.
	 * \return a bool, true if action was successful, false if not.
	 */
	void activateInterrupt(int port);
	/**
	 * deactivates the Interrupt to a certain port
	 * \param port an integer, specifying the Port.
	 * \return a bool, true if action was successful, false if not.
	 */
	void deactivateInterrupt(int port);
	/**
	 * Resets all bits from Port A.
	 * \return a bool, true action succeeded.
	 */
	void resetAllOutPut();
	/**
	 * Removes a certain light.
	 * \param col specifies the color of the light.
	 */
	void removeLight(Color col);
	/**
	 * Adds a certain light.
	 * \param col specifies the color of the light.
	 * \return a bool, true action succeeded.
	 */
	void addLight(Color col);
	/**
	 * Adds a certain light.
	 * Equals void addLight(Color col);
	 * \param col specifies the color of the light.
	 * \return a bool, true action succeeded.
	 */
	void shine(Color col);
	/**
	 * Removes a certain light.
	 * \param led specifies the color of the light.
	 */
	void removeLED(LEDS led);
	/**
	 * Adds a certain LED.
	 * \param led specifies the color of the light.
	 * \return a bool, true action succeeded.
	 */
	void addLED(LEDS led);
	/**
	 * Adds a certain light.
	 * Equals void addLED(LEDS led);
	 * \param led specifies the color of the light.
	 * \return a bool, true action succeeded.
	 */
	void shineLED(LEDS led);
	/*!
	 * returns a Pointer to the threadsafe Singleton Instance of the Hardware Abstraction Layer (HAL)
	 * \return a Pointer to HAL.
	 */
	//static HALCore* getInstance();
	/**
	 * deletes the Instance
	 */
	//static void deleteInstance();
	/**
	 * activates the light specified by color
	 * \param color an integer, specifying the color.
	 * \return a bool, true if action was successful, false if not.
	 */
	void shine(int color);
	/**
	 * activates the LED specified by led
	 * \param led an integer, specifying the Led which should be activated.
	 * \return a bool, true if action was successful, false if not.
	 */
	void shineLED(int led);
	/**
	 * Stops all processes
	 * *reserved for future*
	 * do not use!
	 */
	void stopProcess();
	/**
	 * Performes an emergency stop.
	 */
	void emergencyStop();
	/**
	 * Stops the machine.
	 */
	void stopMachine();
	/**
	 * Restarts the machine.
	 */
	void restart();
	/**
	 * Resets all hardware and software.
	 */
	void resetAll();
	/**
	 *	Identifies the height of a work piece and
	 *	categorize in defined enum types.
	 *	\return a integer, the height of the work piece.
	 */
	int identifyHeight();
	/**
	 * Callback function for identifyHeight
	 * which interrupts the DAC busy waiting.
	 */
	void checkTimeIdentifyHeight();
	/**
	 * Checks the sensor b(6) on the slide.
	 * \return a bool, true if there is a work piece.
	 */
	bool checkSlide();
	/**
	 * Returns if there is metal under the metal detector.
	 * \return a bool, true if there is metal.
	 */
	bool isMetal();
protected:
	void execute(void*);
	void shutdown();

	/**
	 * functionpointer on HALCore functions
	 */
	typedef void (HALCore::*FP)(void*);

	typedef struct val {
		int value1;
		int value2;
		bool value3;
	} __attribute__((__packed__)) VAL;

	typedef struct f {
		FP func;
		VAL* v;
	} __attribute__((__packed__)) Functions;
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
	/**
	 * Calculate the bit mask for LED.
	 * \param led of enumtype LED, LED whose mask will be returned.
	 * \return an integer, the bit mask.
	 */
	int getLEDCode(LEDS led);

	HALCore();
	~HALCore();
	/**
	 * for Singleton
	 */
	HALCore(const HALCore&);
	HALCore& operator=(const HALCore&);

	/**
	 * Pointer for singleton HALCore
	 */
	//static HALCore* pInstance;
	/**
	 * Pointer for Mutex to keep singleton threadsafe
	 */
	//static Mutex singleton;
	/**
	 * Mutex to ensure threadsafety
	 */
	//static Mutex mutEx;
	/**
	 * Stop pushed!
	 */
	bool stopped;
	/**
	 * Timeout flag for identifyHeight loop.
	 */
	bool timeout;
	/**
	 * Wakeup the thread
	 */
	void wakeup();
	/**
	 * function pointer array
	 */
	FP funcArray[2];
	/**
	 * sets the function pointer array
	 */
	void setFPArray();
	/**
	 * List of function pointers which should worked up
	 */
	vector<Functions *> lst;
	/**
	 * Pointer to Timer.
	 */
	Timer *timer;
#ifdef CONDOR

	Condition condvar;
	Mutex mut;
	Mutex changedMutex;
	bool requested;

#endif
#ifdef SEMAP
	/**
	 * Semaphore to wakeup the thread
	 */
	Semaphor sem;
#endif
	Functions * buildFunctions(FP f, int val1, int val2);
	Functions * buildFunctions(FP f, bool val3);
	Functions * buildFunctions(FP f, int val1);
	Functions * buildFunctions(FP f, int val1, int val2, bool val3);
};

#endif /* HALCore_H_ */
