#include "Grayling1.h"


Grayling1::Grayling1() :Grayling(), MPI(30), mutateAt(60) {}

Grayling1::Grayling1(char a, std::string b) :Grayling(a, b), MPI(30),mutateAt(60) {
	this->mutatedTo = " "; // this value will be changed when it is required
	this->MP = 0;
}

void Grayling1::print() const {
	if (mutant == false)
		std::cout << "- Grayling 1 -> Age: " << age << " Name: " << name << " G:" << gender << " MPI: " << MPI << " MP: " << MP << " Mutate at: " << mutateAt << std::endl;
	else
		std::cout << "- Grayling 2 -> Age: " << age << " Name: " << name << " G:" << gender << " MPI: " << MPI << " MP: " << MP << " Mutate at: " << mutateAt << std::endl;
}

void Grayling1::givebirth() const {
	if (alive == true && mutant == false)
		std::cout << "- " << name << " gave birth to 2 offsprings!" << std::endl;

	else if (alive == true && mutant == true)
		std::cout << "- " << name << " gave birth to 1 offsprings!" << std::endl;

	else if (alive == false)
		std::cout << "- Trying to GIVE BIRTH BUT " << name << " is not alive" << std::endl;
	
}

void Grayling1::aging() {
	if (alive == true) {

		age++;
		MP += MPI;
	}
	else if (alive == false) {
		std::cout << "- Trying to AGING BUT " << name << " is not alive " << std::endl;
	}

	if (MP < mutateAt) {
		std::cout << "- AGING: name: " << name <<" ->"<< mutatedTo << "Age: " << age << " MPI: " << MPI << " MP: " << MP << std::endl;
	}

	else if (MP == mutateAt) {
		std::cout << "- AGING: name: " << name <<" ->"<< mutatedTo << "Age: " << age << " MPI: " << MPI << " MP: " << MP << std::endl;
		mutatedTo = " Grayling 2 ";
		std::cout << "- Mutated TO: " << mutatedTo << std::endl;
		MP = 0;
		MPI = 40;
		mutant = true;
	}

	if (age == 4) {
		std::cout << "- AGING: name: " << name <<" ->"<< mutatedTo << "Age: " << age << " MPI: " << MPI << " MP: " << MP << std::endl;
		std::cout << "- " << name << " is dead because of AGING!" << std::endl;
		alive = false;
		MP = 1000; //to make sure that it wont enter other loops after fish's death
	}
}


Grayling1::Grayling1(const Grayling1 &x, char gender, std::string name) {
	this->age = x.age;
	this->alive = x.alive;
	this->gender = gender;
	this->MP = x.MP;
	this->MPI = x.MPI;
	this->mutant = x.mutant;
	this->mutateAt = x.mutateAt;
	this->mutatedTo = x.mutatedTo;
	this->name = name;
}
