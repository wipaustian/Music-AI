/*
.h file used to create the actual midi file
*/
#ifndef MIDIFILE_H
#define MIDIFILE_H
#include "MIDI.h"
#include "MIDItrack.h"

class MIDI;

typedef unsigned char byte;

class MIDIfile: public MIDI
{
protected:
    std::vector<MIDItrack> tracks;
    unsigned deltaticks, tempo;
    string filename;
public:
    MIDIfile()
        : MIDI(), tracks(), deltaticks(1000), tempo(1000000)
    {
    }
    
    MIDItrack& operator[] (unsigned trackno);
    void Finish();
    void setFilename(string f);
    string getFilename();
};

#endif
