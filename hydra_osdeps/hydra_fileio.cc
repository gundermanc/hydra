// Project Hydra
// (C) 2016 Christian Gunderman
// Hydra File System Routines

#include <cstdio>

#include "hydra/hydra_core.h"
#include "hydra/hydra_osdeps.h"

static const char FOpenFileRead[] = "r";
static const char FOpenFileWrite[] = "w";
static const char FOpenFileAppend[] = "a";
static const char FOpenFileReadUpdate[] = "r+";
static const char FOpenFileWriteUpdate[] = "w+";
static const char FOpenFileAppendUpdate[] = "a+";

HyAPI HyFile* HyOpenFile(HyStr fileName, HyOpenFileMode mode) {

    // NULL filename, don't open a file.
    if (fileName == NULL) {
        HyAssert(false);
        return NULL;
    }

    const char* modeStr = NULL;

    switch (mode) {
    case HyOpenFileRead:
        modeStr = FOpenFileRead;
        break;
    case HyOpenFileWrite:
        modeStr = FOpenFileWrite;
        break;
    case HyOpenFileAppend:
        modeStr = FOpenFileAppend;
        break;
    case HyOpenFileReadUpdate:
        modeStr = FOpenFileReadUpdate;
        break;
    case HyOpenFileWriteUpdate:
        modeStr = FOpenFileWriteUpdate;
        break;
    case HyOpenFileAppendUpdate:
        modeStr = FOpenFileAppendUpdate;
        break;
    default:
        HyAssert(false);
        return NULL;
    }

    return reinterpret_cast<HyFile*>(fopen(fileName, modeStr));
}

HyAPI void HyCloseFile(HyFile* file) {

    // Fail silently.
    if (file == NULL) {
        HyAssert(false);
        return;
    }

    fclose(reinterpret_cast<FILE*>(file));
}

HyAPI HyBool HySeekFile(HyFile* file, HyLong offset, HySeekFileRelativeTo relativeTo) {

    int fseekRelativeTo = SEEK_SET;

    // Fail on NULL file.
    if (file == NULL) {
        HyAssert(false);
        return false;
    }

    switch (relativeTo) {
    case HySeekFileRelativeToStart:
        fseekRelativeTo = SEEK_SET;
        break;
    case HySeekFileRelativeToCurrent:
        fseekRelativeTo = SEEK_CUR;
        break;
    case HySeekFileRelativeToEnd:
        fseekRelativeTo = SEEK_END;
        break;
    default:
        HyAssert(false);
        return false;
    }

    return fseek(reinterpret_cast<FILE*>(file), offset, fseekRelativeTo) == 0;
}

HyAPI HyLong HyCurrentOffsetOfFile(HyFile* file) {

    // Fail on NULL file.
    if (file == NULL) {
        HyAssert(false);
        return -1;
    }

    return ftell(reinterpret_cast<FILE*>(file));
}

HyAPI HyInt HyReadCharFromFile(HyFile* file) {

    // Fail on NULL file.
    if (file == NULL) {
        HyAssert(false);
        return -1;
    }

    int c = fgetc(reinterpret_cast<FILE*>(file));

    // Probably redundant and a bit slow (since this step will be done twice, once here
    // and once in the calling code), however, this can prevent bugs when porting to
    // other systems.
    if (c == EOF) {
        return -1;
    }
    else {
        return c;
    }
}

HyAPI HyInt HyWriteCharToFile(HyFile* file, HyChar character) {

    // Fail on NULL file.
    if (file == NULL) {
        HyAssert(false);
        return -1;
    }

    int c = fputc(character, reinterpret_cast<FILE*>(file));

    // Probably redundant and a bit slow (since this step will be done twice, once here
    // and once in the calling code), however, this can prevent bugs when porting to
    // other systems.
    if (c == EOF) {
        return -1;
    }
    else {
        return c;
    }
}