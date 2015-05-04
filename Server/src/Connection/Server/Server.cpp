#include "Server.h"

#include <Consts.h>

using namespace std;
using boost::asio::ip::tcp;

Server::Server()
{
}

Server::~Server()
{
	closeSocket();
	delete mAcceptor;
}

void Server::start()
{
	tcp::endpoint endpoint(tcp::v4(), CONNECTION_PORT);
	mAcceptor = new tcp::acceptor(io_service, endpoint);
}

Socket *Server::acceptClient()
{
	Socket *socket = new Socket(io_service);
	mAcceptor->accept(*socket);

	return socket;
}

void Server::closeSocket()
{
	mAcceptor->close();
}
