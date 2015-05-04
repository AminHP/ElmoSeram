#include "ClientHandler.h"

#include <iostream>
#include <memory>

#include <Message.h>
#include <Consts.h>

using namespace std;


void ClientHandler::handleRequest(const string &msg)
{
	Parser p = Parser();
	p.parseString(msg);

	if (p["command"] == "login")
		handle_login(p);
	else if (p["command"] == "logout")
		handle_logout();
	else if (p["command"] == "signup")
		handle_signup(p);
	else if (p["command"] == "exists_user")
		handle_exists_user(p);
	else if (p["command"] == "send_pv_msg")
		handle_send_pv_msg(p);
	else if (p["command"] == "get_pv_msgs")
		handle_get_pv_msgs(p);
	else if (p["command"] == "add_friend")
		handle_add_friend(p);
	else if (p["command"] == "del_friend")
		handle_del_friend(p);
	else if (p["command"] == "get_friends")
		handle_get_friends(p);
}


bool ClientHandler::loggedIn()
{
	return mLoggedIn;
}

void ClientHandler::doLogin(const string &username)
{
	mLoggedIn = true;
	mUsername = username;

	addThisCH();
}

string ClientHandler::check_login(const string &username, const string &password)
{
	if (loggedIn())
		return "error_alreadyLoggedIn";

	shared_ptr<DB_Res> res(mDB->getUser(username));

	if (res->next())
	{
		if (res->getString("password") == HASH(password))
		{
			doLogin(username);
			return "ok";
		}

		return "error_pass";
	}

	return "error_user";
}

void ClientHandler::handle_login(Parser &p)
{
	string response = check_login(p["username"], p["password"]);
	putMsg("r_login " + response);
}

void ClientHandler::do_logout()
{
	removeThisCH();

	mLoggedIn = false;
	mUsername = "";
}

void ClientHandler::handle_logout()
{
	if (!loggedIn())
	{
		putMsg("r_logout error_login");
		return ;
	}

	do_logout();
	putMsg("r_logout ok");
}

bool ClientHandler::isValid_username(const std::string &username) const
{
	if (!username.size())
		return false;

	for (unsigned int i = 0; i < username.size(); i++)
	{
		char c = username[i];

		if (!(c >= '0' && c <= '9'))
			return false;
	}

	return true;
}

bool ClientHandler::isValid_password(const std::string &password) const
{
	if (!password.size())
		return false;

	for (unsigned int i = 0; i < password.size(); i++)
	{
		char c = password[i];

		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '.'))
			return false;
	}

	return true;
}

string ClientHandler::check_signup(const string &username, const string &password)
{
	if (!isValid_username(username))
		return "error_user_notValid";

	if (!isValid_password(password))
		return "error_pass_notValid";


	if (mDB->existsUser(username))
		return "error_exists";

	string hash = HASH(password);
	std::replace(hash.begin(), hash.end(), '"', '\"');
	mDB->addUser(username, hash);
	return "ok";
}

void ClientHandler::handle_signup(Parser &p)
{
	string response = check_signup(p["username"], p["password"]);
	putMsg("r_signup " + response);
}


void ClientHandler::handle_exists_user(Parser &p)
{
	if (mDB->existsUser(p["username"]))
		putMsg("r_exists_user yes");
	else
		putMsg("r_exists_user no");
}


void ClientHandler::handle_send_pv_msg(Parser &p)
{
	if (!loggedIn())
	{
		putMsg("r_send_pv_msg error_login");
		return ;
	}

	const string dst = p["pnt"];
	if (!mDB->existsUser(dst))
	{
		putMsg("r_send_pv_msg error_dst");
		return ;
	}

	mDateTime.update();

	p["command"] = "recv_pv_msg";
	p["pnt"]     = mUsername;
	p["date"]    = mDateTime.getDateStr();
	p["time"]    = mDateTime.getTimeStr();

	Message message(mUsername, dst, mDateTime.dti, p["body"]);
	mDB->addMessage(message);

	putMsg("r_send_pv_msg sent");

	ClientHandler *first = mClientHandlers_map->operator[](dst);
	if (first)
		first->putMsg4All(p.toStr());
}


void ClientHandler::handle_get_pv_msgs(Parser &p)
{
	if (!loggedIn())
	{
		putMsg("r_get_pv_msgs error_login");
		return ;
	}

	const string &type = p["type"];
	if (!type.size() || (!(type == "src" || type == "dst")))
	{
		putMsg("r_get_pv_msgs error_type");
		return ;
	}

	const string &date = p["date"];
	if (!date.size())
	{
		putMsg("r_get_pv_msgs error_date");
		return ;
	}

	const string &time = p["time"];
	if (!time.size())
	{
		putMsg("r_get_pv_msgs error_time");
		return ;
	}

	shared_ptr<DB_Res> res;
	string otherType = "src";
	if (type == "src")
	{
		res = shared_ptr<DB_Res> (mDB->getSentMessages(mUsername, date, time));
		otherType = "dst";
	}
	else if (type == "dst")
		res = shared_ptr<DB_Res> (mDB->getMessages(mUsername, date, time));

	if (!res->rowsCount())
		putMsg("r_get_pv_msgs empty");
	else
		while (res->next())
			putMsg("recv_pv_msg " + res->getString(otherType) + " " + res->getString("date") + " " + res->getString("time") + " " + res->getString("body"));
}


void ClientHandler::handle_add_friend(Parser &p)
{
	if (!loggedIn())
	{
		putMsg("r_add_friend error_login");
		return ;
	}

	const string &_friend = p["friend"];
	if (!_friend.size())
	{
		putMsg("r_add_friend error_friend");
		return ;
	}

	mDB->addFriend(mUsername, _friend);
	putMsg("r_add_friend ok");
	putMsg4All("recv_notify friends_changed");
}

void ClientHandler::handle_del_friend(Parser &p)
{
	if (!loggedIn())
	{
		putMsg("r_del_friend error_login");
		return ;
	}

	const string &_friend = p["friend"];
	if (!_friend.size())
	{
		putMsg("r_del_friend error_friend");
		return ;
	}

	mDB->delFriend(mUsername, _friend);
	putMsg("r_del_friend ok");
	putMsg4All("recv_notify friends_changed");
}

void ClientHandler::handle_get_friends(Parser &p)
{
	if (!loggedIn())
	{
		putMsg("r_get_friends error_login");
		return ;
	}

	shared_ptr<DB_Res> res(mDB->getFriends(mUsername));

	if (!res->rowsCount())
	{
		putMsg("r_get_friends empty");
		return ;
	}

	string friends = "";
	while (res->next())
		friends += " " + res->getString("friend");

	putMsg("r_get_friends" + friends);
}
