#ifndef DATE
#define DATE
#include <ctime>
#include <string>
#include <sstream>

typedef std::time_t Date;

std::string showDate(Date d);

std::string showDay(Date d);


#endif // !DATE
