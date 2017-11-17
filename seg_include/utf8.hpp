#ifndef __TENGYU_UTF8_HPP__
#define __TENGYU_UTF8_HPP__

#include<iostream>
#include<string>
#include<vector>

namespace utf8{

    std::string encode(unsigned int * unicode_string , int len);

    int decode(std::string utf8_string, unsigned int * unicode_stringi, int len);

};

#endif
