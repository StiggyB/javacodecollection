
#ifndef IHAL_H_
#define IHAL_H_

/**
 * Enumeration for Colors
 */
enum Color {
	RED, GREEN, YELLOW, OFF
};
/**
 * Enumeration for LEDS
 */
enum LEDS{
	START_LED, RESET_LED, Q1_LED, Q2_LED, LEDS_OFF, LEDS_ON
};

/**
 * Interface for the Hardware Abstraction Layer.
 *
 * SE2 (+ SY and PL) Project SoSe 2011
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
 */
class IHAL {
public:
	/**
	 * Reads from a port.
	 * \param dir an integer, specifying the Port.
	 * \return an integer, the value read.
	 */
	virtual int read(int dir)=0;
	/**
	 * Checks if a port is set to Input.
	 * \param dir an integer, specifying the Port.
	 * \return true if port is set to Input.
	 */
	virtual bool isInput(int dir)=0;
	/**
	 * Checks if a port is set to Output.
	 * \param dir an integer, specifying the Port.
	 * \return true if port is set to Output.
	 */
	virtual bool isOutput(int dir)=0;

	/**
	 * Writing to a port.
	 * \param dir an integer, specifying the port.
	 * \param value an integer. The position, where the bits will be set to one.
	 * \return an integer, the actual value of the port.
	 */
	virtual int write(int dir, int value)=0;
	/**
	 * Reseting specified bit position on a port.
	 * \param dir an integer, specifying the port.
	 * \param value an integer. The position, where the bits will be reset to zero.
	 * \return an integer, the actual value of the port.
	 */
	virtual int reset(int dir, int value)=0;
	/**
	 * Starting the Engine into a given direction.
	 * \param direction an integer, specifying the direction (LEFT (BIT_ENGINE_LEFT),
	 *  RIGHT (BIT_ENGINE_RIGHT)).
	 * \return a bool, true if engine started.
	 */
	virtual bool engineStart(int direction)=0;
	/**
	 * Opens the Switch.
	 * \return a bool, true if switch is open.
	 */
	virtual bool openSwitch()=0;
	/**
	 * Closes the Switch.
	 * \return a bool, true if switch is closed.
	 */
	virtual bool closeSwitch()=0;
	/**
	 * Sets the Switch to open or closed.
	 * \param dir a bool,
	 * \return a bool, true action succeeded.
	 */
	virtual bool setSwitchDirection(bool dir)=0;
	/**
	 * Resets the engine. (Resetting port A Bit 0 to 3)
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineReset()=0;
	/**
	 * Stops the engine through setting the stopbit.
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineStop()=0;
	/**
	 * Continues the engine through resetting the stopbit.
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineContinue()=0;
	/**
	 * Sets the engine direction to the right, if not stopped.
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineRight()=0;
	/**
	 * Sets the engine direction to the left, if not stopped.
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineLeft()=0;
	/**
	 * Sets the engine to slow speed.
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineSlowSpeed()=0;
	/**
	 * Sets the engine to normal speed.
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineNormalSpeed()=0;
	/**
	 * Retrieves if the engine has stopped (stop bit set).
	 * \return a bool, true if stop bit set.
	 */
	virtual bool engineStopped()=0;
	/**
	 * Sets the engine to slow speed.
	 * \param dir an integer, BIT_ENGINE_LEFT, BIT_ENGINE_S_L, else it will be slowed.
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineSlowSpeed(int dir)=0;
	/**
	 * Sets the engine to slow speed.
	 * \param slow a bool. If true, the engine will be set to slow speed,
	 * false will continue.
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineSpeed(bool slow)=0;
	/**
	 * Sets the engine to slow speed and left direction.
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineSlowLeft()=0;
	/**
	 * Sets the engine to slow speed and right direction.
	 * \return a bool, true action succeeded.
	 */
	virtual bool engineSlowRight()=0;
	/**
	 * Retrieves the set interrupts.
	 * \return an integer, set interrupts
	 */
	virtual int getSetInterrupt()=0;
	/**
	 * Retrieves the triggered interrupts.
	 * \return an integer, triggered interrupts
	 */
	virtual int getInterrupt()=0;
	/**
	 * activates the Interrupt to a certain
	 * \param port an integer, specifying the Port.
	 * \return a bool, true if action was successful, false if not.
	 */
	virtual bool activateInterrupt(int port)=0;
	/**
	 * deactivates the Interrupt to a certain port
	 * \param port an integer, specifying the Port.
	 * \return a bool, true if action was successful, false if not.
	 */
	virtual bool deactivateInterrupt(int port)=0;
	/**
	 * Resets all bits from Port A.
	 * \return a bool, true action succeeded.
	 */
	virtual bool resetAllOutPut()=0;
	/**
	 * Removes a certain light.
	 * \param col specifies the color of the light.
	 */
	virtual bool removeLight(Color col)=0;
	/**
	 * Adds a certain light.
	 * \param col specifies the color of the light.
	 * \return a bool, true action succeeded.
	 */
	virtual bool addLight(Color col)=0;
	/**
	 * Adds a certain light.
	 * Equals void addLight(Color col);
	 * \param col specifies the color of the light.
	 * \return a bool, true action succeeded.
	 */
	virtual bool shine(Color col)=0;
	/**
	 * Removes a certain light.
	 * \param col specifies the color of the light.
	 */
	virtual bool removeLED(LEDS led)=0;
	/**
	 * Adds a certain light.
	 * \param col specifies the color of the light.
	 * \return a bool, true action succeeded.
	 */
	virtual bool addLED(LEDS led)=0;
	/**
	 * Adds a certain light.
	 * Equals void addLight(Color col);
	 * \param col specifies the color of the light.
	 * \return a bool, true action succeeded.
	 */
	virtual bool shineLED(LEDS led)=0;
	virtual bool setValueOfPort(int port,int val)=0;

	virtual int identifyHeight()=0;
	virtual bool isMetal()=0;
	IHAL();
	virtual ~IHAL();
};

#endif /* IHAL_H_ */
