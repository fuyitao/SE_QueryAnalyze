#pragma once

#include <string>
#include "basic_types.h"

namespace nlp {

typedef struct _SearchEntry {
  uint64 key;
  int32 code;
  uint32 value;
} SearchEntry;

typedef struct _DictEntry {
  uint64 key;
  int32 code;
  uint32 value;
  struct _DictEntry* next;

  void Copy(const SearchEntry& se) {
    key = se.key;
    code = se.code;
    value = se.value;
    next = NULL;
  }

  void CopyValue(const SearchEntry& se) {
    key = se.key;
    code = se.code;
    value = se.value;
  }
} DictEntry;

const uint32 kBlockSize = 1 << 16;

typedef struct _DictEntryBlock {
  DictEntry nodes[kBlockSize];
  struct _DictEntryBlock* next;
} DictEntryBlock;

// Can seek and modify dict, can not delete
class Dict {
 public:
  Dict();
  virtual ~Dict();

  bool LoadFromFile(std::string file_path);
  bool SaveToFile(std::string file_path);

  bool Modify(SearchEntry* to_modify);
  bool Seek(SearchEntry* to_seek);

 private:
  // hash entry num
  uint32 dict_entry_num_;
  // dict node num
  uint32 node_num_;
  uint32 current_code_;
  
  uint32 *offset_list_; 
  uint32 *node_num_list_;
  SearchEntry* dict_entry_list_;
};

class DictBuilder {
 public:
  DictBuilder();
  
  DictBuilder(uint32 entry_num, int32 current_code = 0);
  virtual ~DictBuilder();

  // renew it like just create by <entry_num, current_code>
  bool Renew();
  // adjust the hash entry, to improve seek performance
  bool Adjust();

  bool SaveToFile(std::string file_path);
  bool LoadFromFile(std::string file_path);

  // Dict Entry operation
  bool Add(SearchEntry* to_add);
  bool Modify(SearchEntry* to_modify);
  bool Seek(SearchEntry* to_seek);
  // Not really delete it ,just make the node.code = -1
  bool Delete(SearchEntry* to_delete);

 private:
  DictEntry ** dict_entry_;
  uint32 dict_entry_num_;
  uint32 node_num_;
  uint32 current_code_;

  // Dict entry buffer, it is a single link
  DictEntryBlock *first_block_;
  DictEntryBlock *current_block_;
  DictEntry* current_node_;
  uint32 node_avail_;
};

} // end of namespace
