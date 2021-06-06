#pragma once

#include <stdint.h>
#include <string>



// Leveraging some of the clever ideas from the JUCE MidiMessage class
// However, having said that, we MIGHT want to change the model and assume some
// maximum fixed size for SysexMessages so that we leverage a free pool for sysex MIDI messages
class GPMidiMessage
{
   public:
      GPMidiMessage();
      ~GPMidiMessage(); 

      GPMidiMessage(const char* bytes, int length); // Create a midi message from a sequence of bytes
      GPMidiMessage(const std::string & hexSource); // Create a midi message from a hex string "F0 0a 0b F7" for example

      GPMidiMessage(const GPMidiMessage & source); // Copy another message
      GPMidiMessage & operator= (const GPMidiMessage & source); // Assignment

      uint8_t* asBytes() const
         { 
            return isLongMessage() ? fMidiData.longMessage : (uint8_t*) fMidiData.shortMessage; 
         }

      unsigned long length() const { return fLength; }

      static GPMidiMessage makeNoteOnMessage(int noteNumber, int velocity, int channel);
      static GPMidiMessage makeNoteOffMessage(int noteNumber, int release, int channel);
      static GPMidiMessage makeControlChangeMessage(int ccNumber, int ccValue, int channel);
      static GPMidiMessage makePolytouchMessage(int noteNumber, int pressure, int channel);
      static GPMidiMessage makePitchbendMessage(int bend, int channel);
      static GPMidiMessage makeProgramChangeMessage(int pcValue, int channel);
      static GPMidiMessage makeAftertouchMessage(int pressure, int channel);

      static GPMidiMessage makeMidiMessage(uint8_t byte0);
      static GPMidiMessage makeMidiMessage(uint8_t byte0, uint8_t byte1);
      static GPMidiMessage makeMidiMessage(uint8_t byte0, uint8_t byte1,  uint8_t byte2);
      static GPMidiMessage makeSysexMessage(const std::string & sysexString);

      bool isSysexMessage();

      // These are intended for sysex messages where the values starting at some offset can be changed
      void setValue(int offset, uint8_t value); 
      void setValue(int offset, uint16_t value); // 2 bytes (well, 14 bits worth)
      template <class T>
      void setValue(int offset, T value) = delete; // Prevent any other type conversions

   private:
      union MidiData
         {
            uint8_t shortMessage[sizeof (uint8_t*)]; // Non sysex messages will fit in a space the size of a single pointer
            uint8_t* longMessage; // If we have a sysex message then we need to allocate extra space for it
         };

      MidiData fMidiData;
      unsigned long fLength; // Length of the data. If it's less than what can fit in a pointer, then no memory allocation is used   

      bool isLongMessage() const         { return fLength >  sizeof (MidiData); }
      uint8_t* createSpaceForMessage(int requiredSize);
      void deleteIfLongMessage();
};
