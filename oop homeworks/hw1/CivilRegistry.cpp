#include "CivilRegistry.h"
#include <iostream>
#include <string.h>

using namespace std;

void CivilRegistry::insertCitizen(Citizen x) {
	list<Citizen>::iterator it;

	if (x.getHasApp() == true) {
		it = wApp.begin();
		if (wApp.empty() == false) {
			while (it != wApp.end() && it->getAppTime() < x.getAppTime())
				it++;
			if (it == wApp.end()) {
				wApp.insert(it, x);
			}
			else if (it->getAppTime() == x.getAppTime()) {
				if (strcmp(it->getAppSlot(), x.getAppSlot()) > 0) {
					wApp.insert(it, x);
				}
				else if (strcmp(it->getAppSlot(), x.getAppSlot()) == 0) {
					while (it != wApp.end() && it->getAppTime().getEntryClock() < x.getAppTime().getEntryClock())
						it++;
					wApp.insert(it, x);
				}
				else {
					while (it != wApp.end() && strcmp(it->getAppSlot(), x.getAppSlot()) < 0)
						it++;
					wApp.insert(it, x);
				}					
			}
		}
		else {
			wApp.push_front(x);
		}
	}

	else if (x.getHasApp() == false) {

		it = wOutApp.begin();
		if (wOutApp.empty() == false) {
			while (it != wOutApp.end() && it->getAppTime() < x.getAppTime())
				it++;
			if (it == wOutApp.end()) {
				wOutApp.insert(it, x);
			}

			else if (it->getAppTime() == x.getAppTime()) {
				while (it != wOutApp.end() && it->getAppTime().getEntryClock() < x.getAppTime().getEntryClock())
					it++;
				wOutApp.insert(it, x);
			}

		}

		else {
			wOutApp.push_front(x);
		}

	}
}

void CivilRegistry::removeCitizen(int x) {
	if (x == 1) {
		list<Citizen>::iterator it = wApp.begin();
		delete[] it->idNo;
		delete[] it->name;
		delete[] it->surname;
		delete[] it->appSlot;
		 wApp.pop_front();
	}
	else if (x == 0) {
		list<Citizen>::iterator it = wOutApp.begin();
		delete[] it->idNo;
		delete[] it->name;
		delete[] it->surname;
		delete[] it->appSlot;
		wOutApp.pop_front();
	}
}

list<Citizen>::iterator CivilRegistry::getIterator(int x) {
	if (x == 1) {
		list<Citizen>::iterator it = wApp.begin();
		return it;
	}
	list<Citizen>::iterator it = wOutApp.begin();
	return it;
}

int CivilRegistry::getSize(int x) {
	if (x == 1)
		return wApp.size();
	return wOutApp.size();
}
