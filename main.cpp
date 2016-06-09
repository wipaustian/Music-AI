#include "Composer.h"
#include "MIDI.h"
#include "MIDItrack.h"
#include "MIDIfile.h"
#include "Note.h"
#include "Melody.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <math.h>
#include <string>

using namespace std;

class MIDItrack t;
class MIDIfile f;
class Composer c;
class Note n;
class MIDI m;
class Melody m1;

/*
Input: choice - if it is a human inputting the number or the computer
Output: void
Prompts the user for the tempo

Tempo is the speed or pace of a given piece of music.
In the case of the program the tempo is delivered to the delay function which will slow down the
sound by a given number of miliseconds.  Therefore the amount typed will need to be reversed. A
tempo of 100 will generally be a slow tempo and 200 would be fast but in this program it will be reversed
where 100 is fast and 200 is slow which mimics how much the sounds will be delayed by.
*/
void promptTempo(int choice){
	srand (time(NULL));
	int tempo;
	if(choice==1){
		cout<<"What tempo/how much delay? (The lower the number the faster it is)"<<endl;
		cin>>tempo;
		c.setTempo(tempo);
	}
	else{
		tempo = rand() % 100 + 100;  //between 100 and 200
		cout<<"The tempo/delay is at "<<tempo<<endl;
		c.setTempo(tempo);
	}
}
/*
Input: choice - if it is a human inputting the number or the computer
Output: void
Prompts the user for the key that they would like the piece to be in.
This will be used to devlop the key signature later in the program.

The key of a piece of music is the note that the scale you're using starts on, known as the tonic.
Typically it's the note you come back to throughout the tune and especially at the end.

*/
void promptKey(int choice){
	srand (time(NULL));
	string key;

	if(choice==1){
		cout<<"What major key?"<<endl;
		cin>>key;
		c.setKeySignature(key);
	}
	else{
		int keyNum = rand() % (c.possibleKeys.size()) + 0;  //selects from the generated keys in the Composer class
		cout<<"The key is in "<<c.possibleKeys[keyNum]<<endl;
		c.setKeySignature(c.possibleKeys[keyNum]);
	}
}

/*
Input: choice - if it is a human inputting the number or the computer
Output: instruments - the vector which holds the instruments that will be used.
The melody will be in the 0th space and the bass will be in the 1st space of the vector.

If the user is choosing everything then the computer will prompt the user for the instruments
using their MIDI numbers.  Availiable here: http://www.ccarh.org/courses/253/handout/gminstruments/
If the computer is choosing then it will automatically choose the piano since generating it randomnly
will create messy music.
*/

vector<char> promptInstruments(int choice){
	int piano = 0;
	int ins = 0;
	vector<char> instruments;
	if(choice==1){
		cout<<"Would you like the piano (0) or different instruments (1)?"<<endl;
		cin>>piano;
	}
	else
		piano=0;  //the midi number of the piano is 0

	if(piano==0){
		instruments.push_back(0);
	}
	else{
		cout<<"What instrument would you like for the melody?"<<endl;
		cin>>ins;
		instruments.push_back(ins);  //pushes back the melody midi
		cout<<"What instrument would you like for the bass?"<<endl;
		cin>>ins;
		instruments.push_back(ins); //pushes back the bass midi
	}

	return instruments;

}

/*
Input: choice - if it is a human inputting the number or the computer
Output: void
Prompts the user for the file name

If the computer inputs information then it concatenates all the information into one string
*/
void promptFileName(int choice){

	string name;
	if(choice==1){
		cout<<"What would you like to call it?"<<endl;
		getline(cin,name);
		f.setFilename(name);
	}
	else{
		name = c.getKeySignature()+";"+to_string(c.getNumOfMeasures())+";"+to_string(c.getTempo())+
		";"+to_string(c.getTop())+";"+to_string(c.getBottom());  //adds together all of the numbers and key signature to create a file name

		cout<<"The file is called "<<name<<endl;
		f.setFilename(name);
	}
}
/*
Input: choice - if it is a human inputting the number or the computer
Output: void
Prompts the user for the time signature

The time signature specify how many beats (pulses) are to be contained in
each bar and which note value is to be given one beat. If the bottom number is
a 2 then that corresponds to a half note getting one beat in a measure.  If it's a
4 then it will mean that the quarter note will get one beat and an 8 means an eighth
note will get a beat.  The top number corresponds to how many beats there are per measure.

If the song is in 4/4 time then the following are true:
- There are 4 beats in each measure
- A quarter note gets one beat in a measure
- An eighth note would then get 1/2 a beat
- A half note would get two beats
- A whole note would get four beats
- There can be four quarter notes in each measure,
   - Or two half notes in each measure
   - Or one whole note in each measure
   - Or eight eighth notes in each measure

*/
void promptTimeSignature(int choice){
	int top;
	int bottom;
	srand (time(NULL));
	if(choice==1){
		cout<<"What should get the beat?(2,4,8)"<<endl;
		cin>>bottom;

		while(bottom!=2 && bottom!=4 && bottom!=8){  //if the person writes a different number
			cout<<"Not valid. Try again!"<<endl; //then it asks them again
			cin>>bottom;
		}
		cout<<"How many beats per measure?"<<endl;
		cin>>top;

		c.setTime(top,bottom);
	}
	else{
		top = rand() % 6 + 2; //random number between 8 and 2
		bottom = rand() % 3 + 1;
		bottom = pow(2,bottom);
		cout<<"The piece is in "<<top<<"/"<<bottom<<" time."<<endl;
		c.setTime(top,bottom);
	}
}

/*
Input: choice - if it is a human inputting the number or the computer
Output: void
Prompts the user for the amount of measures and then sets the value.

A measure is a segment of time corresponding to a specific number
of beats in which each beat is represented by a particular note value and
the boundaries of the bar are indicated by vertical bar lines.


*/
void promptNumOfMesures(int choice){
	srand (time(NULL));
	int measures;
	if(choice==1){
		cout<<"How many measures"<<endl;
		cin>>measures;
		c.setNumOfMeasures(measures);
	}
	else{
		measures = rand() % 40 + 10;  //between 10 and 50
		cout<<"The piece has "<<measures<< " measures."<<endl;
		c.setNumOfMeasures(measures);
	}
}

int main()
{

	int choice = 0;  //holds whether the human or the computer will choose the information
	vector<char> ins;
	vector<int> keys_on;
	vector<char> instruments;  //holds the type of instruments
	MIDIfile file;
   	const char x = 99; //no note

	c.addNotesToVector();
	srand (time(NULL));
	cout<<"Do you want to input the information (1) or should the computer (2)?"<<endl;
	cin>>choice;

	ins = promptInstruments(choice);
	promptTempo(choice);
	promptKey(choice);
	c.developKey(c.getKeySignature());
	n.setTonicNote(c.getKeySignature());
	promptTimeSignature(choice);
	promptNumOfMesures(choice);
	n.setValues(c.getBottom());
	cin.ignore();
	promptFileName(choice);

	int chooseBass = rand() % 3 + 0;  //randomly chooses a type of bass line

	if(chooseBass==0){ //chooses to have an ostinato bass
		keys_on.push_back(-1);
		keys_on.push_back(-1);
		if(ins.size()==1){
			//pushes the piano twice into the instrument vector
			instruments.push_back(ins[0]);  //melody
			instruments.push_back(ins[0]);  //bass
		}
		else if(ins.size()==2){
			instruments.push_back(ins[0]); //melody
			instruments.push_back(ins[1]); //bass
		}
		c.setOstinatoBass(n);
		c.leftHand = c.convertToReadableScore(c.score2);
		c.leftHand = c.addNotes(c.leftHand);
		cout<<"Ostinato Bass"<<endl;
	}


	else if(chooseBass==1){ //chooses to have a walking bass
		keys_on.push_back(-1);
		keys_on.push_back(-1);
		if(ins.size()==1){
			instruments.push_back(ins[0]);
			instruments.push_back(ins[0]);
		}
		else if(ins.size()==2){
			instruments.push_back(ins[0]);
			instruments.push_back(ins[1]);
		}
		c.setWalkingBass(n);
		c.leftHand = c.convertToReadableScore(c.score2);
		c.leftHand = c.addNotes(c.leftHand);
		cout<<"Walking Bass"<<endl;
	}


	else if(chooseBass==2){ //chooses to have just chords in the bass
		for(int i=0;i<4;i++)
			keys_on.push_back(-1);

		if(ins.size()==1){
			instruments.push_back(ins[0]);
			for(int i=0;i<3;i++)
				instruments.push_back(ins[0]);  //since the bass requires chords then it needs
				//three sepearate pianos playing at the same time
		}
		else if(ins.size()==2){
			instruments.push_back(ins[0]);
			for(int i=0;i<3;i++)
				instruments.push_back(ins[1]);
		}

		c.developChords(n);
		c.setChordsInBass(n);
		cout<<"Chords"<<endl;
	}


	c.developRhythm(n);  //creates the rhythm
	c.rightHand = c.convertToReadableScore(c.score);

	if(chooseBass== 0 || chooseBass == 1)
	//if the bass line does not have chords then it needs the function does not have use the chords
		c.rightHand = m1.developMelody(c.rightHand,c.leftHand, n, c);
	else
		c.rightHand = m1.developMelodyWithChords(c.rightHand,c.leftHand, n, c);

    for(unsigned c=0; c<instruments.size(); c++)
       file[0].Patch(c, instruments[c]); //adds the instruments

    for(unsigned row=0; row<c.leftHand.size(); row++) //reads through the score
    {
        for(unsigned i=0; i<instruments.size(); i++)
	//reads through the instruments and this will specify which should be played first
        {
            int note = x, octave = 0, vol = 0;
			//note: what note should be played at a point
			//ocatve: whether or not the pitch should be low or high
			//vol: how loud or soft it should be

            if(chooseBass==0 || chooseBass == 1){  //if the bass does not have chords
            //if it is on the melody instrument then play the first note on the score at that specfic octave and volume
				if(i<1)
            		note = c.rightHand[row%(c.rightHand.size())], octave=12*5, vol=0x5F;
            	//if it is on the bass instrument then play the first note on the score at that specfic octave and volume
            	if( i>=1 && i < instruments.size())
            		note = c.leftHand[row%(c.leftHand.size())], octave=12*3, vol=0x4F;
			}

			else if(chooseBass==2){ //if the bass does have chords
				//if it is on the melody instrument then play the first note on the score at that specfic octave and volume
				if(i<1)
            		note = c.rightHand[row%(c.rightHand.size())], octave=12*5, vol=0x6F;
            	//if it is on the bass instrument then play the first note on the score at that specfic octave and volume
				if( i>=1 && i < instruments.size()){
					int chord = c.leftHand[row%c.leftHand.size()];
				//the chord is structured differently than the other basses. The char in the left hand's score
				//is actually the number that corresponds to the space in the possibleChords vector
				//For example a 4 in the leftHand plays c.possibleChords[4] and then each note of the chord
                	if(chord != x) note = c.possibleChords[chord][i%3], octave=12*3, vol=0x4B;
            	}
			}

            //if it sees the x/99 then it does not play a note and holds the previous note out
            //This is used to simulate holding a note out
            if(note == x && i<instruments.size()) {continue;}  //reads x and continues the note
            file[0].KeyOff(i, keys_on[i], 0x20);
            keys_on[i] = -1;
            if(note == x)
				continue;
				//plays the key with the specfic note, octave and volume
            file[0].KeyOn(i, keys_on[i] = note+octave, vol);
        }
        file[0].AddDelay(c.getTempo());  //delays the sound by a certain amount of millisecond
    }

    file.Finish();  //closes and finishes up the file

    //adds the .mid to the file
    string temp=f.getFilename();
    const char *b = ".mid";
    temp += b;
    const char *C = temp.c_str();

    FILE* fp = fopen(C, "wb");//opens the file with the name C writes the file as a binary file
    fwrite(&file.at(0), 1, file.size(), fp);  //writes the music to the file
    fclose(fp);  //closes it

	cout<<"Midi file is exported"<<endl;

	if(chooseBass==2)  //if chords are being used then the chord printing function must be used
		m1.printChords(c.leftHand, c, n, "score.txt");
	else  //otherwise the other one must be used
		m1.print(c.leftHand, n, "score.txt");

	m1.print(c.rightHand, n, "score.txt"); //no matter what bass is used, it always uses this function

	cout<<"Score is exported"<<endl;

    return 0;
}


