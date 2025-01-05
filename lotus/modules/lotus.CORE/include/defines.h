#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char       ubyte;
typedef unsigned short      ubyte2;
typedef unsigned int        ubyte4;
typedef unsigned long long  ubyte8;

typedef signed char       sbyte;
typedef signed short      sbyte2;
typedef signed int        sbyte4;
typedef signed long long  sbyte8;

typedef float   f32;
typedef double  f64;
typedef long double f80, f96, f128;

#define LOTUS_TRUE     1
#define LOTUS_FALSE    0

#define LOTUS_LITERAL(type, value)      (type){value}
#define LOTUS_LITERAL_REF(type, value) &(type){value}

#define LOTUS_LOGO (ubyte[]){    \
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,\
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20,\
  0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 0x7a, 0x7a, 0xf4, 0x00, 0x00, 0x00,\
  0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xae, 0xce, 0x1c, 0xe9, 0x00, 0x00,\
  0x00, 0x93, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85, 0xed, 0x97, 0x41, 0x0e,\
  0x03, 0x21, 0x08, 0x45, 0xa1, 0xf1, 0x80, 0xbd, 0xde, 0x1c, 0xb0, 0xe7,\
  0x78, 0x5d, 0xd9, 0x18, 0x46, 0x6b, 0xb4, 0x35, 0xce, 0x24, 0xff, 0x27,\
  0x2e, 0x24, 0x04, 0x5e, 0x80, 0x05, 0x38, 0x80, 0x6d, 0x54, 0x32, 0x33,\
  0x73, 0xf7, 0x2d, 0xc9, 0x01, 0x7b, 0x6c, 0xc9, 0x5c, 0x48, 0x00, 0x02,\
  0x10, 0x80, 0x00, 0x04, 0x20, 0x00, 0x01, 0x08, 0x40, 0x00, 0x69, 0x55,\
  0xe0, 0xb8, 0xeb, 0xba, 0xbb, 0x01, 0xa7, 0xfd, 0x73, 0x19, 0x40, 0x4e,\
  0xda, 0xd3, 0xbd, 0x5a, 0xd0, 0x2a, 0x6b, 0xd4, 0xc8, 0x9a, 0x3f, 0xdc,\
  0x82, 0x5a, 0xf0, 0xd2, 0x16, 0x81, 0xf2, 0xbf, 0x05, 0x35, 0xdc, 0x02,\
  0xe0, 0xf3, 0x4a, 0x1d, 0xaf, 0x67, 0xd5, 0xbf, 0x57, 0x0d, 0x07, 0x98,\
  0xb9, 0x8c, 0xf2, 0x44, 0xc7, 0xc9, 0xae, 0xd9, 0xbf, 0xf9, 0xfe, 0x34,\
  0x03, 0x33, 0xf6, 0xd8, 0x92, 0xe9, 0x0a, 0xfc, 0x43, 0x97, 0xb8, 0x0d,\
  0x53, 0x26, 0xd9, 0xa5, 0x37, 0x6e, 0x16, 0x53, 0x02, 0xef, 0x81, 0x4c,\
  0xa8, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60,\
  0x82  \
}
#define LOTUS_LOGO_SIZE (ubyte4)217;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define LOTUS_PLATFORM_WINDOWS 1
    #ifndef _WIN64
        #error "64-bits required on Windows"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    #define LOTUS_PLATFORM_LINUX 1
    #if defined(__ANDROID__)
        #define LOTUS_PLATFORM_ANDROID 1
    #endif
#elif defined(__APPLE__) && defined(__MACH__)
    #define LOTUS_PLATFORM_MACOS 1
#endif

#ifdef LOTUS_EXPORT
    #ifdef _MSC_VER
        #define LOTUS_API_ENTRY __declspec(dllexport)
    #elif defined(__GNUC__) || defined(__clang__)
        #define LOTUS_API_ENTRY __attribute__((visibility("default")))
    #else
        #define LOTUS_API_ENTRY
    #endif
#else
    #ifdef _MSC_VER
        #define LOTUS_API_ENTRY __declspec(dllimport)
    #elif defined(__GNUC__) || defined(__clang__)
        #define LOTUS_API_ENTRY __attribute__((visibility("default")))
    #else
        #define LOTUS_API_ENTRY
    #endif
#endif

#ifdef _MSC_VER
    #define _LOTUS_HIDDEN
#elif defined(__GNUC__) || defined(__clang__)
    #define _LOTUS_HIDDEN __attribute__((visibility("hidden")))
#endif

#ifndef _LOTUS_PRIVATE
    #if defined(__GNUC__) || defined(__clang__)
        #define _LOTUS_PRIVATE __attribute__((unused)) static
    #else
        #define _LOTUS_PRIVATE static
    #endif
#endif
