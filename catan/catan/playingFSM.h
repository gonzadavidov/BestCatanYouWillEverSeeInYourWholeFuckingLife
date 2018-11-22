#pragma once

#include "genericFSM.h"

class playingFSM : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][7] = {
		//
	{ { START_MENU,TX(sendInput) },{ WAITING_CONNECTION,TX(verdespues) },{ START_MENU,TX(error) },{ START_MENU,TX(end1) },{ START_MENU,TX(end2) },{ START_MENU,TX(nada) },{ START_MENU,TX(nada) } },			//MY_TURN
	{ { WAITING_CONNECTION,TX(mandar) },{ HANDSHAKING,TX(pasarcomun) },{ START_MENU,TX(verdespues) },{ START_MENU,TX(verdsp) },{ WAITING_CONNECTION,TX(end2) },{ WAITING_CONNECTION,TX(fijarsesierror) },{ WAITING_CONNECTION,TX(refresh) } }, //OPPONENT_TURN
	{ { HANDSHAKING,TX(mandar) },{ PLAYING,TX(verdespues) },{ START_MENU,TX(verdespues) },{ WAITING_TO_QUIT,TX(verdsp) },{ HANDSHAKING,TX(end2) },{ HANDSHAKING,TX(mandar) },{ HANDSHAKING,TX(mandar) } },			//BUILDING
	{ { PLAYING,TX(mandar) },{ REMATCH,TX(avisarquiengano) },{ START_MENU,TX(verdesp) },{ WAITING_TO_QUIT,TX(verdsp) },{ PLAYING,TX(end2) },{ PLAYING,TX(mandar) },{ PLAYING,TX(mandar) } },				//OPPONENT_EXCHANGE
	{ { REMATCH,TX(mandar) },{ HANDSHAKING,TX(verdesp) },{ START_MENU,TX(verdesp) },{ WAITING_TO_QUIT,TX(mandogameover) },{ REMATCH,TX(end2) },{ REMATCH,TX(mandar) },{ REMATCH,TX(mandar) } }				//EXCHANGE
	};

	//The action routines for the FSM

	void prueba1(genericEvent * ev)
	{

	}

public:
	playingFSM(state initState) : genericFSM(&fsmTable[0][0], 6, 7, initState) {}	//crear fsm chica, display (en fsm chica), atachear fsm chica como fuente de eventos
};