#ifndef BASE_BASICTYPES_H_
#define BASE_BASICTYPES_H_
#pragma once

#include <limits.h>         // So we can set the bounds of our types
#include <stddef.h>         // For size_t
#include <string.h>         // for memcpy

#include <stdint.h>         // For intptr_t.

typedef signed char         schar;
typedef signed char         int8;
typedef int16_t             int16;
typedef int32_t             int32;
typedef int64_t             int64;

// NOTE: unsigned types are DANGEROUS in loops and other arithmetical
// places.  Use the signed types unless your variable represents a bit
// pattern (eg a hash value) or you really need the extra bit.  Do NOT
// use 'unsigned' to express "this value should always be positive";
// use assertions for this.

typedef unsigned char      uint8;
typedef uint16_t           uint16;
typedef uint32_t           uint32;
typedef uint64_t           uint64;

// A type to represent a Unicode code-point value. As of Unicode 4.0,
// such values require up to 21 bits.
// (For type-checking on pointers, make this explicitly signed,
// and it should always be the signed version of whatever int32 is.)
typedef int32_t           char32;

const uint8  kuint8max  = (( uint8) 0xFF);
const uint16 kuint16max = ((uint16) 0xFFFF);
const uint32 kuint32max = ((uint32) 0xFFFFFFFF);
const uint64 kuint64max = ((uint64) 0xFFFFFFFFFFFFFFFFULL);
const  int8  kint8min   = ((  int8) 0x80);
const  int8  kint8max   = ((  int8) 0x7F);
const  int16 kint16min  = (( int16) 0x8000);
const  int16 kint16max  = (( int16) 0x7FFF);
const  int32 kint32min  = (( int32) 0x80000000);
const  int32 kint32max  = (( int32) 0x7FFFFFFF);
const  int64 kint64min  = (( int64) 0x8000000000000000LL);
const  int64 kint64max  = (( int64) 0x7FFFFFFFFFFFFFFFLL);

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
 private:                                  \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
//
// This should be used in the private: declarations for a class
// that wants to prevent anyone from instantiating it. This is
// especially useful for classes containing only static methods.
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
 private:                                        \
  TypeName();                                    \
  DISALLOW_COPY_AND_ASSIGN(TypeName)

#include <iostream>
#ifndef LOG_DEFINE
#define LOG_DEFINE
#define LOG(L) std::cerr << "\n" << __LINE__ << " "
#endif

#endif  // BASE_BASICTYPES_H_
