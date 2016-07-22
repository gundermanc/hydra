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

// Hydra File Context.
typedef void HyFile;

// Hydra File Open Modes.
enum HyOpenFileMode {
    HyOpenFileRead,
    HyOpenFileWrite,
    HyOpenFileAppend,
    HyOpenFileReadUpdate,
    HyOpenFileWriteUpdate,
    HyOpenFileAppendUpdate
};

// Hydra File Seek Relative To.
enum HySeekFileRelativeTo {
    HySeekFileRelativeToStart,
    HySeekFileRelativeToCurrent,
    HySeekFileRelativeToEnd
};

// Opens a file for reading, writing, or appending in Hydra.
HyAPI HyFile* HyOpenFile(HyStr fileName, HyOpenFileMode mode);

// Closes a file opened with HyOpenFile().
HyAPI void HyCloseFile(HyFile* file);

// Moves to a particular offset in a file opened with HyOpenFile.
HyAPI HyBool HySeekFile(HyFile* file, HyLong offset, HySeekFileRelativeTo relativeTo);

// Gets the current offset of the cursor within the file, relative to the beginning,
// or -1 if an error occurs.
HyAPI HyLong HyCurrentOffsetOfFile(HyFile* file);

// Reads a single Char from a file and advances the cursor within the file.
// Returns -1 on error.
HyAPI HyInt HyReadCharFromFile(HyFile* file);