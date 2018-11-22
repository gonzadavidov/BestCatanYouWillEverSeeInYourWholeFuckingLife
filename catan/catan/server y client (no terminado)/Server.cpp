#include "Server.h"


server::server()
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), PORT);
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler, ep);
}

/*Devuelve true si se conecto*/
/*PREGUNTAR QUE PASA, SI ES BLOQUEANTE O QUE CARAJO*/
bool server::startConnection()
{
	bool ret = true;
	//Uncomment if non-blocking mode is desired
	//
	//When non-blocking mode is chosen accept operation
	//will fail with boost::asio::error::would_block
	//if there's no client inmediatelly connected when accept operation is performed.
	//Must comment blocking mode.
	//
	server_acceptor->non_blocking(true);
	boost::system::error_code error;
	do
	{
		server_acceptor->accept(*socket, error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
		ret = false;
	//server_acceptor->accept(*socket_forServer);
	socket->non_blocking(true);
}

server::~server()
{
	server_acceptor->close();
	delete server_acceptor;
}
