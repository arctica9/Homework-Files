/* @Author
* Student Name: Murat Calda
* Student ID : 150140107
* Date: 9.10.17
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include<cstdlib>
#include"functions.h"
#include<string.h>


using namespace std;


int main()
{
	int i = 0;
	char **puzzleArray = new char*[15];
	for (int i = 0; i < 15; i++) {
		puzzleArray[i] = new char[15];
	}
	char **puzzleArrayPtr = puzzleArray;
	ifstream puzzle;
	puzzle.open("puzzle.txt");


	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			puzzle >> *(*(puzzleArrayPtr+j)+i);
		}
	}

	FILE* words;
	words = fopen("searchedwords.txt", "r");

	FILE*info;
	info = fopen("foundWordsInfo.txt", "w+");

	FILE*last;
	last = fopen("lastVersionPuzzle.txt", "w+");

	searchedWord* ara = new searchedWord[9];

	char gecici[30]; //to store the words for the first step

	for (int i = 0; i < 9; i++) {
		fscanf(words, "%d %s", &(ara+i)->id, gecici);
		(ara+i)->wordLength = strlen(gecici);
		(ara+i)->word = new char[(ara+i)->wordLength + 1];
		strcpy((ara + i)->word, gecici);
	}


	
	
	for (int s = 0; s < 9; s++) {

		if (horizontalSearch(puzzleArray, (ara + s)) == 1) {
			fprintf(info, "WORD%d\t%s\t[%d][%d] - [%d][%d]\n", s + 1, (ara + s)->type, (ara + s)->dikey1, (ara + s)->yatay1, (ara + s)->dikey2, (ara + s)->yatay2);
			}

		if (verticalSearch(puzzleArray, (ara + s)) == 1) {
			fprintf(info, "WORD%d\t%s\t[%d][%d] - [%d][%d]\n", s + 1, (ara + s)->type, (ara + s)->dikey1, (ara + s)->yatay1, (ara + s)->dikey2, (ara + s)->yatay2);
			}
		if (diagonalSearch(puzzleArray, (ara + s)) == 1) {
			fprintf(info, "WORD%d\t%s\t[%d][%d] - [%d][%d]\n", s + 1, (ara + s)->type, (ara + s)->dikey1, (ara + s)->yatay1, (ara + s)->dikey2, (ara + s)->yatay2);
			}
	}

	for (int s = 0; s < 9; s++) { //changing the words' places with blank in puzzleArray
		for (int x = 0; x < (ara + s)->wordLength; x++) {
			if (strcmp("HORIZONTAL", (ara + s)->type) == 0) {
				if ((ara + s)->yatay1 < (ara + s)->yatay2) {
					*(*(puzzleArrayPtr + x + (ara + s)->yatay1 - 1) + (ara + s)->dikey1 - 1) = ' ';
				}
				else {
					*(*(puzzleArrayPtr + (ara + s)->yatay1 - 1 - x) + (ara + s)->dikey1 - 1) = ' ';
				}
			}


			if (strcmp("VERTICAL", (ara + s)->type) == 0) {
				if ((ara + s)->dikey1 < (ara + s)->dikey2) {
					*(*(puzzleArrayPtr + (ara + s)->yatay1 - 1) + x + (ara + s)->dikey1 - 1) = ' ';
				}
				else {
					*(*(puzzleArrayPtr + (ara + s)->yatay1 - 1) + (ara + s)->dikey1 - 1 - x) = ' ';
				}
			}


			if (strcmp("DIAGONAL", (ara + s)->type) == 0) {
				if ((ara + s)->yatay1 < (ara + s)->yatay2 && (ara + s)->dikey1 < (ara + s)->dikey2) {
					*(*(puzzleArrayPtr + (ara + s)->yatay1 + x - 1) + (ara + s)->dikey1 + x - 1) = ' ';
				}
				if ((ara + s)->yatay1 > (ara + s)->yatay2 && (ara + s)->dikey1 < (ara + s)->dikey2) {
					*(*(puzzleArrayPtr + (ara + s)->yatay1 - 1 - x) + (ara + s)->dikey1 - 1 + x) = ' ';
				}
				if ((ara + s)->yatay1 <(ara + s)->yatay2 && (ara + s)->dikey1 >(ara + s)->dikey2) {
					*(*(puzzleArrayPtr + (ara + s)->yatay1 + x - 1) + (ara + s)->dikey1 - 1 - x) = ' ';
				}
				if ((ara + s)->yatay1 > (ara + s)->yatay2 && (ara + s)->dikey1 > (ara + s)->dikey2) {
					*(*(puzzleArrayPtr + (ara + s)->yatay1 - x - 1) + (ara + s)->dikey1 - x - 1) = ' ';
				}
				
			}
		}
	}
	

	
	for (int i = 0; i < 15; i++) { //printing puzzleArray with blanks to file
		for (int j = 0; j < 15; j++) {
			fprintf(last, "%c ", *(*(puzzleArrayPtr + j) + i));
		}
		fprintf(last, "\n");
	}



	puzzle.close();
	fclose(words);
	fclose(info);
	fclose(last);


	for (i = 0; i < 15; i++) {
		delete[] puzzleArray[i];
	}
	delete[] puzzleArray;

	for (i = 0; i < 9; i++) {
		delete[] ara[i].word;
	}

	delete[] ara;
	return 0;
}


