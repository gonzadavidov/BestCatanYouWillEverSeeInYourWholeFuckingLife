#include <iostream>
#include "eventHandling.h"
#include "genericFSM.h"


enum implStates : stateTypes {START_MENU, WAITING_CONNECTION, HANDSHAKING, PLAYING, REMATCH, WAITING_TO_QUIT };	

using namespace std;

class bossFSM : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&bossFSM::x)) //casteo a funcion, por visual

	const fsmCell fsmTable[6][5] = {
	//	   INPUT_EVENT								DONE								OUT	 						QUIT									CLOSE_DISPLAY
	{ { START_MENU,TX(sendInput)},		{ WAITING_CONNECTION,TX(verdespues)}, { START_MENU,TX(error)},		{ START_MENU,TX(end1)},				  { START_MENU,TX(end2) } },		//START_MENU
	{ { WAITING_CONNECTION,TX(mandar) },{ HANDSHAKING,TX(pasarcomun) },		  { START_MENU,TX(verdespues) },{ START_MENU,TX(verdsp)},			  { WAITING_CONNECTION,TX(end2) } },//WAITING_CONNECTION
	{ { HANDSHAKING,TX(mandar) },		{ PLAYING,TX(verdespues) },			  { START_MENU,TX(verdespues) },{ WAITING_TO_QUIT,TX(verdsp) },		  { HANDSHAKING,TX(end2) } },		//HANDSHAKING
	{ { PLAYING,TX(mandar) },			{ REMATCH,TX(avisarquiengano) },	  { START_MENU,TX(verdesp) },	{ WAITING_TO_QUIT,TX(verdsp) },		  { PLAYING,TX(end2) } },			//PLAYING
	{ { REMATCH,TX(mandar) },			{ HANDSHAKING,TX(verdesp) },		  { START_MENU,TX(verdesp) },	{ WAITING_TO_QUIT,TX(mandogameover) },{ REMATCH,TX(end2) } },			//REMATCH
	{ { WAITING_TO_QUIT,TX(mandar) },	{ START_MENU,TX(xqllegoack) },		  { START_MENU,TX(xqerror)},	{ WAITING_TO_QUIT,TX(nada) },		  { WAITING_TO_QUIT,TX(end2) } }	//WAITING_TO_QUIT
	};

	//The action routines for the FSM
	
	void prueba1(genericEvent * ev)
	{
	
	}

	bool quit_; //indica si hay que salir de la fsm, solo true cuando termina todo
public:
	bossFSM() : genericFSM(&fsmTable[0][0], 6, 5, START_MENU) {}	//crear fsm chica, display (en fsm chica), atachear fsm chica como fuente de eventos
	bool quit() { return quit_; };
};




int main(void)
{
	bossFSM fsm;
	//simpleEventGenerator s;	//generador de UN tipo de eventos
	allegroEventGenerator a;	//mouse, teclado, timer refresh pantalla
	
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

