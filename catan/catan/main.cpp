#include <iostream>
#include "eventHandling.h"
#include "genericFSM.h"

#define FPS 1

enum implStates : stateTypes {START_MENU, WAITING_CONNECTION, HANDSHAKING, PLAYING, REMATCH, WAITING_TO_QUIT };	

using namespace std;

class bossFSM : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][7] = {
	//	   INPUT_EVENT								DONE								OUT	 						QUIT								CLOSE_DISPLAY				NETWORKING_EVENT							TIMER_EVENT
	{ { START_MENU,TX(sendInput)},		{ WAITING_CONNECTION,TX(verdespues)}, { START_MENU,TX(error)},		{ START_MENU,TX(end1)},				  { START_MENU,TX(end2) },			{ START_MENU,TX(nada) },				  { START_MENU,TX(nada) } },			//START_MENU
	{ { WAITING_CONNECTION,TX(mandar) },{ HANDSHAKING,TX(pasarcomun) },		  { START_MENU,TX(verdespues) },{ START_MENU,TX(verdsp)},			  { WAITING_CONNECTION,TX(end2) },	{ WAITING_CONNECTION,TX(fijarsesierror) },{ WAITING_CONNECTION,TX(refresh) } }, //WAITING_CONNECTION
	{ { HANDSHAKING,TX(mandar) },		{ PLAYING,TX(verdespues) },			  { START_MENU,TX(verdespues) },{ WAITING_TO_QUIT,TX(verdsp) },		  { HANDSHAKING,TX(end2) },			{ HANDSHAKING,TX(mandar) },				  { HANDSHAKING,TX(mandar) } },			//HANDSHAKING
	{ { PLAYING,TX(mandar) },			{ REMATCH,TX(avisarquiengano) },	  { START_MENU,TX(verdesp) },	{ WAITING_TO_QUIT,TX(verdsp) },		  { PLAYING,TX(end2) },				{ PLAYING,TX(mandar) },					  { PLAYING,TX(mandar) } },				//PLAYING
	{ { REMATCH,TX(mandar) },			{ HANDSHAKING,TX(verdesp) },		  { START_MENU,TX(verdesp) },	{ WAITING_TO_QUIT,TX(mandogameover) },{ REMATCH,TX(end2) },				{ REMATCH,TX(mandar) },					  { REMATCH,TX(mandar) } },				//REMATCH
	{ { WAITING_TO_QUIT,TX(mandar) },	{ START_MENU,TX(xqllegoack) },		  { START_MENU,TX(xqerror)},	{ WAITING_TO_QUIT,TX(nada) },		  { WAITING_TO_QUIT,TX(end2) },		{ WAITING_TO_QUIT,TX(mandar) },	     	  { WAITING_TO_QUIT,TX(mandar) } }		//WAITING_TO_QUIT
	}; 

	//The action routines for the FSM
	
	void prueba1(genericEvent * ev)
	{
	
	}

	bool quit_; //indica si hay que salir de la fsm, solo true cuando termina todo
public:
	bossFSM() : genericFSM(&fsmTable[0][0], 6, 7, START_MENU) {}	//crear fsm chica, display (en fsm chica), atachear fsm chica como fuente de eventos
	bool quit() { return quit_; };
};




int main(void)
{
	bossFSM fsm;
	//simpleEventGenerator s;	//generador de UN tipo de eventos
	mouseEventGenerator m;	//mouse
	timerEventGenerator refreshTimer(FPS);	//timer para refrescar pantalla
	//timerEventGenerator timeout(); ver en que momento crearlo
	keyboardEventGenerator k;	//keyboard 
	
	mainEventGenerator eventGen;	//generador de eventos de TODO el programa

	eventGen.attach(&a);	//registro fuente de eventos

	do
	{
		genericEvent * ev;
		ev = eventGen.getNextEvent();
		if (ev->getType != NO_EVENT)
		{
			fsm.cycle(ev);
		}
		delete ev;
	} while (!fsm.quit());

	return 0;
}

/*
{} 
{}
{}
{}
*/
