/* @Author
* Student Name: Murat Calda
* Student ID : 150140107
* Date: 9.10.17
*/

#include "functions.h"

bool verticalSearch(char** puzzleArray, searchedWord* word) {
	int size = word->wordLength;
	int i = 0, j = 0, k = 0, cntrl = 0, cntrl2 = 0;
	char* tocmpr = new char[size];

	for (k = 0; k < 15; k++) {
		for (i = 0; i < 15 - size + 1; i++) {
			for (j = 0; j < size; j++) {
				*(tocmpr + j) = *(*(puzzleArray + k) + i + j);
			}

			for (int p = 0; p < size; p++) {
				if (*(tocmpr + p) == *(word->word + p))
					cntrl++;
			}
			for (int v = 0; v < size; v++) {                    //to check reverse direction
				if (*(tocmpr + size - v - 1) == *(word->word + v))
					cntrl2++;
			}
			if (cntrl == size) {
				word->type = "VERTICAL";
				word->yatay1 = k + 1;
				word->dikey1 = i + 1;
				word->yatay2 = k + 1;
				word->dikey2 = i + size;

				delete[]tocmpr;
				return 1;
			}

			if (cntrl2 == size) {
				word->type = "VERTICAL";
				word->yatay1 = 15 - k;
				word->dikey1 = 15 - i;
				word->yatay2 = 15 - k;
				word->dikey2 = 15 - k - size;
				delete[]tocmpr;
				return 1;
			}
			cntrl = 0;
			cntrl2 = 0;
		}
	}



	delete[] tocmpr;
	return 0;
}



bool horizontalSearch(char** puzzleArray, searchedWord* word) {
	int size = word->wordLength;
	int j = 0, i = 0, k = 0, cntrl = 0, cntrl2 = 0;

	char *tocmpr = new char[size];


	for (int k = 0; k < 15; k++) {
		for (i = 0; i < (15 - size + 1); i++) {
			for (j = 0; j < size; j++) {
				*(tocmpr + j) = *(*(puzzleArray + j + i) + k);

			}
			for (int p = 0; p < size; p++) {
				if (*(tocmpr + p) == *(word->word + p))
					cntrl++;
			}
			for (int v = 0; v < size; v++) {//to check reverse direction
				if (*(tocmpr + size - v - 1) == *(word->word + v))
					cntrl2++;
			}
			if (cntrl == size) {

				word->type = "HORIZONTAL";
				word->yatay1 = i + 1;
				word->dikey1 = k + 1;
				word->yatay2 = i + size;
				word->dikey2 = k + 1;

				delete[]tocmpr;
				return 1;
			}
			if (cntrl2 == size) {
				word->type = "HORIZONTAL";
				word->yatay1 = 15 - i;
				word->dikey1 = 15 - k;
				word->yatay2 = 15 - i - size;
				word->dikey2 = 15 - k;


				delete[]tocmpr;
				return 1;
			}
			cntrl = 0;
			cntrl2 = 0;
		}
	}

	delete[]tocmpr;
	return 0;
}



bool diagonalSearch(char** puzzleArray, searchedWord* word) {
	int size = word->wordLength;
	int j = 0, i = 0, k = 0, cntrl = 0, cntrl2 = 0, cntrl3 = 0, cntrl4 = 0;

	char *tocmpr = new char[size];
	char *tocmpr2 = new char[size];

	for (i = 0; i < 15 - size + 1; i++) {
		for (j = 0; j < 15 - size + 1; j++) {
			for (k = 0; k < size; k++) {
				*(tocmpr + k) = *(*(puzzleArray + i + k) + j + k); //from left to right
				*(tocmpr2 + k) = *(*(puzzleArray + 14 - i - k) + j + k); // from right to left
			}

			for (int p = 0; p < size; p++) {
				if (*(tocmpr + p) == *(word->word + p))
					cntrl++;
				if (*(tocmpr2 + p) == *(word->word + p))
					cntrl2++;
			}
			for (int v = 0; v < size; v++) {                    
				if (*(tocmpr + size - v - 1) == *(word->word + v)) //from left to right, in reverse direction
					cntrl3++;
				if (*(tocmpr2 + size - v - 1) == *(word->word + v)) //from right to left, in reverse direction
					cntrl4++;
			}


			if (cntrl == size) {
				word->type = "DIAGONAL";
				word->yatay1 = i + 1;
				word->dikey1 = j + 1;
				word->yatay2 = i + size;
				word->dikey2 = j + size;

				delete[]tocmpr2;
				delete[]tocmpr;
				return 1;
			}
			if (cntrl2 == size) {
				word->type = "DIAGONAL";
				word->yatay1 = 15 - i;
				word->dikey1 = j + 1;
				word->yatay2 = 15 - size - i + 1;
				word->dikey2 = j + size;

				delete[]tocmpr;
				delete[]tocmpr2;
				return 1;
			}
			if (cntrl3 == size) {
				word->type = "DIAGONAL";
				word->yatay1 = size - i;
				word->dikey1 = size - j;
				word->yatay2 = i + 1;
				word->dikey2 = j + 1;

				delete[]tocmpr;
				delete[]tocmpr2;
				return 1;
			}
			if (cntrl4 == size) {
				word->type = "DIAGONAL";
				word->yatay1 = 15 - i - size + 1;
				word->dikey1 = j + size;
				word->yatay2 = 15 - i;
				word->dikey2 = j + 1;

				delete[]tocmpr;
				delete[]tocmpr2;
				return 1;
			}

			cntrl = 0;
			cntrl2 = 0;
			cntrl3 = 0;
			cntrl4 = 0;
		}
	}

	delete[] tocmpr;
	delete[]tocmpr2;

	return 0;
}