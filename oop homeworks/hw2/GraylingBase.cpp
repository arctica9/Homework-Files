#include "GraylingBase.h"
#include <iostream>

using namespace std;

Grayling::Grayling() {
	alive = false;
}

Grayling::Grayling( char gender,string name) {
	this->age = 0;
	this->name = name;
	this->gender = gender;
	this->alive = true;
	this->mutant = false; //this will become true if it mutates
}