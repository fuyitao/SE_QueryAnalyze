#ifndef _WORDSEGMENT__h
#define _WORDSEGMENT__h

#include <string>
#include <vector>

#include "seg_include/word_dict.h"
#include "seg_include/segmenter.h"
#include "seg_include/ul_ccode.h"
#include "seg_include/TransCode.h"
using namespace std;

void word_segment_init(const char* word_dict_path);
string segment_inside(string r_segline, vector<string>& r_segmentVec, int r_mode);  // 内部调用分词工具

#endif
