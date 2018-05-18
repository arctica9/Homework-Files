/* @Author
* Student Name: Murat Calda
* Student ID : 150140107
* Date: 9.10.17
*/

struct searchedWord {
	int id;
	char* word;
	int wordLength;
	int yatay1, yatay2;
	int dikey1, dikey2;
	const char* type;
};

bool verticalSearch(char**, searchedWord*);
bool horizontalSearch(char**, searchedWord*);
bool diagonalSearch(char**, searchedWord*);

