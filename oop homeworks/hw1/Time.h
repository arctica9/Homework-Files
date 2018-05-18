#ifndef TIME_H
#define TIME_H

class Time {
	friend class CivilRegistry;
private:
	int day;
	int month;
	int year;
	int hour;
	int minute;
public:
	Time(int, int, int, int, int);
	Time getWholeTime();
	char* getTime();
	bool operator<(const Time&);
	bool operator>(const Time&);
	bool operator==(const Time&);
	int getEntryClock();
};

#endif