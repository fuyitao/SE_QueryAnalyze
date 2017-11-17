#pragma once

#include "word_dict.h"
#include <vector>
#include <string>

namespace nlp {

enum SegmentFlags {
  BASIC = 2,
  PHRASE = 4,
  SUB_PHRASE = 8,
  HUMAN_NAME = 16,
  BOOK_NAME = 32,
  ALL = 64,
};

enum Encoding {
  GBK = 0,
  UTF8 = 1
};

enum SegmentWordType {
  STATIC_BASIC = 0,
  DYNAMIC_BASIC,
  STATIC_PHRASE,
  DYNAMIC_PHRASE,
};

// segment result
class SegmentResult {
 public:
  SegmentResult(uint32 max_term,  SegmentFlags segment_flags);
  virtual ~SegmentResult();

  // put the next result to result
  // if fetched, return true, else return false
  void GetAllResults(std::vector<std::string>* results);
  bool ResultAt(uint32 index, std::string* result);
  uint32 ResultCount() {
    return word_entry_pointer_index_;
  }

  // to get the phrase term
  // if got, return true, resuls.length() > 0
  // if not, return false, result.length() == 0
  bool GetPhraseTerms(uint32 index, std::vector<std::string>* results);
  bool GetPhraseWordProperty(uint32 index,
                          std::vector<std::string>* results,
                          std::vector<WordProperty>* word_property_vect);

  bool IsMark(uint32 index);
  void RecursiveGetWordString(WordEntry* we, std::string* result);
  void Reset(uint32 max_term, SegmentFlags segment_flags);
  void Clear();

  void SetSegmentFlags(SegmentFlags segment_flags) {
    segment_flags_ = segment_flags;
  }

  void SetWordDict(WordDict* dict) {
    dict_ = dict;
  }

  // return next semgent result index
  uint32 SegmentResultIndex() { return word_entry_pointer_index_; }

  void SetSegmentResultIndex(uint32 index) {
    word_entry_pointer_index_ = index;
  }

  void DecreaseSegmentResult(uint32 delta) {
    word_entry_pointer_index_ -= delta;
  }

  void IncreaseSegmentResult(uint32 delta) {
    word_entry_pointer_index_ += delta;
  }

  bool AddSegmentResult(WordEntry* word_entry);
  bool AddSegmentResult(WordDict* dict, uint32 entry_index) {
    return AddSegmentResult(dict->GetWordEntry(entry_index)); 
  }

  WordEntry* GetSegmentResult(int index) {
    if (index >= word_entry_pointer_index_) {
      return NULL;
    }
    return word_entry_pointers_[index];
  }

  void SetSegmentResult(uint32 pos, WordEntry* entry) {
    word_entry_pointers_[pos] = entry;
  }

  // Dynamic word
  uint32 CreateDynamicWord(char* word);
  // Dynamic phrase
  uint32 CreateDynamicPhrase(uint32 start, uint32 count);

  bool AddDynamicSegmentResult(uint32 entry_index);
  
  bool UnknowEntryBufferFull() {
    return unknow_entry_buffer_index_ >= unknow_entry_buffer_size_;
  }

  bool UnknowPhraseBufferFull() {
    return unknow_phrase_buffer_index_ + 800 >=
        unknow_phrase_buffer_size_;
  }

  WordEntry* CurrentUnknowEntry() {
    return unknow_entry_buffer_ + unknow_entry_buffer_index_;
  }

  WordEntry* GetUnknowEntry(uint32 pos) {
    return unknow_entry_buffer_ + pos;
  }

  uint32 UnknowPhraseBufferIndex() {
    return unknow_phrase_buffer_index_;
  }

  void AddUnknowPhrase(uintptr_t p) {
    unknow_phrase_buffer_[unknow_phrase_buffer_index_] = p;
    unknow_phrase_buffer_index_ ++;
  }

  void IncreaseUnknowPhraseIndex(uint32 delta) {
    unknow_phrase_buffer_index_ += delta;
  }

  uintptr_t UnknowPhraseInfo(uint32 pos) { 
    return unknow_phrase_buffer_[pos]; 
  }

  void SetUnknowPhraseInfo(uint32 pos, uintptr_t value) {
    unknow_phrase_buffer_[pos] = value;
  }

  void CopyUnknowPhrase(uint32 pos, uint32 size) {
    memcpy(unknow_phrase_buffer_ + unknow_phrase_buffer_index_,
           unknow_phrase_buffer_ + pos, size);
  }

  void IncreaseUnknowEntryBufferIndex(uint32 delta) {
    unknow_entry_buffer_index_ += delta;
  }

  uint32 UnknowEntryBufferIndex() {
    return unknow_entry_buffer_index_;
  }
 
 private:
  void Init();

  WordDict* dict_;

  uint32 max_term_;
  SegmentFlags segment_flags_;
  uint32 merge_flag_;
  uint32 offset_;

  // store segment result
  WordEntry **word_entry_pointers_;
  uint32 word_entry_pointer_index_;

  // store dynamic result
  char* unknow_buffer_;
  uint32 unknow_buffer_size_;
  uint32 unknow_buffer_index_;

  uintptr_t* unknow_phrase_buffer_;
  uint32 unknow_phrase_buffer_size_;
  uint32 unknow_phrase_buffer_index_;

  WordEntry* unknow_entry_buffer_;
  uint32 unknow_entry_buffer_size_;
  uint32 unknow_entry_buffer_index_;
} ;

class Segmenter {
  public:
   Segmenter(WordDict* dict);
   virtual ~Segmenter();

   bool Segment(const char* inbuf, int inlen,
                Encoding encoding, SegmentFlags flag);

   bool SegmentGram(const char* inbuf, int inlen,
                Encoding encoding, SegmentFlags flag); 

   void GetAllResults(std::vector<std::string>* results) {
     result_.GetAllResults(results);
   }
   uint32 ResultCount() { return result_.ResultCount(); }
   bool ResultAt(uint32 index, std::string* result) {
     return result_.ResultAt(index, result);
   }

   SegmentResult* GetSegmentResult() { return &result_; }
  private:
   // return the word entry pointer, and move pos_after_word to
   // the char after the matched word
   uint32 NextMaxMatchWord(int *pos_after_word);

   // return just a gram
   uint32 NextGram(int *pos_after_word); 

   // get the hash code of current char, then move pos to the next
   // char, if pos >= inlen, return 0
   uint32 CharHash(int *next_pos);

   // seek the word entry index by word string
   uint32 SeekWordEntry(char* word, int len);

   bool DoChooseSecond(uint32 first, uint32 first_follow,
                       uint32 second, uint32 second_follow);

   int AppendAscii(char * word, int len, int chrcnt, int flag);

   int JoinWordEntry(int bpos, int count,int bname);

   int WordCountInPhrase(WordEntry* plm);
     
   // -1 error, 1 sucess, 0 ignore   
   bool ProcessAscii2(int begin_pos, int end_pos,
                     WordEntry* word_entry, int* new_pos, bool* ignore);
 
   bool ProcessAscii(int begin_pos, int end_pos,
                     WordEntry* word_entry, int* new_pos, bool* ignore);
   
   bool ProcessChineseNumber(int pos, int lpos, int* new_pos, bool* ignore);

   bool CombineNumberAndTime(); 

   bool DealHumanName();

   bool SecondIsBest(uint32* first_entry_index,
                     int* new_first_pos,
                     uint32* second_entry_index,
                     int* new_second_pos);
   WordDict* dict_;
   SegmentResult result_;

   const char* inbuf_;
   int inlen_;

   SegmentFlags flag_;
   Encoding encoding_;
};
} // end of namespace
