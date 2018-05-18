#include <iostream>
#include <typeinfo>

class Money {
	int lira;
	int kurus;
public:
	Money(int, int);
	Money operator+(const Money&);
	Money operator-(const Money&);
	bool operator>(const Money&);
	bool operator<(const Money&);
	bool operator==(const Money&);
	friend std::ostream &operator<<(std::ostream&, const Money &);
};

Money::Money(int lira = 0, int kurus = 0) {
	if (lira < 0 || kurus<0) throw "Money cannot be less than zero";
	if (kurus > 99) throw "Kurus cannot be more than 99";

	this->lira = lira;
	this->kurus = kurus;

}

Money Money::operator+(const Money& z) {
	int lr, krs;
	lr = this->lira + z.lira;
	krs = this->kurus + z.kurus;
	if (krs > 99) {
		lr++;
		krs -= 100;
	}
	return Money(lr, krs);
}

Money Money::operator-(const Money& z) {
	int lr, krs;
	lr = this->lira - z.lira;
	krs = this->kurus - z.kurus;
	if (krs < 0) {
		lr--;
		krs += 100;
	}
	return Money(lr, krs);
}

bool Money::operator>(const Money& z) {
	int mny1, mny2;
	mny1 = 100 * this->lira + this->kurus;
	mny2 = 100 * z.lira + z.kurus;
	if (mny1 > mny2) return true;
	return false;
}

bool Money::operator<(const Money& z) {
	int mny1, mny2;
	mny1 = 100 * this->lira + this->kurus;
	mny2 = 100 * z.lira + z.kurus;
	if (mny1 < mny2) return true;
	return false;
}

bool Money::operator==(const Money& z) {
	int mny1, mny2;
	mny1 = 100 * this->lira + this->kurus;
	mny2 = 100 * z.lira + z.kurus;
	if (mny1 == mny2) return true;
	return false;
}

std::ostream& operator<<(std::ostream& stream, const Money & M) {
	stream << " " << M.lira << " lira " << M.kurus << " kurus";
	return stream;
}

//genericArray baþlangýcý



template <class Type>
class genericArray {
	int x;
	Type total;

public:
	genericArray(int);
	~genericArray();
	Type* elements;
	void sum();
	void operator=(const genericArray);
};

template <class Type>

void genericArray<Type>::sum() {
	for (int i = 0; i < x; i++)
		total = total + elements[i];

	std::cout << "The total of " << typeid(total).name() << " array is " << total << std::endl;

	if (total > 100) {
		total = total + 5;
		std::cout << "You have won 5 points, new total is " << total << std::endl;
	}
	else if (total < 100) {
		total = total - 5;
		std::cout << "You are punished 5 points, new total is " << total << std::endl;
	}
}
template <class Type>

genericArray<Type>::genericArray(int asd) : x(asd) {
	elements = new Type[x];
}

template <class Type>

genericArray<Type>::~genericArray() {
	delete[]elements;
}

template <class Type>

void genericArray<Type>::operator=(genericArray x) {
	this->total = x.total;
	delete[]elements;
	elements = new Type[total];
	for (int i = 0; i < total; i++)
		elements[i] = x.elements[i];
}





using namespace std;


int main() {

	genericArray <int> m1(5);
	genericArray <double> m2(5);
	genericArray <Money> m3(5);

	try { Money d(-1, 89); }

	catch (const char* x) {
		cout << x << endl;
	}

	try {
		Money a(10, 5);
		m3.elements[0] = a;
	}

	catch (const char* x) {
		cout << x << endl;
	}

	try {
		Money b(10, 5);
		m3.elements[1] = b;
	}

	catch (const char* x) {
		cout << x << endl;
	}

	try {
		Money c(43, 7);
		m3.elements[2] = c;


	}

	catch (const char* x) {
		cout << x << endl;
	}

	try {
		Money k(50, 6);
		m3.elements[3] = k;
	}

	catch (const char* x) {
		cout << x << endl;
	}

	try {
		Money m(10, 20);
		m3.elements[4] = m;
	}

	catch (const char* x) {
		cout << x << endl;
	}

	try { Money bonus(5, 0); }

	catch (const char* x) {
		cout << x << endl;
	}


	m2.elements[0] = 12.5;
	m2.elements[1] = 11.6;
	m2.elements[2] = 13.9;
	m2.elements[3] = 23.7;
	m2.elements[4] = 130.7;

	m1.elements[0] = 1;
	m1.elements[1] = 2;
	m1.elements[2] = 5;
	m1.elements[3] = 9;
	m1.elements[4] = 90;

	m3.sum();
	m2.sum();
	m1.sum();

	

	return 0;
}
