#include "connectionEstablisher.h"
#include "Client.h"
#include "Server.h"


connectionEstablisher::connectionEstablisher()
{
}

void connectionEstablisher::startConnecting()
{
	clientToHear.startConnection("localhost");
}



connectionEstablisher::~connectionEstablisher()
{

}
