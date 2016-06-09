/*
The .h file for a part of the artificial intelligence and the 
functions that contain the basic needs for a piece of music
*/

#ifndef COMPOSER_H
#define COMPOSER_H
#include "Note.h"
#include <iostream>
#include <vector>

using namespace std;

class Composer
{
	public:
		string getKeySignature();
		
		int getBottom();
		int getTop();
		int getNumOfMeasures();
		int getTempo();
		
		void developRhythm(Note &n);
		void setTempo(int t);
		void setKeySignature(string s);
		void setTime(int top, int bottom);
		void developKey(string keySig);
		void setNumOfMeasures(int measureNum);
		void developChords(Note &n);
		void setChordsInBass(Note &n);
		void setWalkingBass(Note &n);
		void addNotesToVector();
		
		vector <char> setCurrent(vector <double> temp, Note &n);
		vector<char> buildMajorChords(vector<char> chords, int num);
		vector<char> firstInversion(vector<char> chords);
		vector<char> secondInversion(vector<char> chords);
		vector<int> getInstruments();
		vector <char> setOstinatoBass(Note &n);
		vector<char> convertToReadableScore(vector <char> score);
		vector <char>  addNotes(vector <char> s);
		
		vector<int> notesInKey;
		vector<string> possibleKeys;
		vector<char> score;
		vector<char> score2;
		vector<char> leftHand;
		vector<char> rightHand;
		vector< vector<char> > possibleChords;
		
	protected:
		int tempo;  //tempo variable
		int topNumber; //top number of the time signature/number of beat in each measure
		int bottomNumber;//bottom number of the time signature/note that gets one beat
		int measureNum;
		string keySig; //key signature
};

#endif

