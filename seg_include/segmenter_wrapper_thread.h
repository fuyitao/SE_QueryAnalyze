#pragma once

#include "segmenter.h"
#include "spinlock.h"
#include <string>

using namespace nlp;
using namespace std;

typedef struct _segment_thread_info {
  volatile int lock;
  Segmenter* segmenter;
  char* gbk_buffer;
  char* utf8_buffer;
} SegmentThreadInfo;

class SegmenterWrapperThread {
  public:
    SegmenterWrapperThread(int thread_count);
    virtual ~SegmenterWrapperThread();

    bool Init(const char* word_dict_path);

    // return -1, if no one available
    // else return the index
    int LockOne();
    void Unlock(int index);

    bool Segment(const char* input_buf,
                 int input_buf_len,
                 SegmentFlags flag,
                 int index);

    bool SegmentGram(const char* input_buf,
                 int input_buf_len,
                 SegmentFlags flag,
                 int index);

    uint32 ResultCount(int index) {
      return thread_info_[index].segmenter->ResultCount();
    }
    bool ResultAt(uint32 index, string* result,
                  int thread_index);
    bool ResultAtGBK(uint32 index, string* result,
                  int thread_index);
 
    // to get the phrase term
    // if got, return true, resuls.length() > 0
    // if not, return false, result.length() == 0
    bool GetPhraseTerms(uint32 index, std::vector<std::string>* results, int thread_index);
    bool GetPhraseTermsGBK(uint32 index, std::vector<std::string>* results, int thread_index);
    bool GetPhrasePropertyGBK(uint32 index,
                              std::vector<std::string>* result,
                              std::vector<WordProperty>* word_property_vect,
                              int thread_index);
 
    SegmentResult* GetSegmentResult(int index)  {
      return thread_info_[index].segmenter->GetSegmentResult();
    }

  private:
    string word_dict_path_; 
    WordDict dict_;
    uint32 gbk_buffer_len_;
    int thread_count_;
    SegmentThreadInfo* thread_info_;
};


