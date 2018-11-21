#pragma once

#include "eventHandling.h"

enum implEvent : eventTypes { INPUT_EVENT, DONE, OUT, QUIT, CLOSE_DISPLAY };

class inputEv : public genericEvent
{
public:
	eventTypes getType(void) { return INPUT_EVENT; }
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