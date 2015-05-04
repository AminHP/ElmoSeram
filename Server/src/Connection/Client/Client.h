#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <iostream>

#include <boost/asio.hpp>

typedef boost::asio::ip::tcp::socket Socket;

class Client
{
private:
	Socket *mSocket;
	bool mConnected;

public:
	Client(Socket *socket);
	~Client();

	void putMsg(std::string msg);
	std::string getMsg();
	void closeSocket();

	bool isConnected() const;
};

#endif // __CLIENT_H_
