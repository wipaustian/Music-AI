#include "MIDItrack.h"

/*
Input: ch - instrument being used at the time
n -  note being played combined with an ocatve
p - volume that the note should be played at

Output: void
 
Note activation on a virtual keyboard that takes in the instrument and plays the note at the specified octave and volume

*/
void MIDItrack::KeyOn(int ch, int n, int p){
	 if(n>=0)AddEvent(0x90|ch, n, p); 
}

/*
Input: ch - instrument being used at the time
n -  note being played combined with an ocatve
p - volume that the note should be played at 

Output: void
Releasing a note on a virtual keyboard

*/

void MIDItrack::KeyOff(int ch, int n, int p){ 
	if(n>=0)AddEvent(0x80|ch, n, p); 
}
/*
Input: void

Output: void

Adds the specified delay to each note
*/
void MIDItrack::Flush(){
    AddVarLen(delay);
    delay = 0;
}
/*
Input: t - value of the delay to add to the byte

Output: void

This is a datatype used by MIDI files which can hold values from 0-0x0FFFFFFF and takes between 1 and 4 bytes.
*/    
void MIDItrack::AddVarLen(unsigned t){
	if(t >> 21) AddBytes(0x80 | ((t >> 21) & 0x7F));
    if(t >> 14) AddBytes(0x80 | ((t >> 14) & 0x7F));
    if(t >>  7) AddBytes(0x80 | ((t >>  7) & 0x7F));
    AddBytes(((t >> 0) & 0x7F));
}

template<typename... Args>

/*
Input: data - note being converted to data
Output: void

Adds an event to the buffer from raw midi data.
The sample number will be used to determine the position of the event in the buffer, which is always kept sorted.

*/

void MIDItrack::AddEvent(byte data, Args...args){
    Flush();
    if(data != running_status) AddBytes(running_status = data);
    AddBytes(args...);
}

/*
Input: ch - adds channel/instrument to the midi file
patchno - the number of the patch being added

Adds an instrument to the event buffer
*/
    
void MIDItrack::Patch(int ch, int patchno){ 
	AddEvent(0xC0|ch, patchno); 
}

