#include "Composer.h"
#include "Note.h"
#include "Melody.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

class Melody m2;

using namespace std;

/*
Input: void
Output: number of measures
Returns the number of measures
*/
int Composer::getNumOfMeasures(){
	return measureNum;
}

/*
Input: m - the number of measures given by the user or computer
Output: tempo
Returns the tempo number
*/
void Composer::setNumOfMeasures(int m){
	measureNum = m;
}

/*
Input: void
Output: tempo
Returns the tempo number
*/
int Composer::getTempo(){
	return tempo;
}
/*
Input: tempo
Output: void
Sets the tempo number
*/
void Composer::setTempo(int t){
	tempo=t;
}

/*
Input: Nothing
Output: key signature
Returns the key signature
*/

string Composer::getKeySignature(){
	return keySig;
}


void Composer::setTime(int top, int bottom){
	topNumber=top;
	bottomNumber=bottom;
}
/*
Input: void
Output: bottomNumber
Grabs the bottom number in the time signature
This refers to what will get the beat

4 - quarter note
2 - half note
8 - eighth note
*/
int Composer::getBottom(){
	return bottomNumber;
}
/*
Input: void
Output: topNumber
Grabs the top number in the time signature

This refers to how many beats there are in a measure
*/
int Composer::getTop(){
	return topNumber;
}

/*
Input: s - key signature
Output: void
Sets the key signature
*/
void Composer::setKeySignature(string s){
	keySig=s;
}
/*
Input: chords - a vector of size 3 which holds the notes needed to create a major or minor chord.
num - the number on the scale which helps to determine if the chord need to be major, minor or
diminished.  

Builds chords depending on where the notes are on the scale.

On a scale, you build a major chord on the first, fourth, fifth and and eighth notes.
On the second, third, and sixth notes you can build a minor chord.  On the seventh note, you can 
build a diminshed chord. A major chord is developed by adding a note which is a major third away,
or in the case of numbers adding 4 to the previous number (0 + 4 = 4, C turns into an E). 
and then adding a minor third on top of that, or adding 3 to the next number.  A minor chord is the 
reverse of that: minor third and then a major third.  A diminshed is just two minor thirds on top 
of each other.  

Ex:
Major Chord:
Music Notation:		Midi format:
	G					7
	E					4
	C 					0
	
C Minor Chord:
Music Notation:		Midi format:
	G					7
	Eb					3
	C 					0

C Diminshed Chord:	
Music Notation:		Midi format:
	Gb					6
	Eb					3
	C 					0

*/

vector<char> Composer::buildMajorChords(vector<char> chords, int num){
	int chord;
	
	if(num==0 || num==3 || num==4 || num==7){ //the first, fourth, fifth and last notes in the scale are made into major chords
		chord = chords[0];
		chord+=4;  //makes a note two whole steps (+4) above the bottom note
		chords.push_back(chord);
		chord = chords[1];
		chord+=3;//makes a note two a step and a half (+3) above the bottom note
		chords.push_back(chord);
	}
	else if(num==1 || num==2 || num==5){  //the second, third, and sixth in the scale are made into major chords
		chord = chords[0];
		chord+=3;  //step and a half
		chords.push_back(chord);
		chord = chords[1];
		chord+=4;
		chords.push_back(chord);
	}
	else if(num==6){ //the seventh note is made into a diminshed chord
		chord = chords[0];
		chord+=3;  //step and a half
		chords.push_back(chord);
		chord = chords[1];
		chord+=3;
		chords.push_back(chord);
	}

	return chords;
}

/*
Input: chords - a vector of size 3 which holds the notes needed to create a major or minor chord. 

Creates a first inversion of the previous chord it created

A chord is inverted when a note other than the root is acting as the bass note.  
The third above the root note (C in the bottom example) and the third above that third 
(E in the example) both get moved down an octave.  To change a note to an octave below in MIDI,
you need to subtract 12 away from it.  

Ex:
C Major Chord:
Music Notation:		Midi format:
	G					7
	E					4
	C 					0

C Major Chord first inversion:
Music Notation:		Midi format:

	C 					0
	G				   -5
	E				   -8

*/

vector<char> Composer::firstInversion(vector<char> chords){
	vector<char> newChords;
	int chord = 0;
	chord = chords[1]-12;  //makes these notes an actave below where they originally were
	newChords.push_back(chord);
	chord = chords[2]-12;
	newChords.push_back(chord);
	newChords.push_back(chords[0]);  //keeps the root note where it was
	return newChords;
}

/*
Input: chords - a vector of size 3 which holds the notes needed to create a major or minor chord. 

Creates a first inversion of the previous chord it created

A chord is inverted when a note other than the root is acting as the bass note. 
Second inversion is where the top note a the original chord in now the bottom or an octave below
where it was originally.  An octave is when two pitches sound similar but one is lower and the higher  

Ex:
C Major Chord:
Music Notation:		Midi format:
	G					7
	E					4
	C 					0

C Major Chord second inversion:
Music Notation:		Midi format:
	
	E					4
	C 					0
	G				   -5

*/

vector<char> Composer::secondInversion(vector<char> chords){
	vector<char> newChords;
	int chord = 0;
	chord = chords[2]-12;  //subtracting 12 makes the note an octave below/ a lower pitch.
	newChords.push_back(chord);
	newChords.push_back(chords[0]); //adds the rest of the notes at their original place 
	newChords.push_back(chords[1]);
	
	return newChords;
}

/*
Input: void
output: void

Develops all of the regular, first and second inverted chords for use in the song.

*/

void Composer::developChords(Note &n){

	for(int i=0;i<notesInKey.size()-1;i++){
		vector<char> regChords;  //non inverted chords: Major, minor and diminished
		vector<char> firstInver;  //chords in first inversion
		vector<char> secondInver; //chords in second inversion
		
		regChords.push_back(notesInKey[i]);  //creates the major, minor and diminished chords from the scale
		regChords=buildMajorChords(regChords, i);
		possibleChords.push_back(regChords);
		
		firstInver=firstInversion(regChords);  //creates the first inversion of each of the first chords made
		possibleChords.push_back(firstInver);
		
		secondInver=secondInversion(regChords); //creates the first inversion of each of the first chords made
		possibleChords.push_back(secondInver);
	}
}

/*
Input: void
output: void

Sets the chords needed in the left hand of the piano/accompaniment to melody.

SInce this is trying to make tonic music, then the first and last measures need to include the tonic
major chord:

C major key:
	G
	E
	C

This is why it chooses the first member of the chord vector for the first and last measures.
Everything else is chosen at random since they are all within a human player's range.

When the chord is chosen, since I would like the chord to take up the entire measure, then I fill up the
rest of the measure with 99's in order to make the chord last the entire time.

*/

void Composer::setChordsInBass(Note &n){
	srand (time(NULL));
	int chooseChord;
	char chord;
	char x = 99;
	
	for(int i=0;i<getNumOfMeasures();i++){
		double amount = getTop();  //top number/amount of beats per measure
		
		if(i==0 || i==(getNumOfMeasures()-1))  //the first and last measures get the tonic chord (or the chord with the tonic note)
			chooseChord = 0;
		else
			chooseChord = rand() % possibleChords.size() + 0;  //chooses random chord since all chords are easy to play and are close together
			
		leftHand.push_back(chooseChord);
		
		//begins the process
		if(n.getWholeNoteValue()<=amount){  //since the chord takes up the whole measure then we need to put
			amount=amount-n.getWholeNoteValue();//in enough x's to fill up the measure
			for(int i=0;i<15;i++)
				leftHand.push_back(x);
		}
		else if(n.getHalfNoteValue()<=amount){
			amount=amount-n.getHalfNoteValue();  //subtracts amount from the amount in the measure
			for(int i=0;i<7;i++)
				leftHand.push_back(x);
		}	
		else if(n.getQuarterNoteValue()<=amount){
			amount=amount-n.getQuarterNoteValue();
			for(int i=0;i<3;i++)
				leftHand.push_back(x);
		}
		else if(n.getEighthNoteValue()<=amount){
			amount=amount-n.getEighthNoteValue();
			leftHand.push_back(x);
		}

		while(amount!=0){ 
			if(n.getWholeNoteValue()<=amount){
				amount=amount-n.getWholeNoteValue();
				for(int i=0;i<16;i++)
					leftHand.push_back(x);
			}
			else if(n.getHalfNoteValue()<=amount){
				amount=amount-n.getHalfNoteValue();
				for(int i=0;i<8;i++)
					leftHand.push_back(x);
			}
			else if(n.getQuarterNoteValue()<=amount){
				amount=amount-n.getQuarterNoteValue();
				for(int i=0;i<4;i++)
					leftHand.push_back(x);
			}
			else if(n.getEighthNoteValue()<=amount){
				amount=amount-n.getEighthNoteValue();
				for(int i=0;i<2;i++)
					leftHand.push_back(x);
			}
		}
	}	
}
/*
Input: void
output: void

Walking bass is another type of bass inplemented mostly in jazz tunes, however this will implement a
new style of it where the bass will play the the note designated the beat to give it a good feeling.
For example in 4/4 time, the bass will play four quarter notes
In 2/2 time, the bass will play two half notes.

Walking bass originally was just four 4/4 time but this will design a different time of walking bass
for all time signatures.

Example: 4/4

[Q  Q  Q  Q]

*/

void Composer::setWalkingBass(Note &n){
	char note;
	
	for(int i=0;i<getNumOfMeasures()+1;i++){
		for(int j=0;j<getTop();j++){  //adds it as many times as the top number is
			if(getBottom()==4)
				score2.push_back(n.getQuarterNoteChar());  //adds the beat in 4
			if(getBottom()==8)
				score2.push_back(n.getEighthNoteChar());  //adds the beat in 8
			if(getBottom()==2)
				score2.push_back(n.getHalfNoteChar());	//adds the beat in 2		
		}
	}		
}

/*
Input: takes in the current object of the class Note
Output: void
Takes the top and bottom number to create the rhythm.
Looks at the amount it has left in the measure and checks to see which notes 
it can put in.  When it finds those notes then it will randomnly pick one, if the 
vector's size is greater than 1. It subtracts the amount that the note has from 
the amount left in the measure and does it again.  

*/
void Composer::developRhythm(Note &n){
	double amountInMeasure=getTop();
	char note;
	vector <char> possibleRhythm;
	srand (time(NULL));
	int num=getNumOfMeasures(); //refers to number of measures
	while(num!=-1){
		vector <char> temp;
		while(amountInMeasure!=0){
			
			if(n.getWholeNoteValue()<=amountInMeasure)  //if any of these notes can fit in the amount of space
				possibleRhythm.push_back(n.getWholeNoteChar()); //then they get pushed in
			if(n.getHalfNoteValue()<=amountInMeasure)
				possibleRhythm.push_back(n.getHalfNoteChar());
			if(n.getQuarterNoteValue()<=amountInMeasure)
				possibleRhythm.push_back(n.getQuarterNoteChar());
			if(n.getEighthNoteValue()<=amountInMeasure)
				possibleRhythm.push_back(n.getEighthNoteChar());
			
			if(possibleRhythm.size()==1)
				note = possibleRhythm[0]; 
			else if(possibleRhythm.size()>1){
				int choose = rand() % possibleRhythm.size() + 0;
				note = possibleRhythm[choose];
			}
			
			if(note=='W')
				amountInMeasure=amountInMeasure-n.getWholeNoteValue();  //subtracts the note value from the amount that is in the measure
			else if(note=='H')
				amountInMeasure=amountInMeasure-n.getHalfNoteValue();
			else if(note=='Q')
				amountInMeasure=amountInMeasure-n.getQuarterNoteValue();
			else if(note=='E')
				amountInMeasure=amountInMeasure-n.getEighthNoteValue();
			
			temp.push_back(note);
			
			possibleRhythm.clear();  //clears the rhythms so there is nothing extra
		}
		
		ofstream file;
  		file.open ("rhythm evolution.txt", std::ios_base::app);
  		file<<"Evolution:"<<endl;
		
		m2.regularPrint(temp,"rhythm evolution.txt");  //prints out the evoltuion of the rhythms
		bool b = m2.goodRhythm(temp,getTop(),getBottom()); //checks to see if the rhythm created is good
		
		if(b==false)  //if it is not good enough then the rhythm gets divided
			temp = m2.divideNotes(temp,getTop(),getBottom()); 
		
		for(int i=0;i<temp.size();i++)
			score.push_back(temp[i]);
			
		num--;
		amountInMeasure=getTop();
	}
}

/*
Input: void
output: void

Develops a ostinato bass for the enitre piece to use.
Ostinato is a rhythm that persistently repeats in the same musical voice, usually at the same pitch
(using the same notes).
This function will develop the bass by finding notes that it can use at the time and then deciding
randomly if there are two or more different notes that it can use.  Then it pushes it back so the bass
is use constantly and does not change.

*/

vector <char> Composer::setOstinatoBass(Note &n){
	double amountInMeasure=getTop();
	char note;	
	vector <char> possibleRhythm;
	srand (time(NULL));
	while(amountInMeasure!=0){	//does the same algorithm as creating the melody
		if(n.getHalfNoteValue()<=amountInMeasure)
			possibleRhythm.push_back(n.getHalfNoteChar());
		if(n.getQuarterNoteValue()<=amountInMeasure)
			possibleRhythm.push_back(n.getQuarterNoteChar());
		if(n.getEighthNoteValue()<=amountInMeasure)
			possibleRhythm.push_back(n.getEighthNoteChar());
			
		if(possibleRhythm.size()==1)
			note = possibleRhythm[0];   //only one note means it chooses that note
		else if(possibleRhythm.size()>1){
			int choose = rand() % possibleRhythm.size() + 0;  //more than one then it chooses randomly
			note = possibleRhythm[choose];
		}
			
		if(note=='H')
			amountInMeasure=amountInMeasure-n.getHalfNoteValue();
		else if(note=='Q')
			amountInMeasure=amountInMeasure-n.getQuarterNoteValue();
		else if(note=='E')
			amountInMeasure=amountInMeasure-n.getEighthNoteValue();
			
		score.push_back(note);
		possibleRhythm.clear();
	}
	for(int i=0;i<getNumOfMeasures();i++){  //since the bass is being repeated through the song, it gets pushed
		for(int j=0;j<score.size();j++){  //throughout the length of the song
			score2.push_back(score[j]);
		}
	
	}
	score.clear();
	return score2;
}

/*
Input: void
Output: void
Creates a vector of all possible key signatures for later use
*/

void Composer::addNotesToVector(){
	possibleKeys.push_back("C");
	possibleKeys.push_back("Db");
	possibleKeys.push_back("D");
	possibleKeys.push_back("Eb");
	possibleKeys.push_back("E");
	possibleKeys.push_back("F");
	possibleKeys.push_back("Gb");
	possibleKeys.push_back("G");
	possibleKeys.push_back("Ab");
	possibleKeys.push_back("A");
	possibleKeys.push_back("Bb");
	possibleKeys.push_back("B");
}
/*
Input: keySig
Output: void
Finds the key signature in the vector. Since its place in the vector correlates with
its value in the midi code then it will set the first note in the key as that.
It creates the key signature by adding two, except at the fourth and eighth note
where it is just one; This is similar to how in music theory we go up whole steps (add 2)
until the fourth and eighth where we go a half step (add 1)
*/
void Composer::developKey(string keySig){
	int temp=0;
	int count=0;

	for(int i=0;i<possibleKeys.size();i++){
		if(keySig==possibleKeys[i])
			temp=i;  //finds the space of the vector that holds the key and takes that space number
			//this corresponds to the midi number of the key name 
			//C is in the 0th space and is '0' in midi form
	}
	
	while(count!=8){
		
		notesInKey.push_back(temp);
		if(count==2 || count==6)  //the third and seventh note are added up a half step (+1)
			temp++;
		else
			temp+=2;  //the rest are added up a whole step (+2)
			
		count++;
	}	
}
/*
Input: leftHand - the current score for the left hand
Output: void
Runs through the vector and if a characrer other than 'x' is found then we replace it 
with a random number.  '0' is adding to change the integer into a character
*/
vector <char> Composer::addNotes(vector <char> s){
	
	srand (time(NULL));
	for(int i=0;i<s.size();i++){
		if(s[i]!=99 && s[i]!='M'){
			int note = rand() % 9 + 0;
			s[i]=note;
		}	
	}
	return s;
}
/*
Input: score - the current score for the left hand
Output: void
Reads through the score and pushes its content into the leftHand vector
After it reads a character it will push back the necessary amount of x's to give 
the feeling of its actual space in the score.  

Before: (Q refers to quarter note, E refers to eighth note, M refers to the end of the measure
Q, Q, E, E, M, H, Q, M

After:
1, x, x, 3, x, x, 3, x, 5, x, 7, x, x, x, x, 8, x, x
*/
vector<char> Composer::convertToReadableScore(vector <char> score){
	char x = 99;
	vector<char> completeScore;
	for(int i=0;i<score.size();i++){
		if(score[i]=='Q'){
			completeScore.push_back(score[i]);
			for(int i=0;i<3;i++)
				completeScore.push_back(x);
		}
		else if(score[i]=='H'){
			completeScore.push_back(score[i]);
			for(int i=0;i<7;i++)
				completeScore.push_back(x);
		}
		else if(score[i]=='W'){
			completeScore.push_back(score[i]);
			for(int i=0;i<15;i++)  //a whole note is double the length of a half note so it gets almost double the x's
				completeScore.push_back(x);
		}
		else if(score[i]=='E'){ 
			completeScore.push_back(score[i]);
			completeScore.push_back(x);  //the one x represents how short an eighth note is in comparison to others
		}	
	}
	return completeScore;
}

