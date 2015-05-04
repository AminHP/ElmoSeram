#ifndef __MANAGER_H_
#define __MANAGER_H_

#include <Server.h>

#include <queue>
#include <map>

#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "ClientHandler.h"


class Manager
{
private:
	Server *mServerConnection;

	std::queue<boost::asio::ip::tcp::socket*> mConnectedClients_queue;
	boost::mutex mConnectedClients_mutex;

	std::map<std::string, ClientHandler*> mClientHandlers_map;
	boost::mutex mClientHandlers_mutex;

public:
	Manager();
	~Manager();

	void init();
	void run();

	void thread_acceptClients();
	void thread_createClientHandler();
};

#endif // __MANAGER_H_
