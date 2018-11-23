#pragma once

#include "genericFSM.h"

class playingFSM : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[5][5] = {
		//offer_trade					build					validate_building							validate_oponent_trade														robber	
	{ { EXCHANGE,TX(mandaroferta) },{ BUILDING,TX(construyo) },{ MY_TURN,TX(nada) },						{ MY_TURN,TX(NADA) },													{ MY_TURN,TX(sacarcartasymoverrobber) } },			//MY_TURN
	{ { OPONENT_TURN,TX(nada) },	{ OPONENT_TURN,TX(nada) }, { OPONENT_TURN,TX(verificojugadaoponente) },{ OPONENT_EXCHANGE,TX(verificoelcambioysiesparamidecidosiaceptoonodsp) },{ OPONENT_TURN,TX(sacarcartas) },{ WAITING_CONNECTION,TX(fijarsesierror) },{ WAITING_CONNECTION,TX(refresh) } }, //OPPONENT_TURN
	{ { ,TX(mandar) },{ PLAYING,TX(verdespues) },{ START_MENU,TX(verdespues) },{ WAITING_TO_QUIT,TX(verdsp) },{ HANDSHAKING,TX(end2) },{ HANDSHAKING,TX(mandar) },{ HANDSHAKING,TX(mandar) } },			//BUILDING
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