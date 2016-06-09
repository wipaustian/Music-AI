/*
.h file used to create a custom wrapper over std::vector<byte>
 * so we can quickly push_back multiple bytes with a single call.
*/
#ifndef MIDI_H
#define MIDI_H
#include <vector>   // For std::vector<>
#include <cstring>  // For std::strlen()
#include <iostream>

using namespace std;

typedef unsigned char byte;

class MIDI: public std::vector<byte>
{
public:

    template<typename... Args>
    /*
    Adds a single byte to the buffer
    */
    void AddBytes(byte data, Args...args){ push_back(data); AddBytes(args...);}
    
    template<typename... Args>
    /*
    Adds that bye to the chunk
    All midi files are made up of chunks
    4 character ASCII type and 32 bit length
    */
    void AddBytes(const char* s, Args...args){ insert(end(), s, s + std::strlen(s)); AddBytes(args...);}
    
    void AddBytes() { }
};




#endif

