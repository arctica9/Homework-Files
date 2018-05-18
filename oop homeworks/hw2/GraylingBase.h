#ifndef GRAYLINGBASE_H
#define GRAYLINGBASE_H

#include <string>
#include <iostream>
#include <list>

class Grayling{
protected:
	short age;
	std::string name; 
	char gender; 
	bool alive;
	bool mutant;
public:
	Grayling();
	Grayling(char, std::string );
	virtual void print() const = 0;
	virtual void givebirth() const= 0;
	virtual void aging() = 0; 
};


#endif
