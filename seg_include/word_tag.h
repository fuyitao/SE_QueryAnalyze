#pragma once

#include <string>
#include <vector>
#include "segmenter.h"
#include "predict_cate.h"
#include "word_classifier.h"
#include "goods_classifier.h"
#include "new_classifier.h"
#include "category_mapping.h"
#include "word_tag_common.h"
#include <map>
#include <set>
#include <cmath>
#include "ul_ccode.h"

// #define _DEBUG_LOG

#ifdef _DEBUG_LOG
  #define DebugKeyValue(key, i) std::cout << key << i << std::endl; 
  #define Debug(i) std::cout << word_tag_vect[i].word << " " \
    << GetWordClassName(word_class_vect[i]) << "\n";
  #define DebugList(l) for (int iiii = 0; iiii < l.size(); ++iiii) { \
    std::cout << word_tag_vect[l[iiii]].word << " "; \
  } \
  std::cout << "\n";
  
  #define DebugClassList for (int iiii = 0; iiii < word_tag_vect.size(); ++iiii) { \
    std::cout << word_tag_vect[iiii].word << " " \
    << word_tag_vect[iiii].type << " "; \
  } \
  std::cout << "\n";
  #define DebugLine(i) std::cout << i << " " << __LINE__ << "\n";
  #define DebugString(a, b) std::cout << a << " " << b << "\n";  
  #define Debug_Print(i) std::cout << i << "\n";
#else
  #define DebugKeyValue(key, i)
  #define Debug(i)
  #define DebugList(l)
  #define DebugClassList
  #define DebugLine(i)
  #define DebugString(a,b)
  #define Debug_Print(i)
#endif

#ifndef _TEST_H
#define _TEST_H

using namespace nlp;

namespace nlp {

class WordTag {
  public:
    WordTag();
    virtual ~WordTag();
    
    virtual bool Init(std::string dir);
    virtual bool LoadDicts(std::string dir);  
    virtual bool Reload(std::string dir);

    virtual bool Tagging(std::vector<WordTagInfo>& word_tag_vect,
                         std::vector<WordClassForGoods>& word_class_vect);
    void Tag3C(std::vector<WordTagInfo>& word_tag_vect,
               std::vector<WordClassForGoods>& word_class_vect,
               int brand_index, int product_index);
    void TagCommon(std::vector<WordTagInfo>& word_tag_vect,
                   std::vector<WordClassForGoods>& word_class_vect,
                   int brand_index);
    void TagClothing(std::vector<WordTagInfo>& word_tag_vect,
                     std::vector<WordClassForGoods>& word_class_vect,
                     int brand_index);
    void TagBeauty(std::vector<WordTagInfo>& word_tag_vect,
                   std::vector<WordClassForGoods>& word_class_vect,
                   int brand_index);
    // Create query
    virtual bool Query(std::vector<WordTagInfo>& word_tag_vect,
                       std::vector<WordClassForGoods>& word_class_vect,
                       std::string category,
                       std::string* query);
    
    virtual bool GetPredictCateByName(std::vector<WordTagInfo>& word_tag_vect, int* cate);

    virtual bool GetPredictCateListByName(std::vector<WordTagInfo>& word_tag_vect, std::string* str_category);

    virtual bool Similar(std::vector<WordTagInfo>& word_tag_vect_1,
          std::vector<WordTagInfo>& word_tag_vect_2,
          std::string category, 
          double* weight);

    void Query3C(std::vector<WordTagInfo>& word_tag_vect,
                 std::vector<WordClassForGoods>& word_class_vect,
                 GoodInfo &gi, 
                 std::string* query);
    void QueryCommon(std::vector<WordTagInfo>& word_tag_vect,
                     std::vector<WordClassForGoods>& word_class_vect,
                     GoodInfo &gi, std::string* query);
    void QueryCommonAnd(std::vector<WordTagInfo>& word_tag_vect,
                     std::vector<WordClassForGoods>& word_class_vect,
                     GoodInfo &gi, std::string* query);
    void QueryClothing(std::vector<WordTagInfo>& word_tag_vect,
                       std::vector<WordClassForGoods>& word_class_vect,
                       GoodInfo &gi, std::string* query);
    void QueryBeauty(std::vector<WordTagInfo>& word_tag_vect,
                     std::vector<WordClassForGoods>& word_class_vect,
                     GoodInfo &gi, std::string* query);
    void QueryBook(std::vector<WordTagInfo>& word_tag_vect,
                   std::vector<WordClassForGoods>& word_class_vect,
                   GoodInfo &gi, std::string* query); 
    void CheckInBracket(const char *current_str, bool* in_bracket); 

  protected:
    WordClassifier* word_classifier_;
    CategoryMapping* category_mapping_;
    PredictCate* predict_cate_;
    GoodsClassifier* goods_classifier_;
    NewClassifier* new_classifier_; 

    std::map<std::string, std::string> keep_map_;
    typedef std::map<std::string, std::string>::iterator KeepMapIter;
    std::map<std::string, std::string> new_to_old_map_;
    std::map<std::string, std::string> filter_map_;
    typedef std::map<std::string, std::string>::iterator FilterMapIter;

    std::map<std::string, std::vector<std::string> > expand_map_;

    std::map<std::string, std::vector<std::string> > expand_spec_map_;

    typedef std::map<std::string, std::vector<std::string> >::iterator ExpandMapIter;

    std::set<std::string> direct_to_common_set_;

    std::set<std::string> keep_words_cat_set_;

    std::set<std::string> dup_spec_set_;

    std::set<std::string> must_choose_product_set_;

    // standard goods 
    // brand"\t"mark1[|mark2[|...]]
    Sdict_search* standard_good_dict_;

    Sdict_search* mark_dict_; 

    // category idf dict 
    Sdict_search* cate_idf_dict_; 

    // chongzhi dict 
    std::set<std::string> cz_brand_set_; 
    std::set<std::string> cz_model_set_; 
    std::set<std::string> stopword_set_; 

    // 0 : keep
    // 1 : discard current
    // 2 : discard current and next
    int Discard(std::vector<WordTagInfo>& word_tag_vect,
                 std::vector<WordClassForGoods>& word_class_vect,
                 int index);

    bool DiscardBrand(std::vector<WordTagInfo>& word_tag_vect,
                      std::vector<WordClassForGoods>& word_class_vect,
                      int index);


    int Keep(std::vector<WordTagInfo>& word_tag_vect,
             std::vector<WordClassForGoods>& word_class_vect,
             int index);

    bool must_choose_product(std::vector<WordTagInfo>& word_tag_vect, 
                             int index);

    void GenerateAndClause(std::vector<WordTagInfo>& word_tag_vect,
                           std::vector<int>& clause_vector,
                           std::string* clause);

    void GenerateOrClause(std::vector<WordTagInfo>& word_tag_vect,
                           std::vector<int>& clause_vector,
                           std::string* clause);

    void GenerateOrClauseSame(std::vector<WordTagInfo>& word_tag_vect,
                           std::vector<int>& clause_vector,
                           std::string* clause);

    void Append(std::string& sub, std::string op, std::string* result);
    
    int DirectToCommon(const std::vector<WordTagInfo>& word_tag_vect); 

    // 0, do nothing
    // >0 skip count
    int SaveSegment(std::vector<WordTagInfo>& word_tag_vect,
                    int index,
                    std::vector<int>* result_vect);

    bool ExpandWord(std::vector<WordTagInfo>& word_tag_vect,
                   int index,
                   std::string boost,
                   std::string* expanded);

    bool ExpandSpecification(std::vector<WordTagInfo>& word_tag_vect, 
          int i, std::string* expanded); 

    void GenerateAllMatchClause(std::vector<WordTagInfo>& word_tag_vect,
          std::vector<WordClassForGoods>& word_class_vect,
          std::string* clause);

    void GenerateAllORClause(std::vector<WordTagInfo>& word_tag_vect,
          std::vector<WordClassForGoods>& word_class_vect,
          std::string* clause);
    virtual void DetectGoodsClassAndBrand(std::vector<WordTagInfo>& word_tag_vect,
                             std::vector<WordClassForGoods>& word_class_vect,
                             GoodsClass *goods_class,
                             std::string category, 
                             int* brand_index);
      
    virtual void DetectGoodsClassAndBrand(std::vector<WordTagInfo>& word_tag_vect,
                             std::vector<WordClassForGoods>& word_class_vect,
                             GoodsClass *goods_class,
                             std::string category,
                             GoodInfo* gi); 
    
    bool Has_Mixed_Model(std::vector<WordTagInfo>& word_tag_vect,
      std::vector<WordClassForGoods>& word_class_vect);

    virtual int QueryStandardEach(std::vector<WordTagInfo>& word_tag_vect,
          std::vector<std::string>& model_vect,
          Sdict_search* sel_dict,
          int brand_index, 
          int* ret_val);

    virtual int QueryStandardEachExpand(std::vector<WordTagInfo>& word_tag_vect,
      std::vector<int>& model_vect, 
      Sdict_search* sel_dict, 
      int brand_index, 
      int* ret_val);

    virtual void MakeStandardQuery(std::vector<WordTagInfo>& word_tag_vect,
          std::vector<WordClassForGoods>& word_class_vect,
          std::vector<int>& model_vect,
          int brand_index, 
          std::string* query); 

    virtual bool QueryStandardGoods(std::vector<WordTagInfo>& word_tag_vect,
          std::vector<WordClassForGoods>& word_class_vect,
          std::string& category,
          GoodInfo &gi, 
          std::string* query); 

    bool IsNeedStandSpec(std::vector<WordTagInfo>& word_tag_vect,
      std::vector<int>& brand_vect, 
      std::vector<int>& model_vect); 

    bool FindSubString(std::vector<WordTagInfo>& word_tag_vect, 
          std::vector<WordClassForGoods>& word_class_vect,
          std::vector<int>& brand_vect,
          Sdict_search *dict,
          int s, int size,
          int *id, 
          std::vector<int> *model_vect, 
          std::set<int> *model_set, 
          int *uid);

    bool IsKeepWordByCategory(std::string category, 
          std::string word); 

    bool IsSynonym(std::vector<WordTagInfo>& word_tag_vect,
                   int index, std::vector<int> prev_vect,
                   int* synonym_index);

    bool IsSynonymSpec(const char* word_str, std::string* spec_ext); 

    // comput similarity of 2 items
    double _item_similarity(GoodInfo *gi1, GoodInfo *gi2);

    bool ExtractGoodInfo(std::vector<WordTagInfo>& word_tag_vect,
          std::vector<WordClassForGoods>& word_class_vect,
          std::string category, 
          GoodInfo* gi); 

    // query term idf
    double QueryTermWeight(const char *category, const char* term);

}; 
} // end of namespace
#endif
