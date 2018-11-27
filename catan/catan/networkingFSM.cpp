#include "networkingFSM.h"


networkingFSMopponentsTurn::networkingFSMopponentsTurn() : genericFSM(&fsmTable[0][0], 4, 4, IDLE)
{
	expectedPackages = { DICES_ARE };
	robberfsm = nullptr;
}

/*ACTION ROUTINES FOR FSM*/

void networkingFSMopponentsTurn::sendDices(genericEvent * ev)
{
	//mandarle dados al modelo, el modelo debe cambiar los recursos de cada jugador
	//if (!catanGame->dicesThrown(dices))	//si no gano
	//{
		expectedPackages.clear();
		expectedPackages = { SETTLEMENT, ROAD, CITY, BANK_TRADE, OFFER_TRADE , PASS};
	//}
	//else								//si con esos dados gano el otro
	//{
	//	fsmEvent = new doneEv; 
	//	mandar YOU_WON
	//	expectedeEvents = { PLAY_AGAIN, GAME_OVER };
	//}
}

void networkingFSMopponentsTurn::prepareRobber(genericEvent * ev)
{
	expectedPackages.clear();
	expectedPackages = {ROBBER_CARDS, ROBBER_MOVE};
	/*if(catanGame->myplayer->cardsCount() > 7)
	{
		robberfsm = new robberFSM(WAIT_USER);
	}
	else if(catanGame->otherplayer->cardsCount() > 7)
	{
		robberfsm = new robberFSM(WAIT_ROBBCARDS);
	}
	else
	{
		robberfsm = new robberFSM(WAIT_ROBBMOVE);
	}	
	*/
}

void networkingFSMopponentsTurn::error(genericEvent * ev)
{
	if (robberfsm != nullptr)
	{
		delete robberfsm;
	}
	fsmEvent = new outEv("Unexpected networking event");
	expectedPackages.clear();
	//destruir todo lo que tenga que destruir
}

void networkingFSMopponentsTurn::sendToRobberFSM(genericEvent * ev)
{
	/*
	robberfsm->cycle(static_cast<stay_ev *>(ev)->additionalEvent)
	*/
}

void networkingFSMopponentsTurn::sendTradeOffer(genericEvent * ev)
{
	expectedPackages.clear();
	//catanGame->tradeOffered(tradeOffer)
	
}

void networkingFSMopponentsTurn::sendAnswer(genericEvent * ev)
{

}

void networkingFSMopponentsTurn::changeTurn(genericEvent * ev)
{
	//avisar que cambio el turno
	//
}

void networkingFSMopponentsTurn::validate(genericEvent * ev)
{

}

list<networkingEv> networkingFSMopponentsTurn::getExpectedPackages()
{
	return expectedPackages;
}


robberFSM::robberFSM(stateTypes initState) : genericFSM(&fsmTable[0][0], 3, 2, initState)
{

}

void robberFSM::error(genericEvent * ev)
{
	fsmEvent = new unexpectedNetwEvent("Unexpected event during Robber state");
	//borrar lo que haya que borrar
}

void robberFSM::sendCards(genericEvent * ev)
{
	//mandar robber cards del oponente al modelo
}

void robberFSM::sendCardsToOpponent(genericEvent * ev)
{
	//mandar robber cards propias al oponente
}

void robberFSM::moveRobber(genericEvent * ev)
{
	//mandar robber move al modelo
}
