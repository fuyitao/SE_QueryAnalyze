#pragma once

#include "ul_ccode.h"
#include <string>
#include "ul_dict.h"
#include "segmenter.h"
#include "word_dict.h"
#include "word_tag_common.h"

#define MIN_MULTICATE_COMMON 0.08 * 1000000     //80000
#define MIN_MULTICATE_PRODUCT 0.003 * 1000000   //3000
#define NORMAL_LINE 1024                        //normal buffer len  

using namespace std; 

namespace nlp {
  class PredictCate {
    public: 
      PredictCate() { } 
      virtual ~PredictCate() {}

      bool Init(std::string dict_dir);

      virtual  bool GetPredictCate(std::vector<WordTagInfo>& word_tag_vector, int* cate);
      
      virtual  bool GetPredictCateList(std::vector<WordTagInfo>& word_tag_vector, std::string* str_category);

 
    private:
      std::map<std::string, double> c1_map_;
      Sdict_search* product_c1_dict_;
      Sdict_search* c1_term_weight_;
  }; 
}
