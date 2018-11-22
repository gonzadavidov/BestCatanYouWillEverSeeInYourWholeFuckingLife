#include "Client.h"

client::client()
{
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

/*Devuelve true si se pudo conectar*/
/*PREGUNTAR QUE PASA, SI ES BLOQUEANTE O QUE CARAJO*/
/*PREGUNTAR POR EL PARAMETRO HOST QUE HACER*/
bool client::startConnection(const char* host)
{
	bool ret = false;
	endpoint = client_resolver->resolve(boost::asio::ip::tcp::resolver::query(host, PORT_STR));
	boost::system::error_code error;
	boost::asio::connect(*socket, endpoint, error);
	if (!error)
	{
		ret = true;
	}
	socket->non_blocking(true);
	return ret;
}

client::~client()
{
	delete client_resolver;
}
