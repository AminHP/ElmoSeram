#include "DateTime.h"

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Consts.h"

using namespace std;
namespace pt = boost::posix_time;

void DateTime::update()
{
	pt::ptime current_date_time = pt::microsec_clock::universal_time();

	string year  = int2str(current_date_time.date().year());
	string month = int2str(current_date_time.date().month());
	string day   = int2str(current_date_time.date().day());

	dti.date = year + ((month.size() == 1) ? '0' + month : month) + ((day.size() == 1) ? '0' + day : day);
	dti.time = int2str(current_date_time.time_of_day().total_milliseconds());
}

string DateTime::getDateStr() const
{
	return dti.date;
}

string DateTime::getTimeStr() const
{
	return dti.time;
}
