
#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

enum Com{
	INTERRUPTCONTROLLER, SENSOR, LIGHTS
};

/**
 * Communication
 *
 * SE2 (+ SY and PL) Project SoSe 2011
 *
 * Authors: Rico Flaegel,
 * 			Tell Mueller-Pettenpohl,
 * 			Torsten Krane,
 * 			Jan Quenzel
 *
 * Capsulates many functions for the direct
 * connection of components via Messages.
 *
 */
class Communication {
public:
	/**
	 * Get the ChannelID of the specified component.
	 * \param c the specified component.
	 * \return ChannelID
	 */
	int getComObject(Com c);
	Communication();
	virtual ~Communication();
};

#endif /* COMMUNICATION_H_ */
