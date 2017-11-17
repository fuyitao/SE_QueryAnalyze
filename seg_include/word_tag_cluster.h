#pragma once

#include "word_tag.h"

namespace bbk_offline {
  class WordTagCluster : public WordTag { 

    public: 

      WordTagCluster() {}
      virtual ~WordTagCluster() {}

      int Discard(vector<WordTagInfo>& word_tag_vect,
            vector<WordClassForGoods>& word_class_vect,
            GoodInfo* gi, int i) {
        return WordTag::Discard(word_tag_vect, word_class_vect, i);
      }

      void DetectGoodsClassAndBrand(vector<WordTagInfo>& word_tag_vect,
            vector<WordClassForGoods>& word_class_vect,
            string &category, 
            GoodInfo *gi) {
        GoodsClass goods_class;
        gi->brand_index = -1;
        gi->product_index = -1;
        gi->style_index = -1;
        WordTag::DetectGoodsClassAndBrand(word_tag_vect, word_class_vect, &goods_class, category, &(gi->brand_index));
      }
  }; 

}
