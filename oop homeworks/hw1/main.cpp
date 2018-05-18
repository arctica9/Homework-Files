#include <iostream>
#include "Time.h"
#include"Citizen.h"
#include"CivilRegistry.h"
#include <fstream>
#include<string>
#include<list>


using namespace std;


int main() {
	
	int  minute, hour, day, month, year;
	char name[10], surname[10], hasApp[10], appSlot[10], idNo[10];
	char unnecessary;
	string unnecessary2;

	CivilRegistry list;


	ifstream dosya("input.txt");
	getline(dosya, unnecessary2);

	while (!dosya.eof()) {
		
		dosya >> idNo; dosya >> name; dosya >> surname; dosya >> hasApp;
		dosya >> day; dosya >> unnecessary; dosya >> month; dosya >> unnecessary; dosya >> year;
		dosya >> appSlot;
		dosya >> hour; dosya >> unnecessary; dosya >> minute;

		Citizen x(minute,hour,day, month, year, idNo, name, surname, hasApp, appSlot);
		list.insertCitizen(x);
		
	}
	
	cout << "Citizens with an appointment: " << endl;
	std::list<Citizen>::iterator it;
	int a = list.getSize(1); 
	int b = list.getSize(0);
	it = list.getIterator(1);
	it->getAppTime().getTime();

	for(int i=0;i<a;i++) {
		it->getInformation();
		list.removeCitizen(1);
		it = list.getIterator(1);
	}
	cout << endl << "Citizens without an appointment: " << endl;
	it = list.getIterator(0);
	for (int i = 0; i<b;i++) {
		it->getInformation();
		list.removeCitizen(0);
		it = list.getIterator(0);
	}


	dosya.close();


	return 0;
}
