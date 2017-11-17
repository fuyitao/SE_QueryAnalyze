#ifndef _SYNONYMTERMWEIGHT__h
#define _SYNONYMTERMWEIGHT__h

/*
 * @ Name    : Synonym_Termweight
 * @ Author  : fuyitao
 * @ Version : 3.0
 * @ Date    : 2017.8.9
 */

// 头文件
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "QueryPreprocess.h"
#include "utf8_to_char.h"
#include "word_segment.h"
#include "tool_function.h"
using namespace std;

#define unmap unordered_map
#define unset unordered_set

typedef struct TermweightType{
	vector< vector<string> > syn_termVec;  // 同义词vector
	vector< pair<string, double> > termweightVec;  // term权重vector
	string termStr;  // 合并输出结果字符串
} SynonymType;

class SynonymTermweight{
public:
	SynonymTermweight(string r_synNtoNFile, string r_syn1toNFile,
					string r_stopwordFile, string r_termweightFile);
	~SynonymTermweight();
	void GetTermList(PreproType& r_preStruct, TermweightType& r_termStruct);  // query同义词替换
private:
	unmap<string, unset<string> > m_synonym_NtoN_map;  // 同义词互译字典
	unmap<string, unset<string> > m_synonym_1toN_map;  // 同义词一对多字典
	int m_synonym_maxlen;                              // 同义词最大长度
	int m_syn_num_maxlen;                              // 同义词的最大数量
	unset<string> m_stopword_set;  // 停用词字典
	unmap<string, double> m_termweight_map;  // term权重字典

	void GetMap(string r_synNtoNFile, string r_syn1toNFile,
				string r_stopwordFile, string r_termweightFile);  // 获取字典
	void GetSynonymList(vector<string>& r_segVec, int r_segMode, vector< vector<string> >& r_syntermVec);  // 获取同义词列表
	void GetTermweight(vector< vector<string> >& r_syntermVec,
					vector< pair<string, double> >& r_termweightVec);  // 获取term权重
	string SegString(string r_str, int r_segMode);  // 分词字符串
	string MergeString(vector< vector<string> >& r_syntermVec );  // 合并成输出的字符串
};

#endif
