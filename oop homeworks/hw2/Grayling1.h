#include "GraylingBase.h"



class Grayling1 :public Grayling {
	std::string mutatedTo;
	double  MPI;
	double MP;
	double mutateAt;
public:
	Grayling1();
	Grayling1(char, std::string );
	void print() const;
	void givebirth() const;
	void aging();
	Grayling1(const Grayling1&, char, std::string);
};














