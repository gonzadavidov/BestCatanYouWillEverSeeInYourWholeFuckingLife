#include <iostream>
#include "eventHandling.h"
#include "genericFSM.h"


enum implStates : stateTypes {START_MENU, WAITING_CONNECTION, HANDSHAKING, PLAYING, REMATCH, WAITING_TO_QUIT };	

using namespace std;
class fksdopfsdj : public genericFSM
{


private:

#define TX(x) (static_cast<void (genericFSM::* )(genericEvent *)>(&FSMImplementation::x)) //casteo a funcion, por visual
	const fsmCell fsmTable[6][4] = {
	//		QUEHACEMOSMIERDA               EventB                  EventC                  EventD
	{ { State0,TX(prueba1) },{ State1,TX(prueba2) },{ State2,TX(prueba3) },{ State3,TX(prueba4) } },   //START_MENU
	{ { State1,TX(prueba1) },{ State2,TX(prueba2) },{ State3,TX(prueba3) },{ State0,TX(prueba4) } },   //WAITING_CONNECTION
	{ { State2,TX(prueba1) },{ State3,TX(prueba2) },{ State0,TX(prueba3) },{ State1,TX(prueba4) } },   //HANDSHAKING
	{ { State3,TX(prueba1) },{ State0,TX(prueba2) },{ State1,TX(prueba3) },{ State2,TX(prueba4) } },   //PLAYING
	{ { State2,TX(prueba1) },{ State3,TX(prueba2) },{ State0,TX(prueba3) },{ State1,TX(prueba4) } },   //REMATCH
	{ { State3,TX(prueba1) },{ State0,TX(prueba2) },{ State1,TX(prueba3) },{ State2,TX(prueba4) } }    //WAITING_TO_QUIT
	};

	//The action routines for the FSM
	//These actions should not generate fsmEvents

	void prueba1(genericEvent * ev)
	{
		cout << "prueba 1" << endl;
		return;
	}
	void prueba2(genericEvent * ev)
	{
		cout << "prueba 2" << endl;
		return;
	}
	void prueba3(genericEvent * ev)
	{
		cout << "prueba 3" << endl;
		return;
	}
	void prueba4(genericEvent * ev)
	{
		cout << "prueba 4" << endl;
		return;
	}

public:
	FSMImplementation() : genericFSM(&fsmTable[0][0], 4, 4, State0) {}
};




int main(void)
{

	return 0;
}

