#include "Manager.h"

#include <iostream>
#include <tr1/memory>

#include <boost/thread.hpp>


using namespace std;
using namespace tr1;

Manager::Manager()
{
	mServerConnection = new Server();
}

Manager::~Manager()
{
	delete mServerConnection;
}

void Manager::init()
{
	mServerConnection->start();
}

void Manager::run()
{
	boost::thread(&Manager::thread_acceptClients, this);
	boost::thread(&Manager::thread_createClientHandler, this);

	while (true);
}

void Manager::thread_acceptClients()
{
	while (true)
	{
		Socket *socket = mServerConnection->acceptClient();

		mConnectedClients_mutex.lock();
		mConnectedClients_queue.push(socket);
		mConnectedClients_mutex.unlock();
	}
}

void Manager::thread_createClientHandler()
{
	while (true)
	{
		mConnectedClients_mutex.lock();
		if (mConnectedClients_queue.size())
		{
			Socket *socket = mConnectedClients_queue.front();
			mConnectedClients_queue.pop();
			mConnectedClients_mutex.unlock();

			ClientHandler *ch = new ClientHandler(socket, &mClientHandlers_map, &mClientHandlers_mutex);
			ch->run();
		}
		else
			mConnectedClients_mutex.unlock();
	}
}
