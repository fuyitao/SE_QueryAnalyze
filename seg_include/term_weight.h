#pragma once

#include <math.h>
#include "common.h" 
#include "ul_log.h"
#include "ul_ccode.h"
#include "ul_dict.h"

using namespace std; 
using namespace nlp;

namespace bbk_offline {

  class TermWeightDict {
    public: 
      
      TermWeightDict() {

      }

      ~TermWeightDict() {
        if (cate_idf_dict_ != NULL) {
          ds_del(cate_idf_dict_);
          cate_idf_dict_ = NULL;
        }
      }

      bool Init(const char* dict_dir, const char* dict_name) {
        // load mark dict 
        cate_idf_dict_ = ds_load((char*)dict_dir, (char*)dict_name);
        if (cate_idf_dict_ == NULL) {
          return false;
        }
      }
 
      inline double QueryTermWeight(int category, string term) {
        char buffer[1024];
        Sdict_snode node;

        int df;
        int tc = 1;

        // query doc freq
        sprintf(buffer, "df\t%d", category);
        creat_sign64(buffer, &(node.sign1), &(node.sign2));
        int ret = ds_op1(cate_idf_dict_, &node, SEEK);

        if (ret == 1) {
          df = node.other;
        } else {
          return 1;
        }

        // query cate idf
        sprintf(buffer, "%d\t%s", category, term.c_str());
        creat_sign64(buffer, &(node.sign1), &(node.sign2));
        ret = ds_op1(cate_idf_dict_, &node, SEEK);

        if (ret == 1) {
          tc = node.other;
        }

        return 1 + log(df / (tc + 1)); 
      }

    private:
      // category idf dict 
      Sdict_search* cate_idf_dict_; 

  };


  class TermWeight {
    public: 
      TermWeight(char* idf_file) {
        LoadTermWeight(idf_file);
      }

      ~TermWeight() {
      }

      inline double QueryTermWeight(int c1, string term) {
        if (_c1_term_w.find(c1) == _c1_term_w.end()) {
          return 0;
        }

        map<string,double> *c1_map = _c1_term_w[c1]; 
        if (c1_map->find(term) == c1_map->end()) {
          return 0; 
        }

        return (*c1_map)[term];

      }


      int LoadTermWeight(char* file) {
        char buffer[MAX_LINE]; 
        char term[MAX_LINE];
        char gb_term[MAX_LINE];

        FILE *fp_map = fopen(file, "r");
        if (fp_map == NULL) {
          ul_writelog(UL_LOG_TRACE, "failed to load map %s", file); 
          return -1;
        }

        ul_writelog(UL_LOG_TRACE, "start load file: %s", file); 
        int count=0; 
        while (fgets(buffer, MAX_LINE, fp_map)) {
          trim(buffer);
          string str = buffer; 
          vector<string> fields; 
          SplitString(buffer, "\t", &fields); 

          if (fields.size() < 4) {
            continue;
          }
          int c1 = atoi(fields[0].c_str());
          double w = atof(fields[3].c_str());

          strcpy(term, fields[1].c_str());
          ul_trans2lower(term, term);
          int ret = ul_utf8_to_gbk(gb_term, MAX_LINE, term); 

          if (ret < 0) continue;

          map<string,double>* term_w = NULL;

          if (_c1_term_w.find(c1) == _c1_term_w.end()) {
            term_w = new map<string,double>();
            _c1_term_w[c1]=term_w;
          } else {
            term_w = _c1_term_w[c1];
          }

          (*term_w)[gb_term]=w;

          count++; 

          if (count % 100000 == 0) {
            ul_writelog(UL_LOG_TRACE, "load idf, line=%d", count);
          }
        }

        fclose(fp_map);

      }

    private: 
      map<int, map<string,double>*> _c1_term_w; 

  }; 



}
