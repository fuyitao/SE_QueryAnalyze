#pragma once

#include "segmenter.h"
#include <string>

using namespace nlp;
using namespace std;

class SegmenterWrapper {
  public:
    SegmenterWrapper();
    virtual ~SegmenterWrapper();

    bool Init(const char* word_dict_path);

    bool Segment(const char* input_buf, int input_buf_len,
                 SegmentFlags flag);

    uint32 ResultCount() { return segmenter_->ResultCount(); }
    bool ResultAt(uint32 index, string* result);

    SegmentResult* GetSegmentResult() {
      return segmenter_->GetSegmentResult();
    }

  private:
    string word_dict_path_; 
    WordDict dict_;
    Segmenter* segmenter_;
    char* gbk_buffer_;
    uint32 gbk_buffer_len_;
    char* utf8_buffer_;
};


