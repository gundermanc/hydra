// Project Hydra
// (C) 2016 Christian Gunderman
// Base Defines

#ifndef HYDRA_BASE__H__
#define HYDRA_BASE__H__

#include <cassert>
#include <cstdlib>

#ifndef _DEBUG
#define NDEBUG
#endif

#define HyAssert assert

#define HyBool   bool
#define HyChar   char
#define HyInt    int
#define HyLong   long
#define HyStr    char*
#define HyPtr    void*

#ifdef _WIN32    // Windows
#ifdef _MSC_VER  // Visual C++

// TODO: Windows calling convention.
#define HyAPI    extern "C" __declspec(dllexport)
#define HyInternal
#define HyPrivate  static

#else            // _MSC_VER
#error Unsupported Windows Compiler
#endif           // _WIN32
#elif __linux__  // Linux
#ifdef __GNUC__  // GCC G++

// TODO: decide linux calling convention and attribute.
#define HyAPI    __attribute__((visibility("default")))
#define HyInternal __attribute__((visibility("hidden")))
#define HyPrivate static __attribute__((visibility("hidden")))

#else            // __GNUC__
#error Unsupported Linux Compiler
#endif           // __GNUC__

#elif __APPLE__  // __linux__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
#ifdef __GNUC__  // GCC G++

// TODO: decide linux calling convention and attribute.
#define HyAPI    __attribute__((visibility("default")))
#define HyInternal __attribute__((visibility("hidden")))
#define HyPrivate static __attribute__((visibility("hidden")))

#else            // __GNUC__
#error Unsupported Mac OS X Compiler
#endif           // __GNUC__
#else            // TARGET_OS_MAC
#error Unsupported Apple Operating System
#endif           // TARGET_OS_MAC
#else            // __APPLE__
#error Unsupported Operating System
#endif           // __linux__

#endif // HYDRA_BASE__H__