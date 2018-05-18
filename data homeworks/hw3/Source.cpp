#include<fstream>
#include<iostream>
#include <string>

using namespace std;


struct patient {
	string info;
	int arriving;
	int treatment;
	string complaint;
	patient*next;
};

struct Queue {
	patient*front;
	patient*back;
	void create();
	void close();
	void enqueue(patient*);
	patient* dequeue();
	bool isempty();
};

int main() {
	
	string trash;
	ifstream dosya("patientsInfo.txt");
	int lineCounter=0;
	while (!dosya.eof()) {
		getline(dosya, trash);
		lineCounter++;
	}
	lineCounter--; //ilk satýrý atlamak için

	patient *n = new patient[lineCounter];

	dosya.clear(); //dosyanýn sonuna ulaþtýktan sonra eof'u temizlemek gerekiyor
	dosya.seekg(0, ios::beg); //ve dosyanýn baþýnda dönmeliyiz

	getline(dosya,trash); //ilk satýrdan kurtulmak için trash stringi kullandým

	for (int i = 0; i < lineCounter; i++) { //bütün bilgileri burada array'e atýyor
		dosya >> n[i].info; 
		dosya >> n[i].arriving;
		dosya >> n[i].treatment;
		dosya >> n[i].complaint;	
	}

	Queue RED; Queue YELLOW; Queue GREEN;
	RED.create(); YELLOW.create(); GREEN.create();

	int totalTime=0, currentTime=0;

	

	for (int i = 0; i < lineCounter; i++) {
		totalTime += n[i].treatment;
}


	int t = 0;

	for (int i = 0; i < lineCounter; i++) { //olasý boþ zaman için
		for (int j = 0; j < i; j++) {
			t += n[j].treatment;
		}
		if (t < n[i].arriving)
			totalTime += n[i].arriving - t;
		t = 0;
	}
	

	for (int i = 0; i < lineCounter; i++) { //þayet yeni hasta geldiyse diye, kontrol etmek için
		if (currentTime == n[i].arriving) {
			if (n[i].complaint.compare("RED") == 0)
				RED.enqueue(n + i);
			else if (n[i].complaint.compare("YELLOW") == 0)
				YELLOW.enqueue(n + i);
			else
				GREEN.enqueue(n + i);
		}
	}


	while (currentTime != totalTime) {


		if (RED.isempty() == false) {
			RED.front->treatment--;
			cout << currentTime+1 << ". time slice " << RED.front->info << endl;
			currentTime++;
			for (int i = 0; i < lineCounter; i++) { //curenttime'ý her arttýrýþýmda yeni birinin gelebilitesi var, o yüzden kontrol ediyorum
				if (currentTime == n[i].arriving) {
					if (n[i].complaint.compare("RED") == 0)
						RED.enqueue(n + i);
					else if (n[i].complaint.compare("YELLOW") == 0)
						YELLOW.enqueue(n + i);
					else
						GREEN.enqueue(n + i);
				}
			}
			if(RED.front->treatment!=0)//tedavi bitmediyse yellowa itele
				YELLOW.enqueue(RED.dequeue());
			else {//bittiyse hastayý yolla
				 RED.dequeue(); //delete operation u en sonda olacak
			}
				
		}

		else if (YELLOW.isempty() == false) {
			YELLOW.front->treatment--;
			cout << currentTime+1 << ". time slice " << YELLOW.front->info << endl;
			currentTime++;
			for (int i = 0; i < lineCounter; i++) {
				if (currentTime == n[i].arriving) {
					if (n[i].complaint.compare("RED") == 0)
						RED.enqueue(n + i);
					else if (n[i].complaint.compare("YELLOW") == 0)
						YELLOW.enqueue(n + i);
					else
						GREEN.enqueue(n + i);
				}
			}			if (YELLOW.front->treatment > 0) {
				YELLOW.front->treatment--;
				cout << currentTime+1 << ". time slice " << YELLOW.front->info << endl;
				currentTime++;

				for (int i = 0; i < lineCounter; i++) {
					if (currentTime == n[i].arriving) {
						if (n[i].complaint.compare("RED") == 0)
							RED.enqueue(n + i);
						else if (n[i].complaint.compare("YELLOW") == 0)
							YELLOW.enqueue(n + i);
						else
							GREEN.enqueue(n + i);
					}
				}

			}
			if (YELLOW.front->treatment != 0) 
				GREEN.enqueue(YELLOW.dequeue());
			
			else {
				YELLOW.dequeue(); 
			}
		}

		else if (GREEN.isempty() == false) {
			GREEN.front->treatment--;
			cout << currentTime+1 << ". time slice " << GREEN.front->info << endl;
			currentTime++;
			for (int i = 0; i < lineCounter; i++) {
				if (currentTime == n[i].arriving) {
					if (n[i].complaint.compare("RED") == 0)
						RED.enqueue(n + i);
					else if (n[i].complaint.compare("YELLOW") == 0)
						YELLOW.enqueue(n + i);
					else
						GREEN.enqueue(n + i);
				}
			}

			if (GREEN.front->treatment != 0) {
				GREEN.front->treatment--;
				cout << currentTime+1 << ". time slice " << GREEN.front->info << endl;
				currentTime++;
				for (int i = 0; i < lineCounter; i++) {
					if (currentTime == n[i].arriving) {
						if (n[i].complaint.compare("RED") == 0)
							RED.enqueue(n + i);
						else if (n[i].complaint.compare("YELLOW") == 0)
							YELLOW.enqueue(n + i);
						else
							GREEN.enqueue(n + i);
					}
				}

			}

			if (GREEN.front->treatment != 0) {
				GREEN.front->treatment--;
				cout << currentTime+1 << ". time slice " << GREEN.front->info << endl;
				currentTime++;
				for (int i = 0; i < lineCounter; i++) {
					if (currentTime == n[i].arriving) {
						if (n[i].complaint.compare("RED") == 0)
							RED.enqueue(n + i);
						else if (n[i].complaint.compare("YELLOW") == 0)
							YELLOW.enqueue(n + i);
						else
							GREEN.enqueue(n + i);
					}
				}

			}

			if (GREEN.front->treatment != 0) 
				GREEN.enqueue(GREEN.dequeue()); //hala bitmediyse yesildeki sýranýn sonuna atýyoruz
			
			else {
				GREEN.dequeue();
			}

		}

		else {
			
			currentTime++; //hasta yok, dümdüz currenttime'ý arttýrýyoruz
			for (int i = 0; i < lineCounter; i++) {
				if (currentTime == n[i].arriving) {
					if (n[i].complaint.compare("RED") == 0)
						RED.enqueue(n + i);
					else if (n[i].complaint.compare("YELLOW") == 0)
						YELLOW.enqueue(n + i);
					else
						GREEN.enqueue(n + i);
				}
			}
		}
	}







	delete[]n;


	return 0;
}

void Queue::create() {
	front = NULL; back = NULL;
}
void Queue::close() {
	patient *p;
	while (front) {
		p = front;
		front = front->next;
		delete p;
	}
}
void Queue::enqueue(patient *newdata) {
	
	newdata->next = NULL;
	if (isempty()) {
		back = newdata;
		front = back;
	}
	else {
		back->next = newdata;
		back = newdata;
	}
}

patient* Queue::dequeue() {
	patient *topnode;
	topnode = front;
	
	front = front->next;
	if (front == back) 
		back = front;
	return topnode;
}
bool Queue::isempty() {
	return front == NULL;
}


