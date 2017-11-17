#pragma once

#include <string>
#include "ul_dict.h"
#include "segmenter.h"
#include "word_dict.h"
#include "word_tag_common.h"
#include "synonym_mgr.h"
#include "hashmap.h"

using namespace std; 

namespace nlp {

  typedef hash_map<std::string,double,str_hash,str_compare> hm;
  
  class NewClassifier {
    public: 
      NewClassifier() { } 
      virtual ~NewClassifier() {}

      bool Init(std::string dict_dir) {
        string cate_pro_file = "new_cate_product";
        return _init((char*)dict_dir.c_str(), (char*)cate_pro_file.c_str());
      }

      bool GetSimCoreProduct(std::vector<WordTagInfo>& word_tag_vect,
            std::string category,
            GoodInfo *gi) {
        char product_cate[1024];
        double max_wei = 0;
        int count = 0;
        while(1) {
          for (int i = 0; i < word_tag_vect.size(); i++) {
            sprintf(product_cate, "%s\t%s", word_tag_vect[i].word.c_str(), category.c_str());
            Sdict_snode node;
            creat_sign64(product_cate, &(node.sign1), &(node.sign2));
            int ret = ds_op1(new_cate_product_dict_, &node, SEEK);
            if (ret == 1) {  
              double wei = node.other;
              //第一次循环 find the max product value
              if (wei > max_wei && count == 1) {
                max_wei = wei;
              }
              //第二次循环 find sim core product
              if (wei >= max_wei / 2 && count == 1) {
                gi->sim_core_product_vect.push_back(i);
              }
            }
          }
          count++;
          if (count == 2) {
            break;
          }
        }
      }

      bool GetProductIndex(std::vector<WordTagInfo>& word_tag_vect,
            std::vector<WordClassForGoods>& word_class_vect,
            std::string category,
            int* product_index) {
        char product_cate[1024];
        int prod = -1; 
        double max_wei = 0;
        for (int i = 0; i < word_tag_vect.size(); i++) {
          sprintf(product_cate, "%s\t%s", word_tag_vect[i].word.c_str(), category.c_str());
          Sdict_snode node;
          creat_sign64(product_cate, &(node.sign1), &(node.sign2));
          int ret = ds_op1(new_cate_product_dict_, &node, SEEK);
          if (ret == 1) {  
            word_class_vect[i] = PRODUCT;
            double wei = node.other;
            if (wei > max_wei) {
              prod = i; 
              max_wei = wei;
            }
          }
        }
        *product_index = prod; 
      }

    private: 
      bool _init(char* dict_dir, char* file); 
      Sdict_search* new_cate_product_dict_;
  }; 
}
