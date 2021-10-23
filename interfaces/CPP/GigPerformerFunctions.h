#pragma once

#include <string>
#include <vector>

#include "GPMidiMessages.h"
#include "../C/imports.h"



// These are the functions your library can call
class GigPerformerFunctions
{

public:
   GigPerformerFunctions(LibraryHandle handle);
   virtual ~GigPerformerFunctions();

   std::string getPathToMe();

   void switchToSetlistView();
   void switchToWiringView();
   void switchToPanelView();


   void getPluginList(std::vector<std::string> & list , bool useGlobalRackspace);
   bool pluginExists(const std::string & pluginHandle, bool useGlobalRackspace);
    
   void setPluginParameter(const std::string & pluginHandle, int parameterNumber, double value , bool useGlobalRackspace);
   double getPluginParameter(const std::string & pluginHandle, int parameterNumber, bool useGlobalRackspace);
   int getPluginParameterCount(const std::string & pluginHandle, bool useGlobalRackspace);
   std::string getPluginParameterName(const std::string & pluginHandle, int parameterIndex, bool useGlobalRackspace);

   void getWidgetList(std::vector<std::string> & list , bool useGlobalRackspace);
   bool widgetExists(const std::string & widgetName);
    
   double getWidgetValue(const std::string & widgetName);
   std::string getWidgetTextValue(const std::string &  widgetName);
    
   bool setWidgetValue(const std::string & widgetName, double newValue);
   bool setWidgetCaption(const std::string &  widgetName, const std::string &  newCaption);
   bool resetWidgetToDefault(const std::string & widgetName, double newDefault = -1);

   std::string getWidgetCaption(const std::string &  widgetName);  
   bool listenForWidget(const std::string & widgetName, bool listen);
   bool listeningForWidget(const std::string & widgetName);
   bool listenForMidi(const std::string & deviceName, bool listen);
   bool listeningForMidi(const std::string & deviceName);
   int getMidiInDeviceCount();
   std::string getMidiInDeviceName(int index);
   int getMidiOutDeviceCount();
   std::string  getMidiOutDeviceName(int index);  
   void sendMidiMessageToMidiOutDevice(const std::string & deviceName, const uint8_t* midiData, int length);
   void sendMidiMessageToMidiOutDevice(const std::string & deviceName, std::string & midiData);
   void sendMidiMessageToMidiOutDevice(const std::string & deviceName, const GPMidiMessage & message);  
   std::string textToHexString(const std::string & text);
   void injectMidiMessageToMidiInputDevice(const std::string & deviceName, const uint8_t* midiData, int length);
   void injectMidiMessageToMidiInputDevice(const std::string & deviceName, std::string & midiData);
   void injectMidiMessageToMidiInputAlias(const std::string & rigManagerAlias, const uint8_t* midiData, int length);
   void injectMidiMessageToMidiInputAlias(const std::string & rigManagerAlias, std::string & midiData);
   int getSongCount();
   std::string getSongName(int atIndex); 
   int getCurrentSongIndex();
   int getSongpartCount(int atSongIndex);
   std::string getSongpartName(int atSongIndex, int atPartIndex);  
   int getCurrentSongpartIndex();
   bool inSetlistMode();
   bool switchToSong(int songIndex, int partIndex);
   bool switchToSongPart(int partIndex);
   void consoleLog(const char* message);
   void consoleLog(const std::string & message); 
   void scriptLog(const char* message, bool openLogWindow);
   void scriptLog(const std::string & message, bool openLogWindow);

   int getRackspaceCount();
   std::string getRackspaceName(int atIndex);
   int getCurrentRackspaceIndex();
   int getCurrentVariationIndex();
   int getVariationCount(int atRackspaceIndex);
   std::string getVariationName(int atRackspaceIndex, int atIndex);
    
   bool switchToRackspace(int rackspaceIndex, int variationIndex = 0);
   bool switchToRackspaceName(const std::string & rackspace, const std::string & variation = "");

   bool saveGigUnconditionally(bool withTimestamp);
   bool loadGigByIndex(int indexNumber);

   void tap();
   void previous();
   void next();

   void setPlayheadState(bool play);
   bool getPlayheadState();

   void showTuner(bool show);
   bool tunerShowing();




   bool registerCallback(const std::string & callbackName);   
   bool unregisterCallback(const std::string & callbackName);

private:
   LibraryHandle fHandle;
};
