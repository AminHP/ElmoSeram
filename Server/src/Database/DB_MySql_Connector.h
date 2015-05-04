#ifndef __DB_MYSQL_CONNECTOR_H_
#define __DB_MYSQL_CONNECTOR_H_


#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "mysql_connection.h"


#include <Message.h>


typedef sql::ResultSet DB_Res;

class DB
{
private:
	sql::Driver *mDriver;
	sql::Connection *mCon;
	sql::Statement *mStmt;

private:
	void execute(const std::string &query);
	DB_Res *executeQuery(const std::string &query);

public:
	DB();
	~DB();

	DB_Res *getUser(const std::string &username);

	bool existsUser(const std::string &username);
	void addUser(const std::string &username, const std::string &password);

	void addMessage(const Message &msg);
	DB_Res *getMessages(const std::string &username, const std::string &date, const std::string &time);
	DB_Res *getSentMessages(const std::string &username, const std::string &date, const std::string &time);

	void addFriend(const std::string &user, const std::string &_friend);
	void delFriend(const std::string &user, const std::string &_friend);
	DB_Res *getFriends(const std::string &username);
};

#endif // __DB_MYSQL_CONNECTOR_H_
