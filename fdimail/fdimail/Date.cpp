#include"Date.h"

std::string& showDate(Date d)
{
	std::ostringstream resultado;
	tm ltm;
	localtime_s(&ltm, &d);
	resultado << 1900 + ltm.tm_year << '/' << 1 + ltm.tm_mon << '/' << ltm.tm_mday;
	resultado << ' (' << ltm.tm_hour << ':' << ltm.tm_min << ':' << ltm.tm_sec << ')';
	return resultado.str();
}

std::string& showDay(Date d)
{
	std::ostringstream resultado;
	tm ltm;
	localtime_s(&ltm, &d);
	resultado << 1900 + ltm.tm_year << '/' << 1 + ltm.tm_mon << '/' << ltm.tm_mday;
	return resultado.str();
}