#include "networkingFSM.h"


networkingFSMopponentsTurn::networkingFSMopponentsTurn() : genericFSM(&fsmTable[0][0], 4, 4, IDLE)
{
	expectedEvents = { DICES_ARE };
	robberfsm = nullptr;
}

/*ACTION ROUTINES FOR FSM*/

void networkingFSMopponentsTurn::sendDices(genericEvent * ev)
{
	//mandarle dados al modelo
}

void networkingFSMopponentsTurn::prepareRobber(genericEvent * ev)
{
	/*if(myplayer->cardsCount() > 7)
	{
		robberfsm = new robberFSM(WAIT_USER);
	}
	else if(otherplayer->cardsCount() > 7)
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

}

void networkingFSMopponentsTurn::sendAnswer(genericEvent * ev)
{

}

void networkingFSMopponentsTurn::validate(genericEvent * ev)
{

}

list<networkingEv> networkingFSMopponentsTurn::getExpectedEvents()
{
	return expectedEvents;
}

