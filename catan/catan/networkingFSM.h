#pragma once

#include "genericFSM.h"
#include "networkingEvents.h"

enum netwStates : stateTypes { IDLE, ROBBER, WAIT_MOVE, WAIT_PLAYER };

enum netwFSMEvTypes : eventTypes {OK, DICES7, STAY, UNEXPECTED_EVENT};

class netwFSMEvs : public genericEvent
{
public:
	netwFSMEvs() : error(false) {}
	netwFSMEvs(netwFSMEvTypes type_) { }//if(valid)type = type_; }
	virtual eventTypes getType() { return type; }
	bool getError() { return false; }
private:
	netwFSMEvTypes type;
	bool error;
};

class networkingFSMopponentsTurn : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[4][4] = {
	//			OK							DICES7					STAY 				UNEXPECTED_EVENT					
	{ { WAIT_MOVE,TX(sendDices) },{ ROBBER,TX(prepareRobber) },{ IDLE,TX(error) },{ IDLE,TX(doNothing) } },			//IDLE
	{ { WAIT_MOVE,TX(moveRobber) },{ ROBBER ,TX(error) },{ ROBBER,TX(sendToRobberFSM) },{ ROBBER,TX(error) } },		//ROBBER
	{ { WAIT_PLAYER,TX(sendTradeOffer) },{ WAIT_MOVE,TX(error) },{ WAIT_MOVE,TX(validate) },{ WAIT_PLAYER,TX(error) } },//WAIT_MOVE
	{ { WAIT_MOVE,TX(sendAnswer) },{ WAIT_PLAYER,TX(error) },{ WAIT_PLAYER,TX(error) },{ WAIT_PLAYER,TX(error) } } //WAIT_PLAYER
	};

	//The action routines for the FSM
	void sendDices(genericEvent * ev);
	void prepareRobber(genericEvent * ev);
	void error(genericEvent * ev);
	void sendToRobberFSM(genericEvent * ev);
	void sendTradeOffer(genericEvent * ev);
	void sendAnswer(genericEvent * ev);
	void validate(genericEvent * ev);
	void doNothing(genericEvent * ev) {}
	list<networkingEv> expectedEvents;
	robberFSM * robberfsm;
public:
	networkingFSMopponentsTurn();
	list<networkingEv> getExpectedEvents();
};

enum robberStates : stateTypes { WAIT_USER, WAIT_ROBBCARDS, WAIT_ROBBMOVE };

enum robberFSMEvTypes : eventTypes { ROBBER_CARDS, ROBBER_MOVE, MY_CARDS, MY_CARDS_AND_WAIT };

class robberFSMEvs : public genericEvent
{
public:
	robberFSMEvs();
	robberFSMEvs(robberFSMEvTypes type_); //if(valid) type(type_) {}
	robberFSMMEvTypes getType() { return type; }
	bool getError();
private:
	robberFSMEvTypes type;
	bool error = false;
};

class robberFSM : public genericFSM
{
private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[3][2] = {
	//	   ROBBER_CARDS					ROBBER_MOVE						MY_CARDS						MY_CARDS_AND_WAIT									
	{ { WAIT_USER,TX(error) },		{ WAIT_USER,TX(error) },		{ WAIT_ROBBMOVE,TX(mandar) },	{ WAIT_ROBBCARDS,TX(mandar) } }, //WAIT_USER
	{ { WAIT_ROBBMOVE,TX(send) },	{ WAIT_ROBBCARDS,TX(error) },	{ WAIT_ROBBCARDS,TX(error) },	{ WAIT_ROBBCARDS,TX(error) } },	 //WAIT_ROBBCARDS
	{ { WAIT_ROBBMOVE,TX(error) },	{ WAIT_ROBBMOVE,TX(moveryok) },	{ WAIT_ROBBMOVE,TX(error) },	{ WAIT_ROBBMOVE,TX(error) } }    //WAIT_ROBBMOVE
	};

	//The action routines for the FSM

	void prueba1(genericEvent * ev)
	{

	}
public:
	robberFSM(stateTypes initState) : genericFSM(&fsmTable[0][0], 3, 2, initState) {}	//crear fsm chica, display (en fsm chica), atachear fsm chica como fuente de eventos
};
