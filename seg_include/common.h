#pragma once 

#include "word_tag_common.h"
#include <set> 
#include <map>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


#define MAX_BUFFER_LEN 10240000
#define MAX_MODEL_LINE 204800000        // max 2000,0000 items
#define MAX_DETAIL_LINE 102400
#define MAX_CAND_FA 20000000
#define FILENAME_LEN 500
#define MAX_LINE 5000
#define ZERO_POINT_FIVE 0.5
#define ONE_POINT_FIVE 1.5
#define TWO_POINT_ZERO 2.0
#define MAX_LINE 5000

// each topic t1&t2 max have 5000 items
#define MIN_CAND_FA_2T 5000

// 1 topic
#define MIN_CAND_FA_1T 15000000

//#define _PRINT
//#define _DEBUG

using namespace nlp; 
using namespace std; 

namespace bbk_offline {

  const int NUM_THREAD = 24;
  const double SIM_RESULT_FA = 0.5;
  const double SIM_BARCODE_FA = 0.25; 
  const double SIM_PRODUCTBAOTUAN_FA = 0.2; 
  
  const double SIM_FILTER_RESULT_FA_LOW = 0.7;
  const double PRODUCT_WEI = 1.0;

  const int N = 1000;

  const bool ENABLE_CORE_PROD_WEI = true;  
  const double CORE_PROD_WEI_MAX = 1.5; 
  const double CORE_PROD_WEI_MIN = 1.0; 
  const double CORE_PROD_WORD_NUM = 3;
  const double CORE_PROD_MIN_WEI = 1e-06; 

  const bool ENABLE_CORE_PROD_DISCARD = true; 
  const double CORE_PROD_DISCARD_SIM = 0.5;  
  const double CORE_PROD_DISCARD_RATE = 0.1; 

  // chongzi related
  const bool ENABLE_CZ_IMPROVE = true; 
  const double CZ_IMPROVE_RATE = 100.0; 
  const int C1_CONGZHI = 50004958;
  const double CZ_RESULT_FA = 0.7;

  // core product 
  const double CORE_PROD_SIMILARITY = 0.5;

  // shang improve
  const bool ENABLE_SHANG_IMPROVE = false; 

  const int SHOP_ITEM_NUM = 2;

  // bracket check 
  const bool ENABLE_BRACKET = true;
  const double BRACKET_PUNISH_WEI = 0.1; 

  // detail filter
  const bool ENABLE_DETAIL_FILTER = true; 

  // max term each item
  const int MAX_TERM_NUM_BY_ITEM = 10;

  // enable iq
  const bool ENABLE_ITEM_QUALITY = true;
 
  // enable ff
  const bool ENABLE_FF = true;
  typedef struct _TermInfo {
    int term; 
    float weight;
    bool is_prod;
  } TermInfo;

  typedef struct _ItemDetail {
    int key; 
    int value; 
  } ItemDetail; 

  typedef struct _ItemWeight {
    std::vector<ItemDetail> detail_vect;
    std::vector<TermInfo> term_list;
    std::set<int> core_prod; 
    bool created;
    int category;
    int shop_id;
    float price;
    float x2;
    float iq;
  } ItemWeight;

  //! trim will remove all the \n \t and empty char in the BACK of the str, and give a \0 to the tail as finish mark
  void trim(char* str) {
    if (str == NULL) return; 
    int len = strlen(str); 
    while(len > 0 && (str[len-1]=='\n' || str[len-1]=='\t' || str[len-1]==' ')) {
      len--; 
    }
    if (len >= 0) {
      str[len]='\0'; 
    }
  }

  class TermMap {
    public: 
      TermMap() {
        _cur_id = 0; 
      }

      ~TermMap() {
      }

      inline int GetIdByTerm(string term) {
        if (_term2id.find(term) == _term2id.end()) {
          _term2id[term]=_cur_id;
          _id2term[_cur_id]=term;
          _cur_id++; 
        }
        return _term2id[term]; 
      }

      inline string GetTermById(int id) {
        if (id >= _cur_id) {
          return ""; 
        } else {
          return _id2term[id]; 
        }
      }

      int GetMaxId() {
        return _cur_id; 
      }

      void dump_term_id(const char* file) {
        FILE* fp_out = fopen(file, "w"); 

        if (fp_out == NULL) {
          printf("failed to open %s\n", file); 
          exit(-1);
        }

        for (int i = 0; i < _cur_id; i++) {
          fprintf(fp_out, "%d\t%s\n", i, GetTermById(i).c_str()); 
        }

        fclose(fp_out);
      }
    private: 
      map<string, int> _term2id; 
      map<int, string> _id2term;

      int _cur_id; 
  }; 

  void time_start(clock_t *t) {
    *t = clock();
  }

  double time_end(clock_t *s) {
    double ret = 1.0*(clock() - *s)/CLOCKS_PER_SEC;
    *s=clock();
    return ret;
  }

  string PrintItemInfo(map<string, double> *nw , string spliter) {

    char buffer[MAX_LINE];
    string ret_str;

    for (map<string, double>::iterator iter = nw->begin(); iter != nw->end(); ++iter) {
      sprintf(buffer, "%s|%.3f", iter->first.c_str(), iter->second); 

      ret_str+= buffer; 
      ret_str+= spliter; 
    }

    return ret_str;
  }

  string PrintItemInfo(vector<TermInfo> &term_list, vector<string> &term_str_list, string spliter) {

    char buffer[MAX_LINE];
    string ret_str;

    for (int i = 0; i < term_list.size(); ++i) {
      double weight=term_list[i].weight; 
      string &term = term_str_list[term_list[i].term]; 

      sprintf(buffer, "%s|%.3f", term.c_str(), weight); 

      ret_str+= buffer; 
      ret_str+= spliter; 
    }

    return ret_str;
  }

  string PrintItemInfo(ItemWeight* iw, string spliter) {

    char buffer[MAX_LINE];
    string ret_str;

    for (int i = 0; i < iw->term_list.size(); ++i) {
      double weight=iw->term_list[i].weight; 
      int term = iw->term_list[i].term; 

      sprintf(buffer, "%d|%.3f", term, weight); 

      ret_str+= buffer; 
      ret_str+= spliter; 
    }

    return ret_str;
  }

  int getMin(int a, int b, int c) {
    int min = a;
    if (b < min) {
      min = b;
    }
    if (c < min) {
      min = c;
    }
    return min;
  }

  int BinarySearch(vector<int>* src_item_list, vector<int>* dst_item_list, int min_clu, vector<int>* inter_item_list) {
    int i, src_value, dst_value;
    int inter_count = 0;
    int min, max, mid;
    int src_size = src_item_list->size();
    int dst_size = dst_item_list->size();
    for (i = 0; i < src_size; i++) {
      min = 0; max = dst_size - 1;
      src_value = (*src_item_list)[i];
      while (min <= max && mid < dst_size) {
        mid = (min + max) / 2; 
        dst_value = (*dst_item_list)[mid];
        if (dst_value == src_value) {
          inter_item_list->push_back(src_value);
          inter_count++;
          break;
        } else if (src_value > dst_value) {
          min = mid + 1;
        } else {
          max = mid - 1;
        }
      }

      if (inter_count > min_clu) {
        inter_item_list->clear();
        return 0;
      }
    }
    return inter_count;
  }

  int Merge(vector<int>* src_item_list, vector<int>* dst_item_list, int min_clu, vector<int>* inter_item_list) {
    int i=0, j=0, inter_count=0;
    int src_value, dst_value;
    int src_size = src_item_list->size();
    int dst_size = dst_item_list->size();

    while (inter_count <= min_clu && i < src_size && j < dst_size) {
      src_value = (*src_item_list)[i];
      dst_value = (*dst_item_list)[j];
      if (src_value == dst_value) {
        inter_item_list->push_back(src_value);
        inter_count++;
        i++,j++;
      } else if (src_value < dst_value){
        i++;
      } else {
        j++;
      }
    }
    if (inter_count > min_clu) {
      inter_item_list->clear();
      return 0;
    }
    return inter_count;
  }
  
  // *list1: 1 2 6 9 20
  // *list2: 1 3 5 8 87 90

  int getFastInterSection(vector<int>* src_item_list, vector<int>* dst_item_list, 
        int min_clu, vector<int>* inter_item_list) {
    int mlogn = 0, nlogm = 0, mplusn = 0;
    int inter_count = 0;

    int src_size = src_item_list->size();
    int dst_size = dst_item_list->size();

    if (dst_size > 0) {
      mlogn = src_size * log(dst_size);
    } 
    if (src_size > 0) {
      nlogm = dst_size * log(src_size);
    }
    
    mplusn = src_size + dst_size;

    int min = getMin(mlogn, nlogm, mplusn);

    if (min == mlogn) {
      inter_count = BinarySearch(src_item_list, dst_item_list, min_clu, inter_item_list);
    } else if ( min == nlogm) {
      inter_count = BinarySearch(dst_item_list, src_item_list, min_clu, inter_item_list);
    } else if (min == mplusn) {
      inter_count = Merge(src_item_list, dst_item_list, min_clu, inter_item_list);
    }

    return inter_count;
  }

  /*
  string PrintItemInfo(int itemid, string spliter, TermMap* tm) {
    if (itemid < item_info.size() && item_info[itemid] != NULL) { 
      ItemWeight* iw = item_info[itemid];
      return PrintItemInfo(iw, spliter, tm); 
    }
    return ""; 
  } */

  /*
  int getInterSection(vector<int>* src_item_list, vector<int>* dst_item_list, 
        int min_clu, vector<int>* inter_item_list) {
    int inter_count = 0;
    int i = 0, j = 0;
    int src_value = 0;
    int dst_value = 0;

    int src_size = src_item_list->size();
    int dst_size = dst_item_list->size();

    while (inter_count <= min_clu && i < src_size && j < dst_size) {
      src_value = (*src_item_list)[i];
      dst_value = (*dst_item_list)[j];
      if (src_value == dst_value) {
        inter_item_list->push_back(src_value);
        inter_count++;
        i++;
        j++;
      } else if (src_value < dst_value) {
        i++;
      } else {
        j++;
      }
    }

    if (inter_count > min_clu) {
      inter_item_list->clear();
      return 0;
    }

    return inter_count;

  }
  */



}
