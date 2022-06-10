/// \file    GPMidiMessages.h
/// \brief   Contains the definition of the GPMidiMessage class

#pragma once

#include <cstdint>

#include <string>

namespace gigperformer
{
namespace sdk
{

/// \brief   Represents a MIDI message
/// \details Leveraging some of the clever ideas from the JUCE MidiMessage class. However, having said that, we might
///          want to change the model and assume some maximum fixed size for SysexMessages so that we leverage a free
///          pool for sysex MIDI messages.
class GPMidiMessage
{
  public:
    GPMidiMessage();
    ~GPMidiMessage();

    /// \brief   Create a MIDI message from a sequence of bytes.
    GPMidiMessage(const char *bytes, int length);

    /// \brief   Create a midi message from a hex string.
    /// \param   hexSource could be "F0 0a 0b F7" for example
    explicit GPMidiMessage(const std::string &hexSource);

    /// \brief   Copy another message.
    GPMidiMessage(const GPMidiMessage &source);
    /// \brief   Assign to a message.
    GPMidiMessage &operator=(const GPMidiMessage &source);

    uint8_t *asBytes() const
    {
        return isLongMessage() ? fMidiData.longMessage : (uint8_t *)fMidiData.shortMessage;
    }

    unsigned long length() const
    {
        return fLength;
    }

    static GPMidiMessage makeNoteOnMessage(int noteNumber, int velocity, int channel);
    static GPMidiMessage makeNoteOffMessage(int noteNumber, int release, int channel);
    static GPMidiMessage makeControlChangeMessage(int ccNumber, int ccValue, int channel);
    static GPMidiMessage makePolytouchMessage(int noteNumber, int pressure, int channel);
    static GPMidiMessage makePitchbendMessage(int bend, int channel);
    static GPMidiMessage makeProgramChangeMessage(int pcValue, int channel);
    static GPMidiMessage makeAftertouchMessage(int pressure, int channel);

    static GPMidiMessage makeMidiMessage(uint8_t byte0);
    static GPMidiMessage makeMidiMessage(uint8_t byte0, uint8_t byte1);
    static GPMidiMessage makeMidiMessage(uint8_t byte0, uint8_t byte1, uint8_t byte2);
    static GPMidiMessage makeSysexMessage(const std::string &sysexString);

    bool isSysexMessage();

    /// \brief   Change a single byte in a MIDI message.
    /// \details Intended for sysex messages where the values starting at some offset can be changed.
    /// \param   offset position of the byte to change
    /// \param   value the byte at the given position will be changed to it
    void setValue(int offset, uint8_t value);

    /// \brief   Change two bytes in a MIDI message.
    /// \details Intended for sysex messages where the values starting at some offset can be changed.
    /// \param   offset position of the first byte to change
    /// \param   value the byte at offset and the one after it will be changed to the two bytes of value
    void setValue(int offset, uint16_t value);

    // Prevent any other type conversions
    template <class T> void setValue(int offset, T value) = delete;

  private:
    union MidiData {
        uint8_t shortMessage[sizeof(uint8_t *)]; // Non sysex messages will fit in a
        // space the size of a single pointer
        uint8_t *longMessage; // If we have a sysex message then we need to
                              // allocate extra space for it
    };

    MidiData fMidiData;
    unsigned long fLength; // Length of the data. If it's less than what can fit
                           // in a pointer, then no memory allocation is used

    bool isLongMessage() const
    {
        return fLength > sizeof(MidiData);
    }
    uint8_t *createSpaceForMessage(int requiredSize);
    void deleteIfLongMessage();
};

} // namespace sdk
} // namespace gigperformer
