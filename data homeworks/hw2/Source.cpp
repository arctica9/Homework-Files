/* @Author
* Student Name: Murat Calda
* Student ID : 150140107
* Date: 01.11.17
*/


#include<iostream>
#include<cstring>
#include<fstream>
#define stricmp strcasecmp

using namespace std;


struct studentInfo {
	char name[20];
	char surname[20];
	char email[30];

	studentInfo* next;
	studentInfo* previous;
};

struct surnameMap {
	char surname[20];
	surnameMap* next;
	studentInfo* info;
};


struct List {
	surnameMap * head;
	void createList();
	void insertAll(ifstream&);
	void insertNewRecord(studentInfo*);
	void deleteStudent(studentInfo*);
	void deleteSurnameNode(surnameMap *);
	void updateList(studentInfo*, studentInfo*);
	void writeToFile();
	void deleteAll();
	void giveMail();
};

int main() {
	List s;
	ifstream dosya;
	dosya.open("dataset_wOutTurkishChars.txt");

	int secim = 0;
	while (secim != 8) {
		cout <<endl<<"e-mail Address Program:" << endl<<endl;
		cout << "1) Create" << endl;
		cout << "2) Insert All" << endl;
		cout << "3) Insert New Record" << endl;
		cout << "4) Delete Student" << endl;
		cout << "5) Delete Surname Node" << endl;
		cout << "6) Update" << endl;
		cout << "7) Write to File" << endl;
		cout << "8) Exit" << endl << endl;
		cout << "Enter a choice :" << endl;

		cin >> secim;

		if (secim == 1) {
			s.createList();
		}

		if (secim == 2) {
			s.insertAll(dosya);
			s.giveMail();
		}

		if (secim == 3) {
			studentInfo *np = new studentInfo;
			cout << "Enter the name of the new person: " << endl;
			cin >> np->name;
			cout << "Enter the surname: " << endl;
			cin >> np->surname;
			s.insertNewRecord(np);
			s.giveMail();
			delete np;
		}

		if (secim == 4) {
			studentInfo *np = new studentInfo;
			cout << "Enter the name and the surname of the person you want to delete: " << endl;
			cin >> np->name;
			cin >> np->surname;
			s.deleteStudent(np);
			s.giveMail();
			//fonksiyonun içinde zaten sildiðimden np'yi burada silmiyorum
		}

		if (secim == 5) {
			surnameMap* np = new surnameMap;
			cout << " Enter the surname: " << endl;
			cin >> np->surname;
			s.deleteSurnameNode(np);
			s.giveMail();
			delete np;
		}

		if (secim == 6) {
			studentInfo* np = new studentInfo;
			studentInfo*np2 = new studentInfo;
			cout << "Enter the name and the surname of the person you want to update: " << endl;
			cin >> np->name;
			cin >> np->surname;
			cout << "Enter the new name and the new surname of that person: " << endl;
			cin >> np2->name;
			cin >> np2->surname;
			s.updateList(np, np2);
			s.giveMail();
			delete np2;			
		}

		if (secim == 7) {
			s.writeToFile();
		}


	}


	s.deleteAll();
	return 0;
}

void List::createList(){
	head = new surnameMap;
	head->info = new studentInfo;
	head->info->next = NULL;
	head->next = new surnameMap;
	head->next->info = new studentInfo;
	head->next->info->next = NULL;
	head->next->next = head;
	head->next->surname[0] = 0;
	head->surname[0] = 0;
}

void List::insertAll(ifstream& x) {


	while (!x.eof()) {
		studentInfo*temp = new studentInfo;
		x >> temp->name;
		x >> temp->surname;

		insertNewRecord(temp);
		delete temp;
	}


	
}

void List::insertNewRecord(studentInfo *n) {

	surnameMap* temp = head;
	studentInfo*tempinfo = NULL;

	int i = 0;
	if (head->next->surname[0] == 0) {// ilk node'un boþ olup olmadýðýný kontrol ediyor
		strcpy(head->next->surname, n->surname);
		strcpy(head->next->info->surname, n->surname);
		strcpy(head->next->info->name, n->name);
		
	}

	else if (strcmp(head->next->surname,n->surname)!=0 && head->surname[0] == 0) { //son node'un boþ olup olmadýðýný kontrol ediyor, tabii ilk node'daki soyadla farklý olup olmadýðýný da
		strcpy(head->surname, n->surname);
		strcpy(head->info->surname, n->surname);
		strcpy(head->info->name, n->name);
		if (strcmp(head->surname, head->next->surname) < 0) {
			head = head->next;
		}

		
	}

	else {
		do {
			if (strcmp(n->surname, temp->surname) == 0) 
				break;
			temp = temp->next;
		} while (temp != head);// Ayný soyad grubundan var mý diye kontrol ediyor, varsa ona ekleyecek
		
		if (strcmp(n->surname, temp->surname) == 0) {//Soyad grubunu bulduysa yeni studentInfo açýp oraya ekleyecek
			studentInfo* nG = new studentInfo;
			strcpy(nG->name, n->name);
			strcpy(nG->surname, n->surname);
			tempinfo = temp->info;

			while (tempinfo->next != NULL && strcmp(tempinfo->name,nG->name)<=0) {
				tempinfo = tempinfo->next;
			}
			if (tempinfo == temp->info) {//ilk elemanda kalmýþ mý diye kontrol ediyor
				
				if (strcmp(tempinfo->name, nG->name) > 0) {
					nG->next = tempinfo;
					temp->info = nG;
					nG->next->previous = nG;
				}
				else {
					nG->next = tempinfo->next;
					nG->previous = tempinfo;
					tempinfo->next = nG;
				}
			}
			else if(tempinfo->next == NULL) { //Son eleman olarak mý yerleþecek?
				if (strcmp(tempinfo->name, nG->name) <= 0) {
					tempinfo->next = nG;
					nG->previous = tempinfo;
					nG->next = NULL;
				}
	
				else {
					nG->previous = tempinfo->previous;
					tempinfo->previous->next = nG;
					nG->next = tempinfo;
					tempinfo->previous = nG;
				}
			}
			else { //arada bir eleman olacak 
				nG->next = tempinfo->next;
				nG->previous = tempinfo;
				nG->next->previous = nG;
				nG->previous->next = nG;
			}

		}


		else { // yeni soyad node'u açacak
			temp = head->next;
			do {

				if (stricmp(temp->surname, n->surname) < 0 && stricmp(temp->next->surname, n->surname) > 0)
					break;
				temp = temp->next;
			} while (temp!=head);

			surnameMap* nG = new surnameMap;
			nG->info = new studentInfo;
			nG->info->next = NULL;
			strcpy(nG->surname, n->surname);
			strcpy(nG->info->surname, n->surname);
			strcpy(nG->info->name, n->name);

			if (stricmp(head->surname,nG->surname)<0){
				nG->next = head->next;
				head->next = nG;
				head = nG;
				
			}
			else if (stricmp(head->next->surname, nG->surname) > 0) {
				nG->next = head->next;
				head->next = nG;
			}

			else {
				nG->next = temp->next;
				temp->next = nG;
			}
		}

	}





}

void List::deleteStudent(studentInfo* n) {
	surnameMap* temp = head->next;
	surnameMap*temp3 = NULL;
	studentInfo*temp2 = NULL;
	do
	{
		if (stricmp(temp->next->surname, n->surname) == 0)
			break;
		temp = temp->next;

	} while (temp!=head->next);
	if (stricmp(temp->next->surname, n->surname) == 0) {
		temp2 = temp->next->info;
		while (temp2 != NULL) {
			if (stricmp(temp2->name, n->name) == 0)
				break;
			temp2 = temp2->next;
		}
		if (temp2 == temp->next->info&& temp2->next == NULL) {
			delete temp2;
			temp3 = temp->next;
			temp->next = temp->next->next;
			delete temp3;
		}
		else if (temp2 == temp->next->info) {
			temp->next->info = temp2->next;
			temp2->next->previous = NULL;
			delete temp2;
		}
		else if (temp2->next == NULL) {
			temp2->previous->next = NULL;
			delete temp2;
		}
		else if (temp2 == NULL) {
			cout << "The person you want to delete does not exist!" << endl;
			return;
		}
		else {
			temp2->next->previous = temp2->previous;
			temp2->previous->next = temp2->next;
			delete temp2;
		}

	}



	else {
		cout << "The person you want to delete is not exist!" << endl;
	}
	
}

void List::deleteSurnameNode(surnameMap* n) {
	surnameMap* temp = head->next;
	studentInfo* temp2 = NULL;
	studentInfo* temp3 = NULL;
	surnameMap* temp4 = NULL;

	do {
		if (stricmp(temp->next->surname, n->surname) == 0)
			break;
		temp = temp->next;
	} while (temp != head->next);

	if (stricmp(temp->next->surname, n->surname) == 0) {
		temp2 = temp->next->info;
		while (temp2!= NULL) {
			temp3 = temp2;
			temp2 = temp2->next;
			delete temp3;
		}
		temp4 = temp->next;
		temp->next = temp4->next;
		delete temp4;
	}
	else {
		cout << "The surname could not be found! Please try again later." << endl;
	}

}

void List::updateList(studentInfo* n, studentInfo* n2) {
	deleteStudent(n);
	insertNewRecord(n2);
}

void List::writeToFile() {
	surnameMap* temp = head->next;
	studentInfo*temp2 = NULL;
	ofstream x;
	x.open("emailList.txt");
	int i = 1;
	do {
		temp2 = temp->info;
		while (temp2 != NULL) {
			x << i << ".\t" << temp2->name << "\t" << temp2->surname << "\t" << temp2->email << endl;
			temp2 = temp2->next;
			i++;
		}
		temp = temp->next;
	} while (temp != head->next);

	x.close();
}

void List::deleteAll() {
	surnameMap*temp = head->next;
	surnameMap*temp4 = NULL;
	studentInfo*temp2 = NULL;
	studentInfo*temp3 = NULL;

	int i = 0;
	do {
		if (temp == head)
			i = 1;
		temp2 = temp->info;
		while (temp2!=NULL) {
			temp3 = temp2;
			temp2 = temp2->next;
			delete temp3;
		}
		temp4 = temp;
		temp = temp->next;
		delete temp4;
	} while (i==0);

}

void List::giveMail() {
	surnameMap* temp = head;
	studentInfo* tempinfo = NULL;
	char add[] = "@itu.edu.tr";
	do {
		tempinfo = temp->info;
		while (tempinfo != NULL) {
			int i = 0;
			while (tempinfo->surname[i]) {
				tempinfo->email[i] = tolower(tempinfo->surname[i]);
				i++;
			}
			tempinfo->email[i] = '\0';// bu iþlemi yapmadan strcat çalýþmadý. Sanýrým char array'inin sonunda \0 olmasý str fonksiyonlarý için þart.


			if (tempinfo != temp->info) {
				int i = 0;
				int a = 0;
				while (strlen(tempinfo->email)!=strlen(tempinfo->name)+strlen(tempinfo->surname) && strcmp(tempinfo->previous->email, tempinfo->email) >= 0) {
					a = strlen(tempinfo->email);
					tempinfo->email[strlen(tempinfo->email)] = tolower(tempinfo->name[i]);
					tempinfo->email[a + 1] = '\0';
					i++;
				}
				
				if (strlen(tempinfo->email) == strlen(tempinfo->name) + strlen(tempinfo->surname)) {
					a = strlen(tempinfo->email);
					tempinfo->email[strlen(tempinfo->email)] = 2;
					tempinfo->email[a + 1] = '\0';
				}
				
			
			}
			strcat(tempinfo->email, add);

			tempinfo = tempinfo->next;
		}



		temp = temp->next;
	} while (temp != head);
	
}


