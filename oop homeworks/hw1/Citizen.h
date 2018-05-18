#ifndef CITIZEN_H
#define CITIZEN_H
#include "Time.h"
#include<iostream>
#include<string.h>


using namespace std;

class Citizen {
	friend class CivilRegistry;

	char* idNo;
	char*name;
	char*surname;
	bool hasApp;
	Time*appTime;
	char*appSlot;

public:
	const char* getAppSlot(); //i did them const because i don't want that their values are changed
	const bool getHasApp();
	Citizen(int, int, int, int, int, char[], char[], char[], char[], char[]);
	Time getAppTime();
	void getInformation();
};

#endif