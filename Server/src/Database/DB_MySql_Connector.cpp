#include "DB_MySql_Connector.h"

#include "Consts.h"

using namespace std;
using namespace sql;

DB::DB()
{
	mDriver = get_driver_instance();
	mCon = mDriver->connect(string("tcp://") + DB_HOST + ":" + DB_PORT, DB_USER, DB_PASS);
	mCon->setSchema(DB_NAME);
	mStmt = mCon->createStatement();
}

DB::~DB()
{
	delete mCon;
	delete mStmt;
}

void DB::execute(const std::string &query)
{
	mStmt->execute(query);
}

DB_Res *DB::executeQuery(const std::string &query)
{
	DB_Res *res = mStmt->executeQuery(query);

	return res;
}


DB_Res *DB::getUser(const string &username)
{
	return executeQuery("SELECT password FROM t_users WHERE username='" + username + "'");
}

bool DB::existsUser(const std::string &username)
{
	DB_Res *res = executeQuery("SELECT 1 FROM t_users WHERE username='" + username + "'");

	bool res_bool = (res->next()) ? true : false;
	delete res;

	return res_bool;
}

void DB::addUser(const std::string &username, const std::string &password)
{
	execute("INSERT INTO t_users VALUES ('" + username + "', \"" + password + "\",'')");
}


void DB::addMessage(const Message &msg)
{
	execute("INSERT INTO t_messages VALUES " + msg.asTuple());
}

DB_Res *DB::getMessages(const string &username, const string &date, const string &time)
{
	return executeQuery("SELECT src,date,time,body FROM t_messages WHERE dst='" + username + "' AND ((date>'" + date + "') OR (date='" + date + "' AND time>='" + time + "'))");
}

DB_Res *DB::getSentMessages(const std::string &username, const std::string &date, const std::string &time)
{
	return executeQuery("SELECT dst,date,time,body FROM t_messages WHERE src='" + username + "' AND ((date>'" + date + "') OR (date='" + date + "' AND time>='" + time + "'))");
}


void DB::addFriend(const std::string &user, const std::string &_friend)
{
	execute("INSERT INTO t_friends VALUES (0,'" + user + "','" + _friend + "')");
}

void DB::delFriend(const std::string &user, const std::string &_friend)
{
	execute("DELETE FROM t_friends WHERE user='" + user + "' AND friend='" + _friend + "'");
}

DB_Res *DB::getFriends(const std::string &username)
{
	return executeQuery("SELECT friend FROM t_friends WHERE user='" + username + "'");
}
