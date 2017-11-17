#include "tool_function.h"

// 字符串分割
void splitString(const string& src, string sep_char, vector<string>& sep_vec){
	sep_vec.clear();
	int sep_charLen = sep_char.size();
	int lastPos = 0, index = -1;
	string word;
	while (-1 != (index = src.find(sep_char, lastPos))){
		word = src.substr(lastPos, index-lastPos);
		if ( !word.empty() ) sep_vec.push_back(word);
		lastPos = index + sep_charLen;
	}
	string lastString = src.substr(lastPos);  // 截取最后一个分隔符后的内容
	if ( !lastString.empty() ) sep_vec.push_back(lastString);
	return;
} // splitString
