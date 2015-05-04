#include "Parser.h"

#include <iostream>

#include "Consts.h"

using namespace std;

Parser::Parser()
{
	fillCommand();
}

Parser::~Parser()
{
}

void Parser::parseString(const string &msg)
{
	string value = "";

	unsigned int queue_index = 0;

	string cmd = "";
	for (unsigned int i = 0; i < msg.size(); i++)
	{
		if (msg[i] != ' ')
		{
			value += msg[i];
		}
		else if (msg[i - 1] != ' ')
		{
			if (cmd == "")
			{
				cmd = value;
				if (!commandFound(cmd))
				{
					mData["command"] = "none";
					break;
				}
				mData["command"] = value;
			}
			else
				mData[mCommand[cmd][queue_index++]] = value;

			value = "";
		}

		if (cmd != "" && mCommand[cmd].size() - 1 == queue_index)
		{
			mData[mCommand[cmd][queue_index]] = string(msg.c_str() + i + 1, msg.c_str() + msg.size());
			break;
		}

		if (cmd == "" && i == msg.size() - 1)
		{
			if (!commandFound(value))
				mData["command"] = "none";
			else
				mData["command"] = value;
		}
	}

	//for (dat_itr it = mData.begin(); it != mData.end(); it++)
	//	cerr << it->first << "		" << it->second << endl;
}

void Parser::fillCommand()
{
	const string login[] = {"username", "password"};
	mCommand["login"] = vector<string> (login, login + arrlen(login));

	//const string r_login[] = {"response"};
	//mCommand["r_login"] = vector<string> (r_login, r_login + arrlen(r_login));

	const string logout[] = {};
	mCommand["logout"] = vector<string> (logout, logout + arrlen(logout));

	const string signup[] = {"username", "password"};
	mCommand["signup"] = vector<string> (signup, signup + arrlen(signup));

	//const string r_signup[] = {"response"};
	//mCommand["r_signup"] = vector<string> (r_signup, r_signup + arrlen(r_signup));

	const string exists_user[] = {"username"};
	mCommand["exists_user"] = vector<string> (exists_user, exists_user + arrlen(exists_user));

	const string send_pv_msg[] = {"pnt", "body"};
	mCommand["send_pv_msg"] = vector<string> (send_pv_msg, send_pv_msg + arrlen(send_pv_msg));

	const string recv_pv_msg[] = {"pnt", "date", "time", "body"};
	mCommand["recv_pv_msg"] = vector<string> (recv_pv_msg, recv_pv_msg + arrlen(recv_pv_msg));

	const string get_pv_msgs[] = {"type", "date", "time"};
	mCommand["get_pv_msgs"] = vector<string> (get_pv_msgs, get_pv_msgs + arrlen(get_pv_msgs));

	const string add_friend[] = {"friend"};
	mCommand["add_friend"] = vector<string> (add_friend, add_friend + arrlen(add_friend));

	const string del_friend[] = {"friend"};
	mCommand["del_friend"] = vector<string> (del_friend, del_friend + arrlen(del_friend));

	const string get_friends[] = {};
	mCommand["get_friends"] = vector<string> (get_friends, get_friends + arrlen(get_friends));


	//for (cmd_itr it = mCommand.begin(); it != mCommand.end(); it++)
	//	for (unsigned int i = 0; i < it->second.size(); i++)
	//		cerr << it->first << "	" << it->second[i] << endl;
}

bool Parser::commandFound(const string &cmd)
{
	return (mCommand.find(cmd) == mCommand.end()) ? false : true;
}

string &Parser::operator[](const string &key)
{
	return mData[key];
}

string Parser::toStr()
{
	string res = "";

	string cmd = mData["command"];
	unsigned int n = mCommand[cmd].size();

	res += cmd;
	for (unsigned int i = 0; i < n; i++)
		res += ' ' + mData[mCommand[cmd][i]];

	return res;
}
