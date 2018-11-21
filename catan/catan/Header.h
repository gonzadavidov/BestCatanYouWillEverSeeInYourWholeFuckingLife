#pragma once

#include "eventHandling.h"

class allegroEventGenerator : public eventGenerator
{

public:
	allegroEventGenerator();
	genericEvent * getEvent(void);

private:

};

class networkingEventGenerator : public eventGenerator
{

public:
	allegroEventGenerator();
	genericEvent * getEvent(void);

private:

};