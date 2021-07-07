#include "gigperformer/sdk/cpp/GigPerformerFunctions.h"

#include <sstream>
#include <string>

#include "gigperformer/sdk/cpp/GPMidiMessages.h"
#include "gigperformer/sdk/cpp/GigPerformerAPI.h"

GigPerformerFunctions::GigPerformerFunctions(LibraryHandle handle) : fHandle(handle)
{
}

GigPerformerFunctions::~GigPerformerFunctions()
{
}

bool GigPerformerFunctions::registerCallback(const std::string &callbackName)
{
    return GP_RegisterCallback(fHandle, callbackName.c_str());
}

bool GigPerformerFunctions::unregisterCallback(const std::string &callbackName)
{
    return GP_UnregisterCallback(fHandle, callbackName.c_str());
}

void GigPerformerFunctions::switchToSetlistView()
{
    GP_SwitchToSetlistView(fHandle);
}

void GigPerformerFunctions::switchToWiringView()
{
    GP_SwitchToWiringView(fHandle);
}
void GigPerformerFunctions::switchToPanelView()
{
    GP_SwitchToPanelView(fHandle);
}

bool GigPerformerFunctions::GigPerformerFunctions::widgetExists(const std::string &widgetName)
{
    return GP_WidgetExists(fHandle, widgetName.c_str());
}

double GigPerformerFunctions::getWidgetValue(const std::string &widgetName)
{
    return GP_GetWidgetValue(fHandle, widgetName.c_str());
}

std::string GigPerformerFunctions::getWidgetTextValue(const std::string &widgetName)
{
    const int bufferLength = 1024;
    char returnBuffer[bufferLength] = {0};
    /* int actualLength  = */ GP_GetWidgetTextValue(fHandle, widgetName.c_str(), returnBuffer, bufferLength);
    std::string result(returnBuffer);
    return result;
}

bool GigPerformerFunctions::setWidgetValue(const std::string &widgetName, double newValue)
{
    return GP_SetWidgetValue(fHandle, widgetName.c_str(), newValue);
}

bool GigPerformerFunctions::resetWidgetToDefault(const std::string &widgetName, double newDefault)
{
    return GP_ResetWidgetToDefault(fHandle, widgetName.c_str(), newDefault);
}

bool GigPerformerFunctions::setWidgetCaption(const std::string &widgetName, const std::string &newCaption)
{
    return GP_SetWidgetCaption(fHandle, widgetName.c_str(), newCaption.c_str());
}

void GigPerformerFunctions::getWidgetList(std::vector<std::string> &list, bool useGlobalRackspace)
{
    list.clear();

    const int bufferLength = 150000; // Plenty - just temporary
    char returnBuffer[bufferLength] = {0};

    int actualLength = GP_GetWidgetList(fHandle, returnBuffer, bufferLength, useGlobalRackspace);

    if (actualLength > 0) // sanity check
    {
        std::stringstream lines(returnBuffer);
        std::string line;
        while (std::getline(lines, line, '\n'))
        {
            list.push_back(line);
        }
    }
}

void GigPerformerFunctions::showTuner(bool show)
{
    GP_ShowTuner(fHandle, show);
}

bool GigPerformerFunctions::tunerShowing()
{
    return GP_TunerShowing(fHandle);
}

std::string GigPerformerFunctions::getPathToMe()
{
    const int bufferLength = 10000;
    char returnBuffer[bufferLength] = {0};
    /* int actualLength =  */ GP_GetPathToMe(fHandle, returnBuffer, bufferLength);
    std::string result(returnBuffer);
    return result;
}

std::string GigPerformerFunctions::getWidgetCaption(const std::string &widgetName)
{
    const int bufferLength = 1024;
    char returnBuffer[bufferLength] = {0};
    /* int actualLength  = */ GP_GetWidgetCaption(fHandle, widgetName.c_str(), returnBuffer, bufferLength);
    std::string result(returnBuffer);
    return result;
}

std::string GigPerformerFunctions::textToHexString(const std::string &text)
{
    const int bufferLength = 1024;
    uint8_t returnBuffer[bufferLength] = {0};
    /* int actualLength = */ GP_TextToHexString(fHandle, text.c_str(), returnBuffer, bufferLength);
    std::string result((char *)returnBuffer);
    return result;
}

bool GigPerformerFunctions::listenForWidget(const std::string &widgetName, bool listen)
{
    return GP_ListenForWidget(fHandle, widgetName.c_str(), listen);
}

bool GigPerformerFunctions::listeningForWidget(const std::string &widgetName)
{
    return GP_ListeningForWidget(fHandle, widgetName.c_str());
}

bool GigPerformerFunctions::listenForMidi(const std::string &deviceName, bool listen)
{
    return GP_ListenForMidi(fHandle, deviceName.c_str(), listen);
}

bool GigPerformerFunctions::listeningForMidi(const std::string &deviceName)
{
    return GP_ListeningForMidi(fHandle, deviceName.c_str());
}

int GigPerformerFunctions::getMidiInDeviceCount()
{
    return GP_GetMidiInDeviceCount(fHandle);
}

std::string GigPerformerFunctions::getMidiInDeviceName(int index)
{
    const int bufferLength = 1024;
    char returnBuffer[bufferLength] = {0};
    /* int actualLength = */ GP_GetMidiInDeviceName(fHandle, index, returnBuffer, bufferLength);
    std::string result(returnBuffer);
    return result;
}

int GigPerformerFunctions::getMidiOutDeviceCount()
{
    return GP_GetMidiOutDeviceCount(fHandle);
}

std::string GigPerformerFunctions::getMidiOutDeviceName(int index)
{
    const int bufferLength = 1024;
    char returnBuffer[bufferLength] = {0};
    /* int actualLength =  */ GP_GetMidiOutDeviceName(fHandle, index, returnBuffer, bufferLength);
    std::string result(returnBuffer);
    return result;
}

void GigPerformerFunctions::sendMidiMessageToMidiOutDevice(const std::string &deviceName, const uint8_t *midiData,
                                                           int length)
{
    GP_SendMidiMessageToMidiOutDevice(fHandle, deviceName.c_str(), midiData, length);
}

void GigPerformerFunctions::sendMidiMessageToMidiOutDevice(const std::string &deviceName, std::string &midiData)
{
    GP_SendMidiMessageToMidiOutDevice(fHandle, deviceName.c_str(), (const uint8_t *)midiData.c_str(),
                                      (int)midiData.length());
}

void GigPerformerFunctions::sendMidiMessageToMidiOutDevice(const std::string &deviceName, const GPMidiMessage &message)
{
    GP_SendMidiMessageToMidiOutDevice(fHandle, deviceName.c_str(), message.asBytes(), (int)message.length());
}

void GigPerformerFunctions::injectMidiMessageToMidiInputDevice(const std::string &deviceName, const uint8_t *midiData,
                                                               int length)
{
    GP_InjectMidiMessageToMidiInputDevice(fHandle, deviceName.c_str(), midiData, length);
}

void GigPerformerFunctions::injectMidiMessageToMidiInputDevice(const std::string &deviceName, std::string &midiData)
{
    GP_InjectMidiMessageToMidiInputDevice(fHandle, deviceName.c_str(), (const uint8_t *)midiData.c_str(),
                                          (int)midiData.length());
}

void GigPerformerFunctions::injectMidiMessageToMidiInputAlias(const std::string &rigManagerAlias,
                                                              const uint8_t *midiData, int length)
{
    GP_InjectMidiMessageToMidiInputAlias(fHandle, rigManagerAlias.c_str(), midiData, length);
}

void GigPerformerFunctions::injectMidiMessageToMidiInputAlias(const std::string &rigManagerAlias, std::string &midiData)
{
    GP_InjectMidiMessageToMidiInputAlias(fHandle, rigManagerAlias.c_str(), (const uint8_t *)midiData.c_str(),
                                         (int)midiData.length());
}

int GigPerformerFunctions::getSongCount()
{
    return GP_GetSongCount(fHandle);
}

std::string GigPerformerFunctions::getSongName(int atIndex)
{
    const int bufferLength = 1024;
    char returnBuffer[bufferLength] = {0};
    /* int actualLength = */ GP_GetSongName(fHandle, atIndex, returnBuffer, bufferLength);
    std::string result(returnBuffer);
    return result;
}

int GigPerformerFunctions::getCurrentSongIndex()
{
    return GP_GetCurrentSongIndex(fHandle);
}

int GigPerformerFunctions::getSongpartCount(int atSongIndex)
{
    return GP_GetSongpartCount(fHandle, atSongIndex);
}

std::string GigPerformerFunctions::getSongpartName(int atSongIndex, int atPartIndex)
{
    const int bufferLength = 1024;
    char returnBuffer[bufferLength] = {0};
    /* int actualLength = */ GP_GetSongpartName(fHandle, atSongIndex, atPartIndex, returnBuffer, bufferLength);
    std::string result(returnBuffer);

    return result;
}

int GigPerformerFunctions::getCurrentSongpartIndex()
{
    return GP_GetCurrentSongpartIndex(fHandle);
}

bool GigPerformerFunctions::inSetlistMode()
{
    return GP_InSetlistMode(fHandle);
}

bool GigPerformerFunctions::switchToSong(int songIndex, int partIndex)
{
    return GP_SwitchToSong(fHandle, songIndex, partIndex);
}

bool GigPerformerFunctions::switchToSongPart(int partIndex)
{
    return GP_SwitchToSongPart(fHandle, partIndex);
}

void GigPerformerFunctions::consoleLog(const char *message)
{
    GP_ConsoleLog(fHandle, message);
}

void GigPerformerFunctions::consoleLog(const std::string &message)
{
    GP_ConsoleLog(fHandle, message.c_str());
}

void GigPerformerFunctions::scriptLog(const char *message, bool openLogWindow)
{
    GP_ScriptLog(fHandle, message, openLogWindow);
}

void GigPerformerFunctions::scriptLog(const std::string &message, bool openLogWindow)
{
    GP_ScriptLog(fHandle, message.c_str(), openLogWindow);
}

int GigPerformerFunctions::getRackspaceCount()
{
    return GP_GetRackspaceCount(fHandle);
}

std::string GigPerformerFunctions::getRackspaceName(int atIndex)
{
    const int bufferLength = 1024;
    char returnBuffer[bufferLength] = {0};
    /* int actualLength = */ GP_GetRackspaceName(fHandle, atIndex, returnBuffer, bufferLength);
    std::string result(returnBuffer);
    return result;
}
int GigPerformerFunctions::getCurrentRackspaceIndex()

{
    return GP_GetCurrentRackspaceIndex(fHandle);
}

int GigPerformerFunctions::getCurrentVariationIndex()
{
    return GP_GetCurrentVariationIndex(fHandle);
}

int GigPerformerFunctions::getVariationCount(int atRackspaceIndex)
{
    return GP_GetVariationCount(fHandle, atRackspaceIndex);
}

std::string GigPerformerFunctions::getVariationName(int atRackspaceIndex, int atIndex)
{
    const int bufferLength = 1024;
    char returnBuffer[bufferLength] = {0};
    /* int actualLength = */ GP_GetVariationName(fHandle, atRackspaceIndex, atIndex, returnBuffer, bufferLength);
    std::string result(returnBuffer);
    return result;
}

bool GigPerformerFunctions::switchToRackspace(int rackspaceIndex, int variationIndex)
{
    bool success = GP_SwitchToRackspace(fHandle, rackspaceIndex, variationIndex);
    return success;
}

bool GigPerformerFunctions::switchToRackspaceName(const std::string &rackspace, const std::string &variation)
{
    const char *presetName = nullptr;
    if (variation.length() > 0)
        presetName = variation.c_str();

    bool success = GP_SwitchToRackspaceName(fHandle, rackspace.c_str(), presetName);
    return success;
}

bool GigPerformerFunctions::saveGigUnconditionally(bool withTimestamp)
{
    bool success = GP_SaveGigUnconditionally(fHandle, withTimestamp);
    return success;
}

bool GigPerformerFunctions::loadGigByIndex(int indexNumber)
{
    bool success = GP_LoadGigByIndex(fHandle, indexNumber);
    return success;
}

void GigPerformerFunctions::tap()
{
    GP_Tap(fHandle);
}

void GigPerformerFunctions::previous()
{
    GP_Previous(fHandle);
}

void GigPerformerFunctions::next()
{
    GP_Next(fHandle);
}
