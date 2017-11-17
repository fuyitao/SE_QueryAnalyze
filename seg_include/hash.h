#pragma once

#include "basic_types.h"

namespace nlp {
// create 64bit hash for str, str shoubld be end with '\0'
bool Hash64(const char* str, uint64* hash);

// This is used for exchange high32 and low32 for Hash64
// for struct :
// struct test {
//   uint32 high;
//   uint32 low;
// }
// struct test t = {0x1234, 0x5678};
// if you write t to file, it will ox43218765, when you 
// read it to a struct
// struct test2 {
//   uint64 key;
// }
// key will be 0x56781234, it is (low << 32 | high)
bool Hash64Reverse(const char* str, uint64* hash);
} // end of namespace
