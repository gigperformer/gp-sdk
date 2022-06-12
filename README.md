# Gig Performer SDK

## Prolog

Gig Performer is an audio plugin host (AU, VST3 and VST host) for live performance and session musicians.
Before you consider writing a library for use with Gig Performer, please familiarize yourself with the operation of Gig Performer itself so that you have a reasonable understanding of its capabilities and functionality that might impact your library. More information about Gig Performer can be found at https://gigperformer.com

## Introduction

Starting with Gig Performer 4, Gig Performer (abbreviated as _GP_ from now on) exposes an API that allows third party developers to create libraries that can be used to control GP and to respond to events in GP.
The primary purpose of the API is to enable the creation of libraries to manage control surfaces and other hardware that one might want to use with GP.
This SDK includes the source code that will need to be included in every third party project as well as some samples that will help to get started.

## Fundamentals

1. GP will query all libraries found in `/Users/Shared/Gig Performer/Extensions` (macOS) and in `C:\Users\All Users\Gig Performer\Extensions` (Windows) to collect information (product name, build date, description, etc).
   This information will be displayed to the user who can decide which libraries should be loaded and used.
2. GP will next load the desired libraries.
3. GP exposes a collection of functions that a library can call to interact with the application.
   For example, you can set the current value of a widget in a rackspace (the widget must have a handle defined).
   You can ask for the number of songs in the current setlist, get the name of each song, get the names of all the song parts in a song, switch from one song to another and so forth.
   The library can of course also send MIDI events into GP.
4. The GP API supports callbacks into the third-party library to notify the library that something "happened".
   For example, if the user switches from one song to another, a library supporting a keyboard controller with a programmable display could be notified so that it can display the names of the song parts in the new song.
   If the library is interested in MIDI events coming from a particular piece of hardware, it can be called whenever that hardware sends out MIDI data.

## Structure of the API

The underlying API is defined as a collection of typedefs and functions in C as this will allow almost any language to be used to develop a library as long as it can make C calls.
Simple examples are provided in C++ and shell scripts as well as CMake descriptions are included to automate the build process.
The example class included for the C++ example will perform some initial operations automatically so that the user does not need to be concerned with low level setup.

## Working with the API

When GP is first loaded, it will look for third party libraries.
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

## Using GPScript functions with extensions (experimental)

The GP API includes a mechanism that allows extension developers to define GPScript functions that are available to Gig Performer users.
The implementations of those functions exist within the extension itself.
The purpose of this mechanism is to allow third parties to develop extensions such as graphic packages, algorithmic music packages, lighting control systems and so forth that can then be manipulated inside a GPScript callback while performing with Gig Performer.
This process must be tested extremely carefully as erroneous implementations can easily crash Gig Performer.
The extension developer must ensure that incoming parameters are within expected ranges so that a Gig Performer user cannot crash the system by sending invalid values in a GPScript function call.

### Types

The required types you will need to support GPScript are defined in `gigperformer/sdk/types.h` which is included in the SDK.

- The helper functions used to accept and send back parameters will use instances of this type:

  ```c
  typedef void* GPRuntimeEngine;
  ```

- This is the required signature for the functions you implement in the extension that can be called from Gig Performer via GPScript:

  ```c
  typedef void (*TGPScriptExecutableFunctionSignature)(GPRuntimeEngine* vm);
  ```

- This structure is used to define the parts of a GP function so that it can be properly injected back into Gig Performer.
  During initialization, the function `RequestGPScriptFunctionSignatureList` will be called and you must provide an array of this structure, appropriately filled in.
  An example of this is included in the cpp example for the SDK.
  Gig Performer also includes a location value that indicates what script entity is asking for your function list.
  This allows you to control whether your functions should be available everywhere or perhaps only in the Gig Script, or only in the Global Rackspace, etc:

  ```c
  typedef struct
  {
      const char *functionName;                               ///< Just the name of the function
      const char *args;                                       ///< The args and the optional return type
      const char *returns;                                    ///< optional return type clause
      const char *description;                                ///< For the helper in the script editor
      TGPScriptExecutableFunctionSignature functionToExecute; ///< Pointer to the function implementation
  } ExternalAPI_GPScriptFunctionDefinition;
  ```

### Accessing parameters and returning results

Arguments defined in the function are pushed on to a stack and the extension must pull all the arguments from the stack as the initial action in any function defined in the extension that's associated with an injected GP Script function signature.
In particular, the developer must pull the arguments from the stack in the reverse order.
For example, suppose you have defined the following GP Script signature to multiply the first two arguments, add in the third argument and return the result:

```cpp
ExternalAPI_GPScriptFunctionDefinition{"MA", "a:Double, b:Double, c:Double", "Returns Double", "Mult And Add", MultAdd}
```

Provided, the name of your extension is `myextension`, the GP user will see this GP Script function:

```
function mytension_MA(a : Double, b : Double, c : Double) Returns Double
```

The function would most likely be implemented in your extension as follows:

```c
extern "C" void MultAdd(GPRuntimeEngine *vm)
{
    // Access the incoming arguments in the reverse order
    double c = GP_VM_PopDouble(vm);
    double b = GP_VM_PopDouble(vm);
    double a = GP_VM_PopDouble(vm);

    // Perform your calculation
    double result = a * b + c;

    // Push the result back on to the stack
    GP_VM_PushDouble(vm, result);
}
```

If you do not perform the three "pops" at the beginning (in the reverse order of the declared function) and the "push" at the end, the GP Script stack will be corrupted and Gig Performer will crash.

### GP Script supported function types

Currently, the only types that are available are the basic scalar types, i.e, `Integer`, `Double`, `Boolean` and `String`.
A future version will provide support for arrays and other objects.
