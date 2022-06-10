#include "gigperformer/sdk/GPMidiMessages.h"

#include "gigperformer/sdk/GPUtils.h"
#include "gigperformer/sdk/imports.h"

#define then

using namespace std;

namespace gigperformer
{
namespace sdk
{

GPMidiMessage::GPMidiMessage()
{
    // assert( sizeof(void*) >= 4 );  // Must have room for at least 3 bytes
    // (short MIDI message)
    fMidiData.longMessage = (uint8_t *)0x12345678;
    fLength = 0;
}

GPMidiMessage::~GPMidiMessage()
{
    deleteIfLongMessage();
}

const uint8_t NoteOffEvent = 0x80;
const uint8_t NoteOnEvent = 0x90;
const uint8_t AftertouchEvent = 0xA0;
const uint8_t ControllerEvent = 0xB0;
const uint8_t ProgramChangeEvent = 0xC0;
const uint8_t PolytouchEvent = 0xD0;
const uint8_t PitchbendEvent = 0xE0;
const uint8_t SysexStartByte = 0xF0;
const uint8_t SysexEndByte = 0xF7;

void GPMidiMessage::setValue(int offset, uint8_t value)
{
    if (isSysexMessage())
        then if (offset > 0 && static_cast<unsigned long>(offset) < fLength) then fMidiData.longMessage[offset] = value;
}

void GPMidiMessage::setValue(int offset,
                             uint16_t value) // 2 bytes (well, 14 bits worth)
{
    if (isSysexMessage())
        then if (offset > 0 && static_cast<unsigned long>(offset) < fLength - 1) then
        {
            fMidiData.longMessage[offset] = value & 0x7f;
            fMidiData.longMessage[offset + 1] = (value >> 7) & 0x7f;
        }
}

bool GPMidiMessage::isSysexMessage()
{
    bool result = fMidiData.longMessage[0] == SysexStartByte && fMidiData.longMessage[fLength - 1] == SysexEndByte;
    return result;
}

GPMidiMessage GPMidiMessage::makeNoteOnMessage(int noteNumber, int velocity, int channel)
{
    GPMidiMessage result;
    uint8_t *bytes = result.createSpaceForMessage(3); // Three bytes
    bytes[0] = NoteOnEvent | (channel & 0x0f);
    bytes[1] = noteNumber & 0x7f;
    bytes[2] = velocity & 0x7f;

    return result;
}

GPMidiMessage GPMidiMessage::makeNoteOffMessage(int noteNumber, int release, int channel)
{
    GPMidiMessage result;
    uint8_t *bytes = result.createSpaceForMessage(3); // Three bytes
    bytes[0] = NoteOffEvent | (channel & 0x0f);
    bytes[1] = noteNumber & 0x7f;
    bytes[2] = release & 0x7f;

    return result;
}

GPMidiMessage GPMidiMessage::makeControlChangeMessage(int ccNumber, int ccValue, int channel)
{
    GPMidiMessage result;
    uint8_t *bytes = result.createSpaceForMessage(3); // Three bytes
    bytes[0] = ControllerEvent | (channel & 0x0f);
    bytes[1] = ccNumber & 0x7f;
    bytes[2] = ccValue & 0x7f;

    return result;
}

GPMidiMessage GPMidiMessage::makePolytouchMessage(int noteNumber, int pressure, int channel)
{
    GPMidiMessage result;
    uint8_t *bytes = result.createSpaceForMessage(3); // Three bytes
    bytes[0] = PolytouchEvent | (channel & 0x0f);
    bytes[1] = noteNumber & 0x7f;
    bytes[2] = pressure & 0x7f;

    return result;
}

GPMidiMessage GPMidiMessage::makePitchbendMessage(int bend, int channel)
{
    GPMidiMessage result;
    uint8_t *bytes = result.createSpaceForMessage(3); // Three bytes
    bytes[0] = PitchbendEvent | (channel & 0x0f);
    bytes[1] = bend & 0x7f;
    bytes[2] = bend >> 7 & 0x7f;

    return result;
}

GPMidiMessage GPMidiMessage::makeProgramChangeMessage(int pcValue, int channel)
{
    GPMidiMessage result;
    uint8_t *bytes = result.createSpaceForMessage(3); // Three bytes
    bytes[0] = ProgramChangeEvent | (channel & 0x0f);
    bytes[1] = pcValue & 0x7f;

    return result;
}

GPMidiMessage GPMidiMessage::makeAftertouchMessage(int pressure, int channel)
{
    GPMidiMessage result;
    uint8_t *bytes = result.createSpaceForMessage(3); // Three bytes
    bytes[0] = AftertouchEvent | (channel & 0x0f);
    bytes[1] = pressure & 0x7f;

    return result;
}

GPMidiMessage::GPMidiMessage(const char *bytes, int length)
{
    uint8_t *thisTarget = createSpaceForMessage(length);

    for (unsigned long i = 0; i < fLength; i++)
    {
        *thisTarget++ = *bytes++;
    }
}

GPMidiMessage GPMidiMessage::makeSysexMessage(const std::string &sysexString)
{
    GPMidiMessage result(sysexString.c_str(), (int)sysexString.size());

    return result;
}

GPMidiMessage::GPMidiMessage(const std::string &hexSource)
{
    std::string binaryString = GPUtils::hex2binaryString(hexSource);

    uint8_t *thisObject = createSpaceForMessage((int)binaryString.size());

    const char *bytes = binaryString.c_str(); // Point to the beginning of the string
    for (unsigned long i = 0; i < fLength; i++)
        *thisObject++ = *bytes++;
}

GPMidiMessage::GPMidiMessage(const GPMidiMessage &source) // Copy another message
{
    uint8_t *memory = createSpaceForMessage((int)source.fLength);

    uint8_t *sourceMemory = source.asBytes();
    for (unsigned long i = 0; i < fLength; i++)
        *memory++ = *sourceMemory++;
}

GPMidiMessage &GPMidiMessage::operator=(const GPMidiMessage &source) // Assignment
{
    if (this != &source) // Make sure it's a different object
        then
        {
            // First, delete long message if we are one
            deleteIfLongMessage();

            // Now set up a new message
            fLength = source.fLength;
            uint8_t *memory = createSpaceForMessage((int)fLength);

            uint8_t *sourceMemory = source.asBytes();
            for (unsigned long i = 0; i < fLength; i++)
                *memory++ = *sourceMemory++;
        }
    return *this;
}

uint8_t *GPMidiMessage::createSpaceForMessage(int requiredSize)
{
    fLength = requiredSize;
    if (static_cast<unsigned long>(requiredSize) > sizeof(MidiData))
        then
        {
            fMidiData.longMessage = new uint8_t[requiredSize];
            return fMidiData.longMessage;
        }

    return fMidiData.shortMessage;
}

void GPMidiMessage::deleteIfLongMessage()
{
    if (isLongMessage())
        then
        {
            delete[] fMidiData.longMessage;
            fMidiData.longMessage = nullptr;
            fLength = 0;
        }
}

} // namespace sdk
} // namespace gigperformer
