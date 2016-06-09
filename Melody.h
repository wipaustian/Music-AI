/*
The Melody class is the class that holds most of the artificial intelligence functions
along with the print functions for the melody and bass


*/

#ifndef MELODY_H
#define MELODY_H
#include "Note.h"
#include "Composer.h"
#include <vector>
#include <deque>

using namespace std;

class Melody
{
	public:
		bool goodRhythm(vector<char> temp, int top, int bottom);
		
		char addPassingNote(char note);
		char getTonicNote();
		
		int scoreTonicNote(vector <char> a, Note &n);
		int scoreNumberOfNotesInScale(vector <char> a, Composer &c, Note &n);
		int findNumberOfSteps(vector <char> a);
		
		string charToNote(int num, Note &n);
		
		vector<char> divideNotes(vector<char> score, int top, int bottom);
		vector<char> developConsonantNotes(char note);
		vector<char> chooseBestMelody(deque <Melody> possibleMelodies);
		vector<char> developMelody(vector<char> rightHand, vector<char> leftHand, Note &n, Composer &c);
		vector<char> developMelodyWithChords(vector<char> rightHand, vector<char> leftHand, Note &n, Composer &c);
		
		void print(vector<char> leftHand, Note &n, string fileName);
		void printChords(vector<char> leftHand, Composer &c, Note &n, string fileName);
		void regularPrint(vector<char> e, string fileName);
		void printMelody(vector<char> e, string fileName, int score, Note &n);
		void setTonicNote(char t);
		
		vector<char> measure;
		deque <Melody> possibleMelodies;
	protected:
		int points;
};

#endif
