#include "Note.h"
#include <iostream>

using namespace std;


/*
Input: void
Output: void
Creates a vector of all possible key signatures for later use
*/

void Note::addAllNotes(){
	allNotes.clear();
	allNotes.push_back("C");
	allNotes.push_back("Db");
	allNotes.push_back("D");
	allNotes.push_back("Eb");
	allNotes.push_back("E");
	allNotes.push_back("F");
	allNotes.push_back("Gb");
	allNotes.push_back("G");
	allNotes.push_back("Ab");
	allNotes.push_back("A");
	allNotes.push_back("Bb");
	allNotes.push_back("B");
	
}
/*
Input: t - the tonic note
Output: void

Takes in the tonic note for use in a scoring system.

The tonic note is the tonal center of a piece of music in a specific key.
For example in the key of C the tonic note is C.

*/

void Note::setTonicNote(string t){
	tonic=t;
}

/*
Input: void
Output: tonic = the tonic note

Returns the tonic note for use in a scoring system.

*/

string Note::getTonicNote(){
	return tonic;
}


/*
Input: bottomNote
Output: void
Depending on what note gets the beat, the computer will set up specific values 
for each note type.

No matter what time it is in, the whole note will always be two times greater than
the half note, four times greater than the quarter note annd eight times greater than the eighth note

*/
void Note::setValues(int bottomNote){
	if(bottomNote==2){
		setWholeNoteValue(2);  //whole note is always double the half note, so it gets 2
		setHalfNoteValue(1); //a half note is the beat so its value is 1
		setQuarterNoteValue(0.5);
		setEighthNoteValue(0.25);
	}
	if(bottomNote==4){
		setWholeNoteValue(4);
		setHalfNoteValue(2);
		setQuarterNoteValue(1);  //a quarter note is the beat so its value is 1
		setEighthNoteValue(0.5);
	}
	if(bottomNote==8){
		setWholeNoteValue(8);
		setHalfNoteValue(4);
		setQuarterNoteValue(2);
		setEighthNoteValue(1); //an eighth note is the beat so its value is 1
	}
}

/*
Input: n
Output: void
Makes a pair of char and a double for the quarter note

*/
void Note::setQuarterNoteValue(double n){
	 quarterNote = make_pair ('Q',n);
}
/*
Input: n
Output: void
Makes a pair of char and a double for the whole note

*/
void Note::setWholeNoteValue(double n){
	wholeNote= make_pair ('W',n);
}
/*
Input: n
Output: void
Makes a pair of char and a double for the half note

*/
void Note::setHalfNoteValue(double n){
	halfNote=make_pair ('H',n);
}
/*
Input: n
Output: void
Makes a pair of char and a double for the eighth note

*/
void Note::setEighthNoteValue(double n){
	eighthNote=make_pair ('E',n);
}
/*
Input: 
Output: the second half of the pair
The next four functions return the second half of the note pair when needed

*/
double Note::getQuarterNoteValue(){
	return quarterNote.second;
}

double Note::getWholeNoteValue(){
	return wholeNote.second;
}

double Note::getHalfNoteValue(){
	return halfNote.second;
}

double Note::getEighthNoteValue(){
	return eighthNote.second;
}
/*
Input: void
Output: the first half of the pair
The next four functions eturn the first half of the note pair when needed.

*/
char Note::getQuarterNoteChar(){
	return quarterNote.first;
}

char Note::getWholeNoteChar(){
	return wholeNote.first;
}

char Note::getHalfNoteChar(){
	return halfNote.first;
}

char Note::getEighthNoteChar(){
	return eighthNote.first;
}

