#include"Grayling3.h"

Grayling3::Grayling3() :Grayling(), MPI(50), mutateAt(100) {}

Grayling3::Grayling3(char a, std::string b ) : Grayling(a, b), MPI(50), mutateAt(100) {
	this->mutatedTo = " "; // this value will be changed when it is required
	this->MP = 0;
}

void Grayling3::print() const {
	std::cout << "- Grayling 3 -> Age: " << age << " Name: " << name << " G:" << gender << " MPI: " << MPI << " MP: " << MP << " Mutate at: " << mutateAt << std::endl;
}

void Grayling3::givebirth() const {
	 if (alive == true)
		std::cout << "- Trying to GIVE BIRTH BUT No ability to give birth!" << std::endl;
	else 
		std::cout << "- Trying to GIVE BIRTH BUT " << name << " is not alive and No ability to give birth!" << std::endl;
}

void Grayling3::aging() {
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
		std::cout << "- " << name << " is dead because of HIGH MUTATION RATE!" << std::endl;
		alive = false;
		MP = 1000;
	}
}

Grayling3::Grayling3(const Grayling3 &x, char gender, std::string name) {
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
