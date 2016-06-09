/*
Note class.
Details holds information for the notes in the score
*/

#ifndef NOTE_H
#define NOTE_H
#include <vector>
#include <iostream>
#include <utility>  //pair 

using namespace std;

class Note
{
	public:
	
		string getTonicNote();
		char getQuarterNoteChar();
		char getWholeNoteChar();
		char getHalfNoteChar();
		char getEighthNoteChar();
		
		double getQuarterNoteValue();
		double getWholeNoteValue();
		double getHalfNoteValue();
		double getEighthNoteValue();
		
		void setQuarterNoteValue(double n);
		void setWholeNoteValue(double n);
		void setHalfNoteValue(double n);
		void setEighthNoteValue(double n);
		void setValues(int bottomNote);
		void addAllNotes();
		void setTonicNote(string t);
	
		vector<string> allNotes;
		
	protected:
		pair<char,double> wholeNote; //pair denotes the whole note
		pair<char,double> halfNote;//pair denotes the half note
		pair<char,double> quarterNote;//pair denotes the quarter note
		pair<char,double> eighthNote;//pair denotes the eighth note
		string tonic;
		
};

#endif

