# Gig Performer SDK

## Prolog

Before you consider writing a library for use with Gig Performer, please familiarize yourself with the operation of Gig Performer itself so that you have a reasonable understanding of its capabilities and functionality that might impact your library.

## Introduction

Starting with Gig Performer 4, Gig Performer (abbreviated as _GP_ from now on) exposes an API that allows third party developers to create libraries that can be used to control GP and to respond to events in GP.
The primary purpose of the API is to enable the creation of libraries to manage control surfaces and other hardware that one might want to use with GP.
This SDK includes the source code that will need to be included in every third party project as well as some samples that will help to get started.

## Fundamentals

1. GP will query all libraries found in `/Users/Shared/Gig Performer/Extensions` (macOS) and in `C:\Users\All Users\Gig Performer\Extensions` (Windows) to collection information (product name, build date, description, etc).
   This information will be displayed to the user who can decide which libraries should be loaded and used.
2. GP will next load the desired libraries.
3. GP exposes a collection of functions that a library can call to interact with the application.
   For example, you can set the current value of a widget in a rackspace (the widget must have a handle defined).
   You can ask for the number of songs in the current setlist, get the name of each song, get the names of all the song parts in a song, switch from one song to another and so forth.
   The library can of course also send MIDI events into GP.
4. The GP API supports callbacks into the third party library to notify the library that something "happened".
   For example, if the user switches from one song to another, a library supporting a keyboard controller with a programmable display could be notified so that it can display the names of the song parts in the new song.
   If the library is interested in MIDI events coming from a particular piece of hardware, it can be called whenever that hardware sends out MIDI data.

## Structure of the API

The underlying API is defined as a collection of typedefs and functions in C as this will allow almost any language to be used to develop a library as long as it can make C calls.
Simple examples are provided in C++ and shell scripts as well as CMake descriptions are included to automate the build process.
The example class included for the C++ example will perform some initial operations automatically so that the user does not need to be concerned with low level setup.

## Working with the API

When GP is first loaded, it will looked for third party libraries.
For each library that it finds, the following sequence of steps will be performed:

1. GP will open the library.
2. GP will look for a function called GPQueryLibrary.
   If found, it will be invoked so that the library can return useful information about itself thereby allowing the user to decide whether to use a particular library.
   The information should be returned as a small XML formatted string.
3. GP will then close the library.
4. For all libraries that the user chooses to load, GP will then open the library again and will look for a function called GPRegister.
5. If the function is found, it will be called with two parameters:

   1. `void* (*TGetGPFunctionType)(void* handle, const char* functionName)`
      The first parameter is the address of a function that the library can use to call back into GP to request the address of each function that GP exposes to the API.
   2. The second parameter, `void* handle`, is an opaque handle whose value should be stored and included as a parameter in all subsequent calls into Gig Performer.

   The function should return a string that represents the name of the control surface or whatever product this library supports.
   That name will show up in a list that the user can view and choose to enable or disable.

6. Your implementation of this function should include calls to get the addresses of all the other available functions exposed by GP so that you can use them later.
   Note that the C++ wrapper will do this automatically.
   Here is an example of the raw GPRegister function in raw C along with a single callback:

   ```c
   static LibraryHandle Handle;

   extern "C" void GPRegister(TGetGPFunctionType getGPFunctionAddress, void *handle)
   {
      Handle = handle; // Store the handle for future use
      InitializeImportedFunctions(handle, getGPFunctionAddress);

      // You will need to register callbacks to be informed of changes
      GP_RegisterCallback(handle, "OnSongChanged");
   }

   extern "C" void OnSongChanged(int oldIndex, int newIndex)
   {
      char str[255];
      sprintf(str, "Song changed from: %d, to: %d", oldIndex, newIndex);
      GP_Log(Handle, str);
   }
   ```

7. Register for whatever other callbacks your library will need.
   However, to keep your library mean and lean, please don't just arbitrarily register for all callbacks.
8. Your library is now ready to interact with Gig Performer and whatever hardware you are controlling.
