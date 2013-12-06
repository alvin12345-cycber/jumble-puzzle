/*
 * testJumble.cpp
 *
 *  Created on: 2013-03-29
 *      Author: rileyjshaw
 */

/*
 * A testing class for the JumblePuzzle class and its exception.
 * The code also contains a simple function that allows you to play the game, and
 * another function that you can use to display the puzzle.  You should not need to
 * alter either of these supplied functions unless you wish to enhance them without
 * changing the way JumblePuzzle operates.
 *
 */
#include <string>
#include <iostream>
#include "JumblePuzzle.h"
using namespace std;

// Displays the puzzle to the screen.
// Row and column numbers are added to the display.
void showJumble(char** jumble, const int size) {
	int i, j;
	cout << "\n  ";
	for (i = 0; i < size; i++)
		if (i < 10)
			cout << " " << i << " ";
		else
			cout << i << " ";
	cout << endl;
	for (i = 0; i < size; i++) {
		if (i < 10)
			cout << " " << i << " ";
		else
			cout << i << " ";
		for (j = 0; j < size; j++)
			cout << jumble[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
} // end showJumble

// How quickly can you find the hidden string?
void playGame() {
	srand(time(NULL) + clock());

	string toHide;
	string difficulty;
	int guessRow, guessCol;
	int start, finish;
	char guessDirection;

	cout << "Provide a string to hide in the puzzle, all lower case: ";
	cin >> toHide;
	cout << "\nChoose your difficulty level: \"easy\", \"medium\" or \"hard\": ";
	cin >> difficulty;

	JumblePuzzle* jp;
	try {
		jp = new JumblePuzzle(toHide, difficulty);
	} catch (const BadJumbleException& e) {
		cerr << e.what();
		return;
	}
	showJumble(jp->getJumble(), jp->getSize());
	start = static_cast<int>(time(NULL));
	cout << "Enter row location: ";
	cin >> guessRow;
	cout << "Enter column location: ";
	cin >> guessCol;
	cout << "Enter direction (\"n\", \"e\", \"s\" or \"w\"): ";
	cin >> guessDirection;
	finish = static_cast<int>(time(NULL));
	if (guessRow == jp->getRowPos() && guessCol == jp->getColPos() &&
			guessDirection == jp->getDirection())
		cout << "You found it!" << endl;
	else {
		cout << "Wrong location..." << endl;
		cout << "The location is row: " << jp->getRowPos() << " col: " << jp->getColPos()
				<< ", direction: " << jp->getDirection() << endl;
	}
	cout << "You took " << (finish - start) << " seconds." << endl;
	delete jp;
	jp = NULL;
} // end playGame

// Unit tests added for exception, accessors, and the possible random locations
void testJumble() {

	srand(time(NULL) + clock());

	// Test BadJumbleException
	cout << "Testing exception class:" << endl;
	try {
		JumblePuzzle test1("CMPE320", "octopus");
	} catch (const BadJumbleException& e) {
		cerr << e.what();
		int tic = clock();
		while (clock() - tic < 500) {} // keeps the error message in the right spot
		cout << "Moving on instead of quitting." << endl << endl;
	}

	// Test accessors
	cout << "Testing all accessors:" << endl;
	JumblePuzzle test2("ABCDEF", "medium");
	showJumble(test2.getJumble(), test2.getSize());
	cout << "Size should be 6 * 4: " << test2.getSize() << endl;
	cout << "The row, column and direction should match the location of the word ABCDEF." << endl << endl;
	cout << "Row number: " << test2.getRowPos() << endl;
	cout << "Column number: " << test2.getColPos() << endl;
	cout << "Direction: " << test2.getDirection() << endl;

	// Test maximum and minimum locations
	cout << "Testing the possible hidden word locations:" << endl;
	string locationTestWord = "HIDDEN";
	string locationTestDifficulty = "medium";
	JumblePuzzle test3(locationTestWord, locationTestDifficulty); // just to get the size
	int siz = test3.getSize();
	int nRowMin = siz, nRowMax = 0, nColMin = siz, nColMax = 0;
	int eRowMin = siz, eRowMax = 0, eColMin = siz, eColMax = 0;
	int sRowMin = siz, sRowMax = 0, sColMin = siz, sColMax = 0;
	int wRowMin = siz, wRowMax = 0, wColMin = siz, wColMax = 0;
	int row, col;
	int numToTest = 500;
	for (int i = 0; i < numToTest; i++) {
		JumblePuzzle test4(locationTestWord, locationTestDifficulty);
		row = test4.getRowPos();
		col = test4.getColPos();
		switch (test4.getDirection()) {
		case 'n':
			if (row < nRowMin)
				nRowMin = row;
			if (row > nRowMax)
				nRowMax = row;
			if (col < nColMin)
				nColMin = col;
			if (col > nColMax)
				nColMax = col;
			break;
		case 'e':
			if (row < eRowMin)
				eRowMin = row;
			if (row > eRowMax)
				eRowMax = row;
			if (col < eColMin)
				eColMin = col;
			if (col > eColMax)
				eColMax = col;
			break;
		case 's':
			if (row < sRowMin)
				sRowMin = row;
			if (row > sRowMax)
				sRowMax = row;
			if (col < sColMin)
				sColMin = col;
			if (col > sColMax)
				sColMax = col;
			break;
		case 'w':
			if (row < wRowMin)
				wRowMin = row;
			if (row > wRowMax)
				wRowMax = row;
			if (col < wColMin)
				wColMin = col;
			if (col > wColMax)
				wColMax = col;
			break;
		} // end switch
	} // end loop for the many puzzles
	cout << "North-facing words start between rows " << nRowMin << " and " << nRowMax << endl;
	cout << "and between columns " << nColMin << " and " << nColMax << "." << endl;
	cout <<  "East-facing words start between rows " << eRowMin << " and " << eRowMax << endl;
	cout << "and between columns " << eColMin << " and " << eColMax << "." << endl;
	cout << "South-facing words start between rows " << sRowMin << " and " << sRowMax << endl;
	cout << "and between columns " << sColMin << " and " << sColMax << "." << endl;
	cout <<  "West-facing words start between rows " << wRowMin << " and " << wRowMax << endl;
	cout << "and between columns " << wColMin << " and " << wColMax << "." << endl << endl;

	// Test copy constructor for proper operation
	cout << "Testing copy constructor:" << endl;
	// While debugging, you can use capital letters to make the hidden string easier to locate
	JumblePuzzle jp1("HELLO", "easy");
	showJumble(jp1.getJumble(), jp1.getSize());
	JumblePuzzle jp2(jp1);
	cout << "Should look the same:" << endl;
	showJumble(jp2.getJumble(), jp2.getSize());

	// Test aliasing from copy constructor
	char** puzzle = jp2.getJumble();
	int sz = jp2.getSize();
	for (int i = 0; i < sz; i++)
		puzzle[i][i] = '.';
	cout << "Dotted diagonal:" << endl;
	showJumble(puzzle, sz);
	cout << "Should be same as original 1:" << endl;
	showJumble(jp1.getJumble(), sz);
	cout << "Should be same as original 2:" << endl;
	showJumble(jp2.getJumble(), sz);

	// Test assignment operator for proper operation
	cout << "Testing assignment operator:" << endl;
	JumblePuzzle jp3("BYE", "easy");
	showJumble(jp3.getJumble(), jp3.getSize());
	JumblePuzzle jp4 = jp3;
	cout << "Should look the same:" << endl;
	showJumble(jp4.getJumble(), jp4.getSize());

	// Test aliasing from assignment operator
	puzzle = jp4.getJumble();
	sz = jp4.getSize();
	for (int i = 0; i < sz; i++)
		puzzle[i][i] = '*';
	cout << "Star diagonal:" << endl;
	showJumble(puzzle, sz);
	cout << "Should be same as original 3:" << endl;
	showJumble(jp3.getJumble(), sz);
	cout << "Should be same as original 4:" << endl;
	showJumble(jp4.getJumble(), sz);

	// Test self-assignment
	// This shows as a "bug", which it should do.  However, you should still
	// be able to build and run your program.
	jp4 = jp4;
	cout << "Should be same as original 4:" << endl;
	showJumble(jp4.getJumble(), sz);

	// Test for a memory leak.
	// I tested this with loopLimit up to 5,000,000 and found a crash when the destructor
	// was empty, and no increase in memory usage when the destructor was written as it is now.
	int loopLimit = 1000;
	for (int i = 0; i < loopLimit; i++)
		JumblePuzzle jp("HIDDENWORD", "hard");
	cout << "Passed memory leak test!" << endl;

} // end testJumble

int main() {

	testJumble();
	playGame();

	return 0;
} // end main
