#include "ClientHandler.h"

#include <iostream>

using namespace std;

ClientHandler::ClientHandler(Socket *socket, map<string, ClientHandler*> *clientHandlers_map, boost::mutex *clientHandlers_mutex)
{
	mClientConnection = new Client(socket);
	mDB = new DB();

	mLoggedIn = false;
	mUsername = "";

	mClientHandlers_map   = clientHandlers_map;
	mClientHandlers_mutex = clientHandlers_mutex;

	mNextCH = NULL;
	mPrevCH = NULL;
}

ClientHandler::~ClientHandler()
{
	delete mClientConnection;
	delete mDB;

	removeThisCH();
}

void ClientHandler::run()
{
	runningThreads_counter = 3;

	boost::thread(&ClientHandler::thread_send, this);
	boost::thread(&ClientHandler::thread_recv, this);
	boost::thread(&ClientHandler::thread_analyse_recveied_data, this);
}

void ClientHandler::putMsg(const std::string &msg)
{
	sending_mutex.lock();
	sending_queue.push(msg);
	sending_mutex.unlock();
}

void ClientHandler::putMsg4All(const std::string &msg)
{
	putMsg(msg);

	if (mNextCH)
		mNextCH->putMsg4All(msg);
}

void ClientHandler::thread_send()
{
	while (mClientConnection->isConnected())
	{
		sending_mutex.lock();
		if (sending_queue.size())
		{
			string msg = sending_queue.front();
			sending_queue.pop();
			sending_mutex.unlock();

			mClientConnection->putMsg(msg);
		}
		else
			sending_mutex.unlock();
	}


	runningThreads_finish();

	//cerr << "cloesed thread 1" << endl;
}

void ClientHandler::thread_recv()
{
	while (true)
	{
		string msg = mClientConnection->getMsg();
		if (!mClientConnection->isConnected())
			break;

		received_mutex.lock();
		received_queue.push(msg);
		received_mutex.unlock();
	}

	runningThreads_finish();

	while (!runningThreads_isFinished());
	delete this;

	//cerr << "cloesed thread 2" << endl;
}

void ClientHandler::thread_analyse_recveied_data()
{
	while (true)
	{
		received_mutex.lock();
		if (received_queue.size())
		{
			string msg = received_queue.front();
			received_queue.pop();
			received_mutex.unlock();

			handleRequest(msg);
		}
		else
		{
			received_mutex.unlock();

			if (!mClientConnection->isConnected())
				break;
		}
	}

	runningThreads_finish();

	//cerr << "cloesed thread 3" << endl;
}

void ClientHandler::runningThreads_finish()
{
	runningThreads_mutex.lock();
	runningThreads_counter --;
	runningThreads_mutex.unlock();
}

bool ClientHandler::runningThreads_isFinished()
{
	runningThreads_mutex.lock();
	if (!runningThreads_counter)
	{
		runningThreads_mutex.unlock();
		return true;
	}
	else
		runningThreads_mutex.unlock();

	return false;
}
