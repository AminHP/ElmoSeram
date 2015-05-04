#ifndef __SERVER_H_
#define __SERVER_H_

#include <boost/asio.hpp>

typedef boost::asio::ip::tcp::socket Socket;

class Server
{
private:
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::acceptor *mAcceptor;

public:
	Server();
	~Server();

	void start();
	Socket *acceptClient();
	void closeSocket();
};

#endif // __SERVER_H_
