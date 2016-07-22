// Project Hydra
// (C) 2016 Christian Gunderman
// Operating System Dependencies Library Code Header

#include "hydra/hydra_base.h"

#ifdef _WIN32

#include <windows.h>

// Dynamically loaded library (.dll on Windows, .so on *nix).
typedef HMODULE HyLibrary;

#elif __linux__  // _WIN32

#include <dlfcn.h>

// Dynamically loaded library (.dll on Windows, .so on *nix).
typedef void* HyLibrary;

#elif __APPLE__ // __linux__

#include <dlfcn.h>

// Dynamically loaded library (.dll on Windows, .so on *nix).
typedef void* HyLibrary;

#else           // __APPLE__
#error Unsupported Operating System
#endif // _WIN32

// Loads an external dynamically loaded library (.dll on Windows, .so on *nix).
// Accepts a file name and returns the handle to the file, or NULL on failure.
HyAPI HyLibrary HyLoadLibrary(HyStr libraryFileName);

// Closes an external dynamically loaded library that was loaded with
// HyLoadLibrary(). Returns TRUE on success and FALSE on failure.
HyAPI HyBool HyFreeLibrary(HyLibrary library);

// Gets a procedure address for a HyAPI (dllexported) function in a library
// loaded with HyLoadLibrary().
HyAPI HyPtr HyLibraryProcedureAddress(HyLibrary library, HyStr symbolName);