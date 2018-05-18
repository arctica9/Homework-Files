#include "Time.h"
#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;
Time Time::getWholeTime() {
	return *this;
}

Time::Time(int minute, int hour, int day, int month, int year) {
	this->minute = minute;
	this->hour = hour;
	this->day = day;
	this->month = month;
	this->year = year;
}

bool Time::operator<(const Time&x) {//kýyaslamayý sadece tarih üzerinden yaptým, zira appslot apptime'dan önemli 
	if (this->year < x.year)
		return true;
	else if (this->year==x.year && this->month < x.month)
		return true;
	else if (this->year == x.year && this->month == x.month && this->day < x.day)
		return true;
	else
		return false;
}

bool Time::operator>(const Time&x) {
	if (this->year > x.year)
		return true;
	else if (this->year == x.year && this->month > x.month)
		return true;
	else if (this->year == x.year && this->month == x.month && this->day > x.day)
		return true;
	else
		return false;
}

bool Time::operator==(const Time&x) {
	if (this->year == x.year && this->month == x.month && this->day == x.day)
		return true;
	else
		return false;
}

int Time::getEntryClock() {
	return minute + 100 * hour;
}

char* Time::getTime() { //when you use this, you must be sure to free the memory. Otherwise there will be a memoryleak
	char *x= new char[17];
	char*t = x;
	std::string s = std::to_string(hour);
	char temp[5];
	char*p = temp;
	std::strcpy(temp, s.c_str());

	while (*p != '\0') {
		*t = *p;
		t++; p++;
	}
	*t = '.'; t++;
	p = temp;
	s = std::to_string(minute);
	std::strcpy(temp, s.c_str());


	while (*p != '\0') {
		*t = *p;
		t++; p++;
	}
	*t = ' '; t++;

	p = temp;
	s = std::to_string(day);
	std::strcpy(temp, s.c_str());

	while (*p != '\0') {
		*t = *p;
		t++; p++;
	}
	*t = '/'; t++;
	p = temp;
	s = std::to_string(month);
	std::strcpy(temp, s.c_str());

	while (*p != '\0') {
		*t = *p;
		t++; p++;
	}
	*t = '/'; t++;
	p = temp;
	s = std::to_string(year);
	std::strcpy(temp, s.c_str());

	while (*p != '\0') {
		*t = *p;
		t++; p++;
	}
	*t = '\0';
	return x;
}
