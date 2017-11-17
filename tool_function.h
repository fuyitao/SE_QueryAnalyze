#ifndef _TOOLFUNCTION__h
#define _TOOLFUNCTION__h

#include <string>
#include <vector>
using namespace std;

struct CmpByStrValue{
	bool operator()(const pair<string, double> &lhs, const pair<string, double> &rhs){
		return lhs.second > rhs.second;
	}
};

struct CmpByIntValue{
	bool operator()(const pair<int, double> &lhs, const pair<int, double> &rhs){
		return lhs.second > rhs.second;
	}
};

void splitString(const string& src, string seg_char, vector<string>& sep_vec);  // 字符串按sep_char分割

#endif
