#pragma once

#include <math.h>
#include "common.h" 
#include "ul_log.h"
#include "hashmap.h"


using namespace std; 
using namespace nlp;

namespace bbk_offline {

  typedef hash_map<string,double,str_hash,str_compare> hm;
  
  class ProductIndex {
    public: 
      ProductIndex() {
      }

      ~ProductIndex() {
      }

      bool IsProduct(string& p) {
        return py.find(p) != py.end(); 
      }

      double GetProductWeight(string& term, string& category) {
        string key = term + "\t" + category; 
        hm::iterator ipxy = pxy.find(key); 
        hm::iterator ipx = px.find(category); 
        hm::iterator ipy = py.find(term);

        // printf("key=%s c=%s prod=%s\n", key.c_str(), category.c_str(), gi.keywords[i].c_str()); 
        if (ipxy != pxy.end() && ipx != px.end() && ipy != py.end()) {
          double wei = ipxy->second * ipy->second / ipx->second;
#ifdef _DEBUG
          char buffer[MAX_LINE];
          printf("%s %.2f\n", term.c_str(), wei); 
          sprintf(buffer, "%s|%.2f ", term.c_str(), wei); 
          debug_str.append(buffer); 
#endif
          return wei; 
        }
        return 0.0; 
      }

      int GetProductIndex(string &category, GoodInfo& gi) {
        int prod = -1; 
        double max_wei = 0;
        debug_str = ""; 
        for (int i = 0; i < gi.keywords.size(); i++) {
          double wei = GetProductWeight(gi.keywords[i], category); 
          if (wei > max_wei) {
            prod = i; 
            max_wei = wei;
          }
        }
        return prod;
      }

      void init(const char* file_pxy, const char* file_px, const char* file_py) {
        char input[MAX_LINE];

        // read file pxy
        FILE* fp = fopen(file_pxy, "r");
        while(fgets(input, sizeof(input), fp)) {
          trim(input); 
          vector<string> str_vec; 
          SplitString(input, "\t", &str_vec); 

          if (str_vec.size() < 3) {
            continue;
          }

          string key = str_vec[0] + "\t" + str_vec[1]; 
          double wei = atof(str_vec[2].c_str());

          pxy[key]=wei; 
        }
        fclose(fp); 

        // read file px
        fp = fopen(file_px, "r");
        while(fgets(input, sizeof(input), fp)) {
          trim(input); 
          vector<string> str_vec; 
          SplitString(input, "\t", &str_vec); 

          if (str_vec.size() < 2) {
            continue;
          }

          px[str_vec[0]] = atof(str_vec[1].c_str()); 
        }
        fclose(fp); 

        // read file py
        fp = fopen(file_py, "r");
        while(fgets(input, sizeof(input), fp)) {
          trim(input); 
          vector<string> str_vec; 
          SplitString(input, "\t", &str_vec); 

          if (str_vec.size() < 2) {
            continue;
          }

          py[str_vec[0]] = atof(str_vec[1].c_str()); 
        }
        fclose(fp); 
        // fprintf(stderr, "read pxy=%d, px=%d, py=%d\n", pxy.size(), px.size(), py.size());
      }

    public:
      string debug_str; 
    private:
      hm pxy; 
      hm px; 
      hm py;

  }; 
}
