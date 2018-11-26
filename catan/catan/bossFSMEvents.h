#pragma once

#include "eventHandling.h"

#include <iostream>

using namespace std;

enum implEvent : eventTypes { INPUT_EVENT, DONE, OUT, QUIT, CLOSE_DISPLAY , NETWORKING_EVENT , TIMER_EVENT};

//enunm Forward Declaration
//it is feasible as long as the type is defined in the code.
using inputEventTypes = unsigned int;

class inputEv : public genericEvent
{
public:
	eventTypes getType(void) { return INPUT_EVENT; }
	virtual inputEventTypes getInputEvType() = 0;
};

class doneEv : public genericEvent
{
public:
	eventTypes getType(void) { return DONE; }
};

class outEv : public genericEvent
{
public:
	outEv(string detail_) : detail(detail_) {}
	eventTypes getType(void) { return OUT; }
	string getDetail() { return detail; } 
private:
	const string detail;
};

class quitEv : public genericEvent
{
public:
	eventTypes getType(void) { return QUIT; }
};

class closeDisplayEv : public genericEvent
{
public:
	eventTypes getType(void) { return CLOSE_DISPLAY; }
};

class networkingEv : public genericEvent
{
public:
	eventTypes getType(void) { return NETWORKING_EVENT; }

};

class timerEv : public genericEvent
{
public:
	eventTypes getType(void) { return TIMER_EVENT; }
};