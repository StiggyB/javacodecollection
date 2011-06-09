
#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <list>
#include <iostream>
#include <stdlib.h>
#include "../Thread/HAWThread.h"

#define PULSE_MIN_PRIO 1
/**
 * All types of Communicators
 */
enum CommunicatorType {
	INTERRUPTCONTROLLER = (1),
	SENSOR = (2),
	LIGHTS = (3),
	ANLAGENSTEUERUNG = (4),
	COMMUNICATIONCONTROLLER = (5),
	SERIAL = (6),
	TIMER = (7),
	NONE = (0),
	TESTER = (99)
};

/**
 * All Types of Messages
 */
enum MsgType {
	addToServer = (4),
	removeFromServer = (5),
	closeConnection = (6),
	startConnection = (7),
	getIDforCom = (8),
	react = (9),
	reactC = (0xa),
	reactSerial = (0xc),
	information = (0xb),
	OK = (1),
	notAvailable = (-2),
	sendID = (3),
	error = (-1)
};

/**
 * Message structure containing information about the Sender and what he wants from the Receiver
 */
typedef struct msg{
	int chid;
	int coid;
	int wert;
	MsgType ca;
	CommunicatorType comtype;
} Msg;

/**
 * union for possible messages. It could be a sigevent, a pulse or a msg.
 */
typedef union message{
	struct sigevent event;
	struct _pulse pulse;
	/**
	 * the message which should be transmitted itself, like event for InterruptPulses
	 */
	Msg m;
} Message;

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
protected:
	/**
	 * Get the ChannelID of the specified Communicator from the local list.
	 * \param c the specified Communicator.
	 * \return ChannelID
	 */
	int getChannelIdForObject(CommunicatorType c);
	/**
	 * Get the ChannelID of the specified Communicator from the local list.
	 * \param c the specified Communicator.
	 * \param number the number of entries which should be ignored
	 * \return ChannelID
	 */
	int getChannelIdForObject(CommunicatorType c, int number);
	/**
	 * Get the ConnectID of the specified Communicator from the local list.
	 * \param c the specified Communicator.
	 * \return ConnectID
	 */
	int getConnectIdForObject(CommunicatorType c);
	/**
	 * Get the ConnectID of the specified Communicator from the local list.
	 * \param c the specified Communicator.
	 * \param number the number of entries which should be ignored
	 * \return ConnectID
	 */
	int getConnectIdForObject(CommunicatorType c, int number);
	/**
	 * Get the UniqueID of the specified Communicator from the local list.
	 * \param c the specified Communicator.
	 * \return UniqueID
	 */
	int getUniqueIdForObject(CommunicatorType c);
	/**
	 * Get the UniqueID of the specified Communicator from the local list.
	 * \param c the specified Communicator.
	 * \param number the number of entries which should be ignored
	 * \return UniqueID
	 */
	int getUniqueIdForObject(CommunicatorType c, int number);
	/**
	 * Get the specified ID of the specified Communicator from the local list.
	 * \param c the specified Communicator.
	 * \param number the number of entries which should be ignored
	 * \param mode the number specifying the ID type -> Connect, Unique or Channel
	 * \return specified ID
	 */
	int getIdForObject(CommunicatorType c, int number,int mode);

	/**
	 * Gets the ChannelID of the specified Communicator from the CommunicatorServer
	 * over a separate connection to the CommunicatorServer and adds it to the local list.
	 * \param c the specified Communicator.
	 * \return true if request was successful, else it will be false
	 */
	bool requestChannelIDForObject(CommunicatorType c);
	/**
	 * Gets the ChannelID of the specified Communicator from the CommunicatorServer
	 * over a separate connection to the CommunicatorServer and adds it to the local list.
	 * \param c the specified Communicator.
	 * \param number the number of entries which should be ignored
	 * \return a bool, true if request was successful, else it will be false
	 */
	bool requestChannelIDForObject(CommunicatorType c, int number);

	/**
	 * Adds a Communicator to the local list.
	 * \param ch an integer, specifying the ChannelID.
	 * \param cod an integer, specifying the ConnectID.
	 * \param uni an integer, specifying the unique ID of the Communicator.
	 * \param ct the type of the Communicator.
	 * \return bool, true if successful
	 */
	bool addCommunicator(int ch, int cod, int uni, CommunicatorType ct);

	/**
	 * Removes a Communicator from the local list.
	 * \param uni an integer, specifying the unique ID of the Communicator.
	 * \return bool, true if successful
	 */
	bool removeCommunicator(int uni);
	/**
	 * Creates a Channel for Message Passing
	 * \return bool, true if successful
	 */
	bool setUpChannel();
	/**
	 * Registers a Channel at the Communicator Server for Message Passing
	 * so it will be available for other parts
	 * \param c the Communicator which wants to be registered
	 * \param unique the UniqueID of the Communicator
	 * \return bool, true if successful
	 */
	bool registerChannel(CommunicatorType c, int unique);
	/**
	 * Destroys a Channel for Message Passing
	 * \param id and integer specifying the Channel which should be destroyed.
	 * \return bool, true if successful
	 */
	bool destroyChannel(int id);
	/**
	 * Unregisters a Channel and removes it from the Communicators Server list
	 * \param c the Communicator which wants to be unregistered
	 * \return bool, true if successful
	 */
	bool unregisterChannel(CommunicatorType c, int unique);
	/**
	 * Attaches a connection to a Channel and informs the Target-Communicator.
	 * \param id an integer specifying the ChannelID
	 * \param c the Communicator which wants to be attached
	 * \return bool, true if successful
	 */
	bool attachConnection(int id, CommunicatorType c);
	/**
	 * Detaches a connection to a Channel and informs the Target-Communicator.
	 * \param coid an integer specifying the ConnectID
	 * \param c the Communicator which wants to be detached
	 * \return bool, true if successful
	 */
	bool detachConnection(int coid, CommunicatorType c,int unique);
	/**
	 * Builds a Message.
	 * \param s an pointer to the Message, which should be build
	 * \param chid an integer specifying the ChannelID of the sender
	 * \param coid an integer specifying the ConnectID of the sender
	 * \param activity is the message type, which tells us what should happen
	 * \param c the Communicator which sends the message
	 * \return bool, true if successful
	 */
	void buildMessage(void *s, int chid, int coid, MsgType activity,CommunicatorType c);
	/**
	 * Builds a Message.
	 * \param s an pointer to the Message, which should be build
	 * \param chid an integer specifying the ChannelID of the sender
	 * \param coid an integer specifying the ConnectID of the sender
	 * \param activity is the message type, which tells us what should happen
	 * \param c the Communicator which sends the message
	 * \param val an integer representing the value of the register
	 * \return bool, true if successful
	 */
	void buildMessage(void *s, int chid, int coid, MsgType activity,CommunicatorType c,int val);
	/**
	 * Prints the local list of Communicators
	 */
	void printList();
	/**
	 * Detaches connection and frees memory
	 * \param coid an integer, the connectionId which should be cleared
	 * \return bool, true if successful
	 */
	bool cleanUp(int coid);
	/**
	 * Detaches connection and frees memory
	 * \param coid an integer, the connectionId which should be cleared
	 * \param m pointer of type Message, this memory will be freed
	 * \param r pointer of type Message, this memory will be freed
	 * \return bool, true if successful
	 */
	bool cleanUp(int coid, Message *m, Message *r);
	/**
	 * allocates Space for the Messages
	 * \return bool, true if successful
	 */
	bool allocMessages();
	/**
	 * allocates Space for the Messages
	 * \return bool, true if successful
	 */
	bool allocMessages(void ** msg, void ** rmsg);
	/**
	 * Equivalent to setupChannel () and registerChannel()
	 * \param c the Communicator which wants to be registered
	 * \return bool, true if successful
	 */
	bool prepareCommunication(CommunicatorType c);
	/**
	 * Equivalent to attachConnection () and sending startConnection()
	 * \param c the Communicator which you want to attach communication with
	 * \param my the CommunicatorType of your own
	 * \return bool, true if successful
	 */
	bool connectWithCommunicator(CommunicatorType c, CommunicatorType my);
	/**
	 * Equivalent to attachConnection () and sending startConnection()
	 * \param c the Communicator which you want to attach communication with
	 * \param my the CommunicatorType of your own
	 * \param number the number of entries which should be ignored
	 * \return bool, true if successful
	 */
	bool connectWithCommunicator(CommunicatorType c, int number, CommunicatorType my);
	/**
	 * Sends an Puls Message to the specified target with given code and value.
	 * The Target's ChannelID etc. must be known!
	 * \param target whom should get the Pulse
	 * \param code which should be delivered
	 * \param value which should be delivered
	 * \return bool, true if successful
	 */
	bool sendPulses(CommunicatorType target, int code, int value);
	/**
	 * Sends an Puls Message to the specified target with given code and value.
	 * The Target's ChannelID etc. must be known!
	 * \param target whom should get the Pulse
	 * \param number the number of entries which should be ignored
	 * \param code which should be delivered
	 * \param value which should be delivered
	 * \return bool, true if successful
	 */
	bool sendPulses(CommunicatorType target, int number, int code, int value);
	/**
	 * Sends a Message.
	 * \param msg Message which should be send.
	 * \param rec Message where the answer should be received.
	 * \returns bool, true if send successful
	 */
	bool sendMessage(Message *msg, Message * rec);
	/**
	 * Sends a Message with the in Message * m specified content and receives an answer.
	 * \returns bool, true if send successful
	 */
	bool sendMessage();
	/**
	 * Sets up a communicator device (allocate memory, register and acquire a needed communication path);
	 * \return bool, true if successful
	 */
	bool settingUpCommunicatorDevice(CommunicatorType target);
	/**
	 * cleans up the Communication
	 */
	void cleanCommunication();
	/**
	 * ends the Communication and cleans up.
	 */
	void endCommunication();
	/**
	 * retrieve the code from a Pulse Message
	 * \param ptr a pointer to a Message containing a pulse.
	 * \return the code of the Pulse Message
	 */
	int getCodeFromPulse(Message *ptr);
	/**
	 * retrieve the code from the receive Pulse Message
	 * \return the code of the receive Pulse Message
	 */
	int getCodeFromReceivePulse();
	/**
	 * retrieve the value from a Pulse Message
	 * \param ptr a pointer to a Message containing a pulse.
	 * \return the value of the Pulse Message
	 */
	int getValueFromPulse(Message *ptr);
	/**
	 * retrieve the value from the receive Pulse Message
	 * \return the value of the receive Pulse Message
	 */
	int getValueFromReceivePulse();
	Communication();
	virtual ~Communication();
private:
	/**
	 * Communicator (private class)
	 *
	 * SE2 (+ SY and PL) Project SoSe 2011
	 *
	 * Authors: Rico Flaegel,
	 * 			Tell Mueller-Pettenpohl,
	 * 			Torsten Krane,
	 * 			Jan Quenzel
	 *
	 * Capsules information about the Communicator which uses Message Passing
	 *
	 */
	class Communicator {
	public:
		/**
		 * Constructor with information about ChannelID, ConnectionID and Communicator Type
		 * \param id an integer, specifying the ChannelID
		 * \param cod an integer, specifying the ConnectionID
		 * \param uni an integer, specifying the UniqueID
		 * \param c type of the Communicator
		 */
		Communicator(int id, int cod, int uni, CommunicatorType c) {
			chid = id;
			coid = cod;
			cm = c;
			uniqueID = uni;
		}
		~Communicator() {
		}
		/**
		 * Get the CommunicatorType of the Communicator.
		 * \return type of the Communicator
		 */
		CommunicatorType getCom() {
			return cm;
		}
		/**
		 * Get the ChannelID of the Communicator.
		 * \return an integer, the ChannelID
		 */
		int getChannelID() {
			return chid;
		}
		/**
		 * Get the ConnectionID of the Communicator.
		 * \return an integer, the ConnectionID
		 */
		int getConnectID() {
			return coid;
		}
		/**
		 * Sets the ConnectionID of the Communicator.
		 * \param co an integer, the new Connection ID
		 */
		bool setConnectID(int co) {
			coid = co;
			return true;
		}
		/**
		 * Get the UniqueID of the Communicator.
		 * \return an integer, the UniqueID
		 */
		int getUniqueID() {
			return uniqueID;
		}
		/**
		 * Get the UniqueID of the Communicator.
		 * \return an integer, the UniqueID
		 */
		void setUniqueID(int uni) {
			uniqueID = uni;
		}
	private:
		/**
		 * ChannelID of this Communicator
		 */
		int chid;
		/**
		 * ConnectionID of this Communicator
		 */
		int coid;
		/**
		 * type of this Communicator
		 */
		CommunicatorType cm;
		/**
		 * unique identification number
		 */
		int uniqueID;
	};
	/**
	 * Different types of IDs
	 */
	enum GET_MODES {
		CHANNEL = 1, CONNECT = 2, UNIQUE = 3
	};
	/**
	 * unique identification number
	 */
	static int uniqueIDCounter;
	/**
	 * unique identification number
	 */
	int uniqueID;
	/**
	 * List of all connected Communicators
	 */
	std::list<Communicator> lst;
protected:
	/**
	 * own CommunicatorType
	 */
	CommunicatorType mine;
	/**
	 * ChannelID and ConnectionID of this Communicator
	 */
	int chid, coid, rcvid;
	/**
	 * Message which can be send
	 */
	Message * m;
	/**
	 * Message where messages will be received
	 */
	Message * r_msg;
	/**
	 * handles all Messages received
	 * if Pulse -> handlePulsMessage will be called
	 * if Normal -> handleNormalMessage will be called
	 */
	void handleMessage();
	/**
	 * handles all PulsMessages received
	 */
	virtual void handlePulsMessage()=0;
	/**
	 * handles all NormalMessages received
	 */
	virtual void handleNormalMessage()=0;
	/**
	 * handles add and close connection commands
	 * \returns a boolean true, if did something.
	 */
	bool handleConnectionMessage();
	/**
	 * attaches received connection and does the necessary reply, adds the received communicator to local list
	 */
	void getConnectionAttached();
	/**
	 * Registers a Channel at the Communicator Server for Message Passing
	 * so it will be available for other parts
	 * \param c the Communicator which you want to attach communication with
	 * \param unique the UniqueID specifying the
	 * \param m the type of message which should be send
	 * \return bool, true if successful
	 */
	bool regEditChannel(CommunicatorType c, int unique, MsgType m);
	/**
	 * Just for internal use and for the communication between 2 CommunicatorDevices.
	 * Allocates space for the Messages, builds them and sends the Message. Detaches the Connection afterwards.
	 * \param ptrM pointer to the address of the Message
	 * \param ptrR pointer to the address of the Message
	 * \param c the Communicator which you want to send a message
	 * \param coid the ConnectionID which will be used for the message
	 * \param chid the ChannelID which will be used for the message
	 * \param unique the UniqueID specifying the
	 * \param m the type of message which should be send
	 */
	bool doInternalExchange(Message ** ptrM,Message ** ptrR,CommunicatorType c, int coid, int chid, int unique, MsgType m);
public:
	/**
	 * CommunicationServer ChannelID
	 */
	static volatile int serverChannelId;
	/**
	 * Retrieves the Communicator with the given ChannelID and ConnectionID.
	 * \param ci ChannelID of the searched Communicator
	 * \param co ConnectionID of the searched Communicator
	 * \return iterator representing a pointer to a Communicator object or NULL
	 */
	std::list<Communicator>::iterator getCommunicatorForObject(int ci, int co);
	/**
	 * Retrieves the Communicator with the given UniqueID.
	 * \param uni UniqueID of the searched Communicator
	 * \return iterator representing a pointer to a Communicator object or NULL
	 */
	std::list<Communicator>::iterator getCommunicatorForObject(int uni);
};

#endif /* COMMUNICATION_H_ */
