#include "Client.h"

#include <Consts.h>

using namespace std;

Client::Client(Socket *socket)
{
	mSocket = socket;
	mConnected = true;

	mSocket->set_option(boost::asio::ip::tcp::no_delay(true));

	/*struct timeval tv;
	tv.tv_sec  = 1;
	tv.tv_usec = 0;
	setsockopt(socket->native(), SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	setsockopt(socket->native(), SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));*/
}

Client::~Client()
{
	closeSocket();
	delete mSocket;
}

void Client::putMsg(const string msg)
{
	boost::asio::write(*mSocket, boost::asio::buffer(msg + CONNECTION_END_STR));
}

string Client::getMsg()
{
	boost::asio::streambuf stream;
	try
	{
		//char msg[1024];
		//mSocket->read_some(boost::asio::buffer(msg, 1024));

		size_t n = boost::asio::read_until(*mSocket, stream, CONNECTION_END_STR);
		boost::asio::streambuf::const_buffers_type bufs = stream.data();
		string all(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + n - strlen(CONNECTION_END_STR));
		return all;
	}
	catch(const exception &e)
	{
		mConnected = false;
		return "";
	}
}

void Client::closeSocket()
{
	mSocket->close();
	mConnected = false;
}

bool Client::isConnected() const
{
	return mConnected;
}
