#include"Citizen.h"




using namespace std;

Citizen::Citizen(int minute, int hour, int day, int month, int year, char idNo[], char name[], char surname[], char hasApp[], char appSlot[]) {
	appTime = new Time(minute, hour, day, month, year);
	this->idNo = new char[strlen(idNo)+1];
	strcpy(this->idNo, idNo);
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->surname = new char[strlen(surname) + 1];
	strcpy(this->surname, surname);
	if (strcmp(hasApp, "TRUE") == 0)
		this->hasApp = true;
	else
		this->hasApp = false;
	this->appSlot = new char[strlen(appSlot) + 1];
	strcpy(this->appSlot, appSlot);	
};

Time Citizen::getAppTime() {
	return appTime->getWholeTime();
}


void Citizen::getInformation() {
	cout << name << endl;
}

const bool Citizen::getHasApp() {
	return hasApp;
}

const char* Citizen::getAppSlot() {
	return appSlot;
}