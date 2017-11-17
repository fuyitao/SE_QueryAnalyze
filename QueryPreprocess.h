#ifndef _QUERYPREPROCESS__h
#define _QUERYPREPROCESS__h

/*
 * @ Name    : QueryPreprocess
 * @ Autho   : fuyitao
 * @ Version : 4.0
 * @ Date    : 2017.8.8
 */

// 头文件
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include "utf8_to_char.h"
#include "tool_function.h"
#include "word_segment.h"
using namespace std;

#define unset unordered_set

typedef struct PreproType{
	vector<string> pre_segVec;  // 分词结果
	int pre_segMode;            // 粗细粒度
	string sourcename;          // 来源
} PreproType;

class QueryPreprocess{
public:
	QueryPreprocess(string r_id_sourcenameFile);
	~QueryPreprocess();
	void Preprocess(string r_query, string r_segMode, PreproType& r_preStruct);  // query预处理
private:
	unset<string> m_sourcenameSet;  // 来源词字典

	void GetMap(string r_id_sourcenameFile);  // 获取字典
	string Space_Process(string r_query);  // 空格处理
	string Get_Sourcename(vector<string>& r_segVec);  // 获取query来源
};

#endif
