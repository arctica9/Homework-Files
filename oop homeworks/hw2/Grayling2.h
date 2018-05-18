#include "GraylingBase.h"


class Grayling2 :public Grayling {
	std::string mutatedTo;
	double  MPI;
	double MP;
	double mutateAt;
public:
	Grayling2();
	Grayling2(char,std::string);
	void print() const;
	void givebirth() const;
	void aging();
	Grayling2(const Grayling2&, char, std::string);

};
