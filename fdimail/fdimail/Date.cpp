#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include "Date.h"
#include <time.h>

//Shows the complete date, day and hour
std::string showDate(Date d)
{
	std::ostringstream resultado;
	tm ltm;
	localtime_s(&ltm, &d);
	resultado << 1900 + ltm.tm_year << '/' << 1 + ltm.tm_mon << '/' << ltm.tm_mday
		<< " (" << ltm.tm_hour << ':' << ltm.tm_min << ':' << ltm.tm_sec << ')';
	return resultado.str();
}

//Shows only the day, month and year 
std::string showDay(Date d)
{
	std::ostringstream resultado;
	tm ltm;
	localtime_s(&ltm, &d);
	resultado << 1900 + ltm.tm_year << '/' << 1 + ltm.tm_mon << '/' << ltm.tm_mday;
	return resultado.str();
}

Date turnDate(char* str)
{
	Date rawtime;
	tm* timeinfo;
	int year, month, day;

	std::replace(str, str + strlen(str), '/', ' ');
	std::istringstream(str) >> year >> month >> day;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	timeinfo->tm_year = year - 1900;
	timeinfo->tm_mon = month - 1;
	timeinfo->tm_mday = day;
	timeinfo->tm_hour = 0;
	timeinfo->tm_min = 0;
	timeinfo->tm_sec = 0;

	return mktime(timeinfo);
}