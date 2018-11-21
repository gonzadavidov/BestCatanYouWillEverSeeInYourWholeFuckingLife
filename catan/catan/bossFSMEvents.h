#pragma once

#include "eventHandling.h"

enum implEvent : eventTypes { INPUT_EVENT, DONE, OUT, QUIT, CLOSE_DISPLAY };

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
	eventTypes getType(void) { return OUT; }
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