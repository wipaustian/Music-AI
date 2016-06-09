#include "MIDIfile.h"

/*
Input: f - filename
output: void
Sets the name of the file
*/
void MIDIfile::setFilename(string f){
	filename=f;
}
/*
Input: 
output: file name
Grabs the name of the file
*/
string MIDIfile::getFilename(){
    return filename;	
}
/*
Input: 
output: file name
Returns the list of events for a track.
*/
MIDItrack& MIDIfile::operator[] (unsigned trackno){
    if(trackno >= tracks.size())
    {
        tracks.reserve(16);
        tracks.resize(trackno+1);
    }
        
    MIDItrack& result = tracks[trackno];
    if(result.empty())
    {
        result.AddMetaEvent(0x58,4,  4,4, 24,8);
        result.AddMetaEvent(0x51,3,  tempo>>16, tempo>>8, tempo);
    }
    return result;
}
/*
Input: void
output: void
Adds all the bytes needed to the midi file in order to create it
*/

void MIDIfile::Finish(){
    clear();  //Clear all tracks in the MidiFile, leaving one track with no data in it.
    AddBytes(
            
        "MThd", 0,0,0,6, //32 bit representation 
        0,1,
        tracks.size() >> 8, tracks.size(),
        deltaticks    >> 8, deltaticks);
    for(unsigned a=0; a<tracks.size(); ++a)
    {
        tracks[a].AddMetaEvent(0x2F, 0);
        AddBytes("MTrk", //track data
        tracks[a].size() >> 24, //adds 24 bytes to track
        tracks[a].size() >> 16, //adds 16 bytes to track
        tracks[a].size() >>  8, //adds 8 bytes to track
        tracks[a].size() >>  0); //adds 0 bytes to track
        insert(end(), tracks[a].begin(), tracks[a].end());  //inserts into midi file
    }
}
