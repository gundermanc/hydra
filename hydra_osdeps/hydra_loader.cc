// Project Hydra
// (C) 2016 Christian Gunderman
// Hydra Dynamic Loader Code

#include <cstdlib>

#include "hydra/hydra_core.h"
#include "hydra/hydra_osdeps.h"

HyAPI HyLibrary HyLoadLibrary(HyStr libraryFileName) {

    // NULL filename, don't open a library, for consistent behavior between
    // various platforms.
    if (libraryFileName == NULL) {
        return NULL;
    }

#ifdef _WIN32
    return LoadLibrary(libraryFileName);
#elif __linux__
    return dlopen(libraryFileName, RTLD_NOW | RTLD_GLOBAL);
#elif __APPLE__
    return dlopen(libraryFileName, RTLD_NOW | RTLD_GLOBAL);
#else
#error Unsupported Operating System
#endif

}

HyAPI HyBool HyFreeLibrary(HyLibrary library) {

    // Cannot free a NULL library.
    if (library == NULL) {
        return false;
    }

#ifdef _WIN32
    return FreeLibrary(library);
#elif __linux__
    return dlclose(library) == 0;
#elif __APPLE__
    return dlclose(library) == 0;
#else
#error Unsupported Operating System
#endif

}

HyAPI HyPtr HyLibraryProcedureAddress(HyLibrary library, HyStr symbolName) {

    // Check inputs.
    if (library == NULL || symbolName == NULL) {
        return NULL;
    }

#ifdef _WIN32
    return GetProcAddress(library, symbolName);
#elif __linux__
    return dlsym(library, symbolName);
#elif __APPLE__
    return dlsym(library, symbolName);
#else
#error Unsupported Operating System
#endif
}