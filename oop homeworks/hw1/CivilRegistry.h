#ifndef CIVILREGISTRY_H
#define CIVILREGISTRY_H

#include"Citizen.h"
#include<list>

class CivilRegistry {
	list<Citizen> wApp;
	list<Citizen> wOutApp;
public:
	list<Citizen>::iterator getIterator(int);
	void insertCitizen(Citizen);
	void removeCitizen(int);
	int getSize(int);

};

#endif