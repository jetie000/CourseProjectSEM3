#pragma once

class Date {
	int day;
	int month;
	int hours;
	int minutes;
public:
	void setDate();
	void getPrint();
	template<typename T>
	char* getPrint(T);
	int getMinutes() { return minutes; }
	int getHours() { return hours; }
	int getDay() { return day; }
	int getMonth() { return month; }
	int getTime() { return getDay() * 1440 + getHours() * 60 + getMinutes() + getMonth() * 17280; }
	Date operator =(Date obj);
};
