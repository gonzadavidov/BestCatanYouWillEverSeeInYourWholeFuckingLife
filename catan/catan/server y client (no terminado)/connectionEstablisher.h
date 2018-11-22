#pragma once

#include "connector.h"


class connectionEstablisher : public eventGenerator
{
public:
	connectionEstablisher();
	void startConnecting();
	bool connectionEstablished();				//devuelve true si se establecio la conexion
	connector * getConnector();		//devuelve un connector (client o server) si se pudo conectar, sino nullptr 
	~connectionEstablisher();

private:
	connector * currentConnector;
	client clientToHear;
};

