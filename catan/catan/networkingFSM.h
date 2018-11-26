#pragma once

#include "genericFSM.h"

enum netwStates : stateTypes { IDLE, ROBBER, WAIT_MOVE, WAIT_PLAYER };


class networkingFSMopponentsTurn : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][6] = {
	//	   ROBBER								DICESNOT7			BANK_TRADE	 		OFFER_TRADE			CONSTRUCTION	UNEXPECTED_EVENT					
	{ { ROBBER,TX(avisarcartas) },{ WAIT_MOVE,TX(verdespues) },{ IDLE,TX(error) },{ IDLE,TX(error) },{ IDLE,TX(error) },{ IDLE,TX(nada) } },			//IDLE
	{ { ROBBER,TX(mandar) },{ ,TX(pasarcomun) },{ ROBBER,TX(error) },{ ROBBER,TX(error) },{ ROBBER,TX(error) },{ROBBER,TX(error) } }, //ROBBER
	{ { WAIT_MOVE,TX(error) },{ WAIT_MOVE,TX(error) },{ WAIT_MOVE,TX(chequea) },{ WAIT_PLAYER,TX(wait) },{ WAIT_MOVE,TX(valida) },{ WAIT_MOVE,TX(error) } },			//WAIT_MOVE
	{ { WAIT_PLAYER,TX(error) },{ WAIT_PLAYER,TX(error) },{ START_MENU,TX(verdesp) },{ WAITING_TO_QUIT,TX(verdsp) },{ PLAYING,TX(end2) },{ PLAYING,TX(mandar) },{ PLAYING,TX(mandar) } },				//WAIT_PLAYER
	};

	//The action routines for the FSM

	void prueba1(genericEvent * ev)
	{

	}
public:
	networkingFSMopponentsTurn() : genericFSM(&fsmTable[0][0], 6, 7, IDLE) {}	//crear fsm chica, display (en fsm chica), atachear fsm chica como fuente de eventos
};

class robberFSM : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][7] = {
	//	   ROBBER_CARDS						ROBBER_MOVE											
	{ { START_MENU,TX(sendInput) },{ WAITING_CONNECTION,TX(verdespues) } },			//WAIT_CARDS
	{ { WAITING_CONNECTION,TX(mandar) },{ HANDSHAKING,TX(pasarcomun) } }, //WAIT_MOVE
	{ { HANDSHAKING,TX(mandar) },{ PLAYING,TX(verdespues) } }			//WAIT_USER
	};

	//The action routines for the FSM

	void prueba1(genericEvent * ev)
	{

	}
public:
	robberFSM() : genericFSM(&fsmTable[0][0], 6, 7, WAIT_CARDS) {}	//crear fsm chica, display (en fsm chica), atachear fsm chica como fuente de eventos
};
