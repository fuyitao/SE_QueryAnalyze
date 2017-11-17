#pragma once 

#include <ext/hash_map>
#include <string> 

using namespace std; 
using namespace __gnu_cxx;

namespace nlp {

  struct str_hash{
    size_t operator()(const string& s) const {
      return __stl_hash_string(s.c_str());
    }
  };

  struct str_compare{
    int operator()(const string& a,const string& b) const {
      return (a==b);
    }
  };

  typedef hash_map<string,int,str_hash,str_compare> hashmap; 

}
