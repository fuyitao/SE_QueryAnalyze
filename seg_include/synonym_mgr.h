#pragma once

#include <stdio.h>
#include <map>
#include <string>
#include <string.h>
#include "word_tag_common.h"

namespace nlp {

typedef struct _synonym_info {
  std::string from;
  std::string to;
  WordClassForGoods word_class;
} SynonymInfo;

class SynonymMgr {
  public:
    SynonymMgr();
    virtual ~SynonymMgr();

    bool Init(std::string dict_dir);

    bool GetSynonym(SynonymInfo* info);   

  private:
    std::map<std::string, SynonymInfo> *synonym_map_;
    typedef std::map<std::string, SynonymInfo>& MapRef;
    typedef std::map<std::string, SynonymInfo>::iterator MapIter;

    void add(std::vector<std::string>& brand_vector,
             WordClassForGoods word_class);
}; // end of class
} // end of namespace
