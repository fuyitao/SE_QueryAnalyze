#pragma once

#include "basic_types.h"
#include "dict.h"
#include <string>

namespace nlp {

// word property 
typedef struct _word_property {
  int32 high_property;
  int32 low_property;
} WordProperty;

// word entry of the dict
typedef struct _word_entry {
  unsigned type:3;
  unsigned weight:21;
  unsigned length:8;

  WordProperty property;

  union {
    // for static and dynmaic basic word, this point to the
    // the char* word_buffer
    uint32 basic_pos;
    // for static and dynamic phrase word, this point to the
    // phrase list
    uint32 phrase_pos;
  };
  uint32 sub_phrase_pos;
  uint32 prefix_pos;
  uint32 rule_pos;
} WordEntry;

// rule infomation
typedef struct _rule_info {
  // point to the rule_list
  uint32 suffix_pos;
  uint32 name_pos;
  uint32 fname_pos;
} RuleInfo;

// node of the trie tree
typedef struct _trie_node {
  uint32 value;
  // point the WorkEntry List
  uint32 word_entry_pos;
  uint32 children_pos;
} TrieNode;

const uint32 kMaxWordEntryLen = 256;
const uint32 kCommonNull = 0xFFFFFFFF;
const uint32 kEntryNull = 0xFFFFFFFF;
const uint32 kNodeFirst = 0xFFFFFFFF;
const uint32 kNodeNULL = 0xFFFFFFFF;

class WordDict {
 public:
   WordDict();
   virtual ~WordDict();

   bool LoadFromDir(std::string file_path);
   bool SaveToFile(std::string file_path);

   // Seek in the WorkEntry list
   WordEntry* GetWordEntry(uint32 index) {
     return entry_buffer_ + index;
   }

   // trie_node_index: index to the trie node list
   // return index to the WordEntry list
   uint32 GetEntryIndexByNode(uint32 trie_node_index) {
     TrieNode* node = node_buffer_ + trie_node_index;
     return node->word_entry_pos;
   }

   TrieNode* GetTrieNode(uint32 node_index) {
     return node_buffer_ + node_index;
   }

   // Follow the trie tree by hash, 
   // return the children node index
   uint32 NextTrieNode(uint32 last_trie_node, uint32 hash);

   uint32 TrieRoot() { return trie_root_; }

   // Read the phrase list value at pos
   uint32 PhraseInfo(uint32 pos) {
     return phrase_list_[pos];
   }

   // Seek WorkEntry for the word value
   WordEntry* SeekOneWordEntry(uint32 word_val);

   bool RuleChoose(WordEntry* first, WordEntry* second, uint32 follow);

   const char* GetWordString(uint32 word_index) {
     WordEntry* we = GetWordEntry(word_index);
     return word_buffer_ + we->basic_pos;
   }

   const char* GetWordString(WordEntry* entry) {
     return word_buffer_ + entry->basic_pos;
   }

  private:
   // store words 
   char* word_buffer_;
   uint32 word_buffer_size_;
   uint32 word_buffer_index_;

   // store trie nodes
   TrieNode* node_buffer_;
   uint32 node_buffer_size_;
   uint32 node_buffer_index_;

   // store word entries
   WordEntry* entry_buffer_;
   uint32 entry_buffer_size_;
   uint32 entry_buffer_index_;

   // store rules
   RuleInfo* rule_buffer_;
   uint32 rule_buffer_size_;
   uint32 rule_buffer_index_;

   int32* probility_buffer_;
   uint32 probility_buffer_size_;
   uint32 probility_buffer_index_;

   Dict* left_name_dict_;
   Dict* right_name_dict_;

   // |word number in phrase|word1|word2|...|wordn| 
   uint32* phrase_list_;
   uint32 phrase_list_size_;
   uint32 phrase_list_index_;

   // |children number of node| child node index |...|child node index|
   uint32* node_list_;
   uint32 node_list_size_;
   uint32 node_list_index_;

   // |rule size|ruleinfo_1|ruleinfo_2|...|ruleinfo_n|
   uint32* rule_list_;
   uint32 rule_list_size_;
   uint32 rule_list_index_; 

   // root node of the trie tree, point to the node_list
   uint32 trie_root_;

   uint32 dict_type_;
};

} // end of namespace
