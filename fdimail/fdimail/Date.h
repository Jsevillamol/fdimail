#ifndef DATE
#define DATE
#include <ctime>
#include <string>
#include <sstream>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/*
This functions are responsible for showing the date.
It can show just the date, which is used in the 
uses active tray, to show the date when the mail 
was sent; or also the hour, which is used when you
are reading a mail, there you can see the date and 
the hour when the mail was sent
*/

typedef std::time_t Date;

std::string showDate(Date d);
std::string showDay(Date d);

Date turnDate(char str[256]);

#endif // !DATE
