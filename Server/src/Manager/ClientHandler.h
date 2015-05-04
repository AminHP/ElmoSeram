#ifndef __CLIENR_HANDLER_H_
#define __CLIENR_HANDLER_H_

#include <Client.h>

#include <queue>
#include <map>

#include <Parser.h>
#include <DB_MySql_Connector.h>
#include <DateTime.h>

#include <boost/thread.hpp>

class ClientHandler
{
private:
	Client *mClientConnection;
	DB *mDB;
	DateTime mDateTime;

	bool mLoggedIn;
	std::string mUsername;

private:
	std::map<std::string, ClientHandler*> *mClientHandlers_map;
	boost::mutex *mClientHandlers_mutex;

	ClientHandler *mNextCH;
	ClientHandler *mPrevCH;

public:
	void setNextCH(ClientHandler *ch);
	void setPrevCH(ClientHandler *ch);

	ClientHandler *getNextCH();
	ClientHandler *getPrevCH();

	void addThisCH();
	void removeThisCH();

private:
	std::queue<std::string> sending_queue;
	boost::mutex sending_mutex;

	std::queue<std::string> received_queue;
	boost::mutex received_mutex;

	unsigned int runningThreads_counter;
	boost::mutex runningThreads_mutex;
	void runningThreads_finish();
	bool runningThreads_isFinished();

	void putMsg(const std::string &msg);
	void putMsg4All(const std::string &msg);
	void thread_send();

	void thread_recv();
	void thread_analyse_recveied_data();

private:
	void handleRequest(const std::string &msg);

	bool loggedIn();
	void doLogin(const std::string &username);
	std::string check_login(const std::string &username, const std::string &password);
	void handle_login(Parser &p);

	void do_logout();
	void handle_logout();

	bool isValid_username(const std::string &username) const;
	bool isValid_password(const std::string &password) const;
	std::string check_signup(const std::string &username, const std::string &password);
	void handle_signup(Parser &p);

	void handle_exists_user(Parser &p);

	void handle_send_pv_msg(Parser &p);

	void handle_get_pv_msgs(Parser &p);

	void handle_add_friend(Parser &p);
	void handle_del_friend(Parser &p);
	void handle_get_friends(Parser &p);

public:
	ClientHandler(Socket *socket, std::map<std::string, ClientHandler*> *clientHandlers_map, boost::mutex *clientHandlers_mutex);
	~ClientHandler();

	void run();
};

#endif // __CLIENR_HANDLER_H_
