#pragma once

#include "genericFSM.h"
#include "networkingEvents.h"

enum netwStates : stateTypes { IDLE, ROBBER, WAIT_MOVE, WAIT_PLAYER };

enum netwFSMEvTypes : eventTypes {OK, DICES7, STAY, UNEXPECTED_EVENT};

class netwFSMEv : public genericEvent
{
public:
	netwFSMEv() : error(false) {}
	netwFSMEv(netwFSMEvTypes type_) { }//if(valid)type = type_; }
	virtual eventTypes getType() { return type; }
	bool getError() { return false; }
private:
	netwFSMEvTypes type;
	bool error;
};

class unexpectedNetwEvent : public netwFSMEv
{
public:
	unexpectedNetwEvent(string detail_ = "") : netwFSMEv(UNEXPECTED_EVENT) { detail = detail_; }
	string getDetail() { return detail; }

private:
	string detail;
};

class networkingFSMopponentsTurn : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[4][4] = {
	//			OK							CHANGE					STAY 				UNEXPECTED_EVENT					
	{ { WAIT_MOVE,TX(sendDices) },	{ ROBBER,TX(prepareRobber) },{ IDLE,TX(error) },{ IDLE,TX(doNothing) } },				//IDLE
	{ { WAIT_MOVE,TX(moveRobber) },	{ ROBBER ,TX(error) },{ ROBBER,TX(sendToRobberFSM) },{ ROBBER,TX(error) } },			//ROBBER
	{ { IDLE,TX(changeTurn) },		{ WAIT_PLAYER,TX(sendTradeOffer) },{ WAIT_MOVE,TX(validate) },{ WAIT_PLAYER,TX(error) } },//WAIT_MOVE
	{ { WAIT_MOVE,TX(sendAnswer) },	{ WAIT_PLAYER,TX(error) },{ WAIT_PLAYER,TX(error) },{ WAIT_PLAYER,TX(error) } }		//WAIT_PLAYER
	};

	//The action routines for the FSM
	void sendDices(genericEvent * ev);
	void prepareRobber(genericEvent * ev);
	void error(genericEvent * ev);
	void sendToRobberFSM(genericEvent * ev);
	void sendTradeOffer(genericEvent * ev);
	void sendAnswer(genericEvent * ev);
	void changeTurn(genericEvent * ev);
	void validate(genericEvent * ev);
	void doNothing(genericEvent * ev) {}

	list<networkingEv> expectedPackages;
	robberFSM * robberfsm;
public:
	networkingFSMopponentsTurn();
	list<networkingEv> getExpectedPackages();
};

enum robberStates : stateTypes { WAIT_USER, WAIT_ROBBCARDS, WAIT_ROBBMOVE };

enum robberFSMEvTypes : eventTypes { ROBBER_CARDS, ROBBER_MOVE, MY_CARDS, MY_CARDS_AND_WAIT };

class robberFSMEv : public genericEvent
{
public:
	robberFSMEv();
	robberFSMEv(robberFSMEvTypes type_); //if(valid) type(type_) {}
	robberFSMEvTypes getType() { return type; }
	bool getError();
private:
	//referencia al modelo de juego
	robberFSMEvTypes type;
	bool error = false;
};

class robberFSM : public genericFSM
{
private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[3][2] = {
	//	   ROBBER_CARDS					ROBBER_MOVE								MY_CARDS									MY_CARDS_AND_WAIT									
	{ { WAIT_USER,TX(error) },		 { WAIT_USER,TX(error) },			{ WAIT_ROBBMOVE,TX(sendCardsToOpponent) },	{ WAIT_ROBBCARDS,TX(sendCardsToOpponent) } },	//WAIT_USER
	{ { WAIT_ROBBMOVE,TX(sendCards)},{ WAIT_ROBBCARDS,TX(error) },		{ WAIT_ROBBCARDS,TX(error) },				{ WAIT_ROBBCARDS,TX(error) } },					//WAIT_ROBBCARDS
	{ { WAIT_ROBBMOVE,TX(error) },	 { WAIT_ROBBMOVE,TX(moveRobber) },	{ WAIT_ROBBMOVE,TX(error) },				{ WAIT_ROBBMOVE,TX(error) } }					//WAIT_ROBBMOVE
	};

	//The action routines for the FSM

	void error(genericEvent * ev);
	void sendCards(genericEvent * ev);
	void sendCardsToOpponent(genericEvent * ev);
	void moveRobber(genericEvent * ev);
public:
	robberFSM(stateTypes initState);	
};
