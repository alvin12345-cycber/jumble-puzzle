/*
 * JumblePuzzle.cpp
 *
 *  Created on: 2013-03-29
 *      Author: rileyjshaw
 */

#include "JumblePuzzle.h"

using namespace std;

BadJumbleException::BadJumbleException(const string& msg) {
	 message = msg + '\n';
}

string BadJumbleException::what() const {
	return message;
}

JumblePuzzle::JumblePuzzle() {
	jumble = NULL;
	size = 0;
	row = 0;
	col = 0;
	direction = 0;
}

JumblePuzzle::JumblePuzzle(const string& hiddenWord, const string& difficulty) {
	int dir = rand() % 4;
	int south_inc, east_inc;
	string directions = "nesw";
	int south_incs[4] = {-1, 0, 1, 0};
	int east_incs[4] = {0, 1, 0, -1};
	direction = directions[dir];
	south_inc = south_incs[dir];
	east_inc = east_incs[dir];
	int wordLen = hiddenWord.length();
	if (wordLen < 3 || wordLen > 10) {
        throw BadJumbleException("Word is too short. Should be between 3 and 10 letters long.");
	}
	if (difficulty == "easy") {
		size = 2 * wordLen;
	} else if (difficulty == "medium") {
		size = 3 * wordLen;
	} else if (difficulty == "hard") {
		size = 4 * wordLen;
	} else {
		throw BadJumbleException("Invalid difficulty \"" + difficulty + "\".\nDifficulty must be \"easy\", \"medium\", or \"hard\", without quotes and in lower case.");
	}
	// Pick a spot where the word is sure to fit, based on which way it's going
	row = rand() % (size - (south_inc ? wordLen - 1 : 0)) + (south_inc == -1 ? wordLen - 1 : 0);
	col = rand() % (size - ( east_inc ? wordLen - 1 : 0)) + ( east_inc == -1 ? wordLen - 1 : 0);

	int i, j;

	jumble = new char*[size];

	for (i=0; i<size; i++)
		jumble[i] = new char[size];
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++) {
			jumble[i][j] = rand() % 26 + 'a';
		}
	}

	i = row;
	j = col;
	int count;
	for (count = 0; count < wordLen; count++) {
		jumble[i][j] = hiddenWord[count];
		i += south_inc;
		j += east_inc;
	}
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& orig) {
	int i, j;
	direction = orig.getDirection();
	size = orig.getSize();
	row = orig.getRowPos();
	col = orig.getColPos();
	if (orig.getJumble()) {
		jumble = new char*[size];
		for (i=0; i<size; i++)
			jumble[i] = new char[size];
		for (i=0; i<size; i++) {
			for (j=0; j<size; j++) {
				jumble[i][j] = orig.getJumble()[i][j];
			}
		}
	}
}

JumblePuzzle::~JumblePuzzle() {
	int i;
	for (i=size-1; i>=0; i--) {
		delete[] jumble[i];
		jumble[i] = NULL;
	}
	delete[] jumble;
	jumble = NULL;
}


JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& right) {
	if (this != &right) {
		int i, j;
		for (i=size-1; i>=0; i--) {
			delete[] jumble[i];
		}
		delete[] jumble;

		direction = right.getDirection();
		size = right.getSize();
		row = right.getRowPos();
		col = right.getColPos();
		if (right.getJumble()) {
			jumble = new char*[size];
			for (i=0; i<size; i++)
				jumble[i] = new char[size];
			for (i=0; i<size; i++) {
				for (j=0; j<size; j++) {
					jumble[i][j] = right.getJumble()[i][j];
				}
			}
		}
	}
	return *this;
}

char** JumblePuzzle::getJumble() const {
	int i, j;
	char** replicatedJumble = new char*[size];
	for (i=0; i<size; i++)
		replicatedJumble[i] = new char[size];
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++) {
			replicatedJumble[i][j] = jumble[i][j];
		}
	}
	return replicatedJumble;
}

int JumblePuzzle::getSize() const {
	return size;
}

int JumblePuzzle::getRowPos() const {
	return row;
}

int JumblePuzzle::getColPos() const {
	return col;
}

char JumblePuzzle::getDirection() const {
	return direction;
}
