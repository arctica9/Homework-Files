#include"GraylingBase.h"



class Grayling3 :public Grayling {
	std::string mutatedTo;
	double  MPI;
	double MP;
	double mutateAt;

public:
	Grayling3();
	Grayling3( char,std::string);
	void print() const;
	void givebirth() const;
	void aging();
	Grayling3(const Grayling3&, char, std::string);

};