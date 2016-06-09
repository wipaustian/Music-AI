/*
.h file which encodes MIDI events into a track 
*/
#ifndef MIDITRACK_H
#define MIDITRACK_H
#include "MIDI.h"

typedef unsigned char byte;

class MIDItrack: public MIDI
{
protected:
    unsigned delay, running_status;
public:
    MIDItrack(): MIDI(), delay(0), running_status(0)
    {
    }
   
   	//adds the amount to delay of the sound in the file
    void AddDelay(unsigned amount) { delay += amount; }
    /*
    This is a datatype used by MIDI files which
     * can hold values from 0-0x0FFFFFFF and takes between 1 and 4 bytes.
     * @param value The varlen to add.
     */
    void AddVarLen(unsigned t);
    
    //Adds the delay number to the track length
    //sets delay back to zero
    void Flush();
    
    template<typename... Args>
    //used by the main parser for adding event to the list
    void AddEvent(byte data, Args...args);
    //void AddEvent() { }
    
    template<typename... Args>
    void AddMetaEvent(byte metatype, byte nbytes, Args...args){Flush();AddBytes(0xFF, metatype, nbytes, args...);}
    
     /*
    Input:ch - note being played, n - octave, p - volume of note
    Output:
    note activation on a virtual keyboard
    */

    void KeyOn(int ch, int n, int p);
    /*
    Input:ch - note being played, n - octave, p - volume of note
    Output:
    release  of note on a virtual keyboard.
    */
    void KeyOff(int ch, int n, int p);
   
    /*
    Input:ch - number of instrument in array, patchno - number of instrument
    Output:
    Adds the instrument to the midi file to be played
    */
    void Patch(int ch, int patchno);
};

#endif
