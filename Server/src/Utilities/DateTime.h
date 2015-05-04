#ifndef __DATE_TIME_H_
#define __DATE_TIME_H_

#include <iostream>

struct DateTimeInfo
{
	std::string date;
	std::string time;
};

struct DateTime
{
	DateTimeInfo dti;

	void update();

	std::string getDateStr() const;
	std::string getTimeStr() const;
};

#endif // __DATE_TIME_H_
