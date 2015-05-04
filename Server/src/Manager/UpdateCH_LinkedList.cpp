#include "ClientHandler.h"

using namespace std;

void ClientHandler::setNextCH(ClientHandler *ch)
{
	mNextCH = ch;
}

void ClientHandler::setPrevCH(ClientHandler *ch)
{
	mPrevCH = ch;
}

ClientHandler *ClientHandler::getNextCH()
{
	return mNextCH;
}

ClientHandler *ClientHandler::getPrevCH()
{
	return mPrevCH;
}

void ClientHandler::addThisCH()
{
	ClientHandler *first = mClientHandlers_map->operator[](mUsername);

	if (first)
	{
		if (first->getNextCH())
			first->getNextCH()->setPrevCH(this);

		mPrevCH = first;
		mNextCH = first->getNextCH();
		first->setNextCH(this);
	}
	else
	{
		mClientHandlers_mutex->lock();
		mClientHandlers_map->operator[](mUsername) = this;
		mClientHandlers_mutex->unlock();
	}

	//cerr << this << "	" << mNextCH << "	" << mPrevCH << endl;
}

void ClientHandler::removeThisCH()
{
	if (mClientHandlers_map->operator[](mUsername) == this)
	{
		mClientHandlers_mutex->lock();
		mClientHandlers_map->operator[](mUsername) = mNextCH;
		mClientHandlers_mutex->unlock();
	}

	if (mPrevCH)
		mPrevCH->setNextCH(mNextCH);

	if (mNextCH)
		mNextCH->setPrevCH(mPrevCH);

	if (!mPrevCH && !mNextCH)
	{
		mClientHandlers_mutex->lock();
		mClientHandlers_map->operator[](mUsername) = NULL;
		mClientHandlers_mutex->unlock();
	}

	mPrevCH = NULL;
	mNextCH = NULL;

	/*ClientHandler *tmp = mClientHandlers_map->begin()->second;
	while (tmp)
	{
		cerr << tmp->getPrevCH() << "\t" << tmp << "\t" << tmp->getNextCH() << endl;
		tmp = tmp->getNextCH();
	}
	cerr << "--------------------------------------------" << endl;*/

	//cerr << this << "	" << mNextCH << "	" << mPrevCH << endl;
}
