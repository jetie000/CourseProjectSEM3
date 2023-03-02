#include "Date.h"
#include <iostream>
#include <time.h>

void Date::setDate()
{
	struct tm localtime;
	time_t now = time(NULL);
	localtime_s(&localtime, &now);
	day = localtime.tm_mday;
	month = 1 + localtime.tm_mon;
	hours = localtime.tm_hour % 24;
	minutes = localtime.tm_min;
}

void Date::getPrint() {
	std::cout << getPrint(hours) << ":" << getPrint(minutes) << "  " << getPrint(day) << "." << getPrint(month);
}

template<typename T>
char* Date::getPrint(T t)
{
	char* temp = new char[3];
	if (t < 10){
		temp[0] = '0';
		temp[1] = t + '0';
	}
	else {
		temp[0] = t / 10 + '0';
		while (t >= 10)
			t -= 10;
		temp[1] = t + '0';
	}
		temp[2] = '\0';
	return temp;
}

Date Date::operator =(Date obj) {
	day = obj.day;
	month = obj.month;
	hours = obj.hours;
	minutes = obj.minutes;
	return *this;
}