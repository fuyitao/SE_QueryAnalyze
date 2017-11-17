#pragma once

#include <string>
#include "ul_dict.h"
//#include "segmenter.h"
#include "word_dict.h"
#include "word_tag_common.h"
#include "synonym_mgr.h"
#include <set>
namespace nlp {

class GoodsClassifier;

typedef struct _ProductInfo {
    std::string product_type;
      std::string product_percent;
} ProductInfo;


class WordClassifier {
  public:
    WordClassifier();
    virtual ~WordClassifier();
    bool Init(std::string dict_dir);

    bool NewClassify(std::vector<WordTagInfo>& word_tag_vect,
                    std::vector<WordClassForGoods>& word_class_vect,
                    std::string category,
                    int* product_index,
                    int* style_index);
    bool Classify(WordProperty property,
                  std::string word_string,
                  WordClassForGoods* word_class);
    void SetGoodsClassifier(GoodsClassifier* classifier) {
      goods_classifier_ = classifier;
    }

    SynonymMgr* GetSynonymMgr() {
      return &synonym_mgr_;
    }
  private:
    Sdict_search* new_product_dict_; 
    Sdict_search* new_style_dict_; 
    Sdict_search* new_caizhi_dict_; 
    

    Sdict_search* word_class_dict_; 
    GoodsClassifier* goods_classifier_;
    SynonymMgr synonym_mgr_;
};

} // end of namespace
