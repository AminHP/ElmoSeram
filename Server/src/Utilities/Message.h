#ifndef __MESSAGE_H_
#define __MESSAGE_H_

#include <iostream>
#include "DateTime.h"

struct Message
{
	const std::string &src;
	const std::string &dst;
	const DateTimeInfo &dti;
	std::string body;

	Message(const std::string &s, const std::string &d, const DateTimeInfo &dt, const std::string &b): 
			src(s), dst(d), dti(dt)
	{
		body = b;
		std::replace(body.begin(), body.end(), '"', '\"');
	}

	std::string asTuple() const
	{
		std::string res = "(0,";

		res += "'" + src + "'";
		res += ",'" + dst + "'";

		res += "," + dti.date;
		res += "," + dti.time;

		res += ",\"" + body + "\"";

		res += ")";

		return res;
	}
};

#endif // __MESSAGE_H_
