#pragma once

#include <string>
#include "ul_dict.h"
#include <map>
#include <vector>
#include "basic_types.h"
#include "word_tag_common.h"
#include "meta_data.h"
#include "word_dict.h"
#include "word_tag_common.h"
#include "segment_define.h"
#include <set>

namespace nlp {

typedef struct _GoodsClassifyInfo {
  std::string word;
  WordProperty property;
  WordClassForGoods word_class;

  _GoodsClassifyInfo() {
    word_class = INVALID;
  }
} GoodsClassifyInfo;

typedef struct _BrandInfo {
  std::string brand_type;
  std::string brand_percent;
} BrandInfo;

class GoodsClassifier {
  public:
    GoodsClassifier();
    virtual ~GoodsClassifier();
    bool Init(std::string dict_dir);

    bool Classify(std::string goods_name,
                  std::vector<int>* goods_class);
    
    bool NewClassify(std::vector<WordTagInfo>& word_tag_vect,
                  std::vector<WordClassForGoods>& word_class_vect,
                  std::string category,
                  int* brand_index);

    bool ClassifyToCat(std::vector<GoodsClassifyInfo>& word_vect,
                       std::string* cat);

    bool ClassifyToSubCat(std::vector<GoodsClassifyInfo>& word_vect,
                          int* sub_cat);

    void SetMetaData(MetaDataManager* mgr) {
      meta_mgr_ = mgr;
    }

  private:
    std::set<std::string> discard_brand_set_;

    Sdict_search* new_brand_dict_;

    Sdict_search* goods_class_dict_; 
    //std::map<uint64, std::vector<BrandInfo>* > new_brand_dict_;
    //typedef std::map<uint64, std::vector<BrandInfo>* >::iterator NewBrandClassIter;

    std::map<uint64, std::vector<int>* > goods_class_array_dict_;
    typedef std::map<uint64, std::vector<int>* >::iterator GoodsClassIter;

    std::map<uint64, std::vector<std::string>* > new_goods_class_dict_;
    typedef std::map<uint64, std::vector<std::string>* >::iterator NewGoodsClassIter;

    void AddToDict(char* brand_name, int brand_id);
    void AddToDictInternal(char* brand_name, int brand_id);
    void AddToDictNew(char* brand, char* brand_class); 

    MetaDataManager* meta_mgr_; 
};

} // end of namespace
