#include "Synonym_Termweight.h"

SynonymTermweight::SynonymTermweight(string r_synNtoNFile, string r_syn1toNFile,
									string r_stopwordFile, string r_termweightFile){
	m_synonym_maxlen = 0;
	m_syn_num_maxlen = 5;
	GetMap(r_synNtoNFile, r_syn1toNFile, r_stopwordFile, r_termweightFile);
	cout << "weight:" << m_termweight_map.size() << "|" << endl;
} // SynonymTermweight

SynonymTermweight::~SynonymTermweight(){
} // ~SynonymTermweight

/************************************************
 * Function    : GetTermList(主函数)
 * Description : 对分词结果进行同义词替换、term权重生成
 * Date        : 2017.8.9
 ***********************************************/
void SynonymTermweight::GetTermList(PreproType& r_preStruct, TermweightType& r_termStruct){
	r_termStruct.syn_termVec.clear();    // 初始化
	r_termStruct.termweightVec.clear();  // 初始化
	r_termStruct.termStr = "";          // 初始化
	if ( (int)r_preStruct.pre_segVec.size() == 0 ) return;

	GetSynonymList(r_preStruct.pre_segVec, 
					r_preStruct.pre_segMode,
					r_termStruct.syn_termVec);                            // 生成同义词列表
	r_termStruct.termStr = MergeString(r_termStruct.syn_termVec);         // 生成输出字符串
	GetTermweight(r_termStruct.syn_termVec, r_termStruct.termweightVec);  // 生成term权重

	return;
} // GetTermList

/************************************************
 * Function    : GetMap
 * Description : 获取所有需要的字典
 * Date        : 2017.8.9
 ***********************************************/
void SynonymTermweight::GetMap(string r_synNtoNFile, string r_syn1toNFile,
							string r_stopwordFile, string r_termweightFile){
	string strline, word;
	vector<string> wordVec;
	int len;

	// 同义词互译字典，m_synonm_NtoN_map
	ifstream fpin_synNtoN(r_synNtoNFile.c_str());
	if ( !fpin_synNtoN ){
		cerr << "同义词互译字典读取错误!" << endl;
		fpin_synNtoN.close();
		exit(0);
	}
	while (getline(fpin_synNtoN, strline)){
		transform(strline.begin(), strline.end(), strline.begin(), ::tolower);  // 转小写
		wordVec.clear();
		splitString(strline, "|", wordVec);  // 字符串切割
		// 放入字典，并获取最大长度
		for (int i = 0; i < (int)wordVec.size(); ++i){
			word = wordVec[i];
			if (word == "") continue;
			len = utf8_to_len(word);
			if (len > m_synonym_maxlen) m_synonym_maxlen = len;  // 最大长度
			// 放字典
			for (int j = 0; j < (int)wordVec.size(); ++j){
				if (i == j || wordVec[j] == "") continue;
				m_synonym_NtoN_map[word].insert(wordVec[j]);
			} // end for(j)
		} // end for(i)
	} // end while
	fpin_synNtoN.close();
	//---------------------------------------

	// 同义词一对多字典, m_synonm_1toN_map
	ifstream fpin_syn1toN(r_syn1toNFile.c_str());
	if ( !fpin_syn1toN ){
		cerr << "同义词一对多字典读取错误!" << endl;
		fpin_syn1toN.close();
		exit(0);
	}
	while (getline(fpin_syn1toN, strline)){
		transform(strline.begin(), strline.end(), strline.begin(), ::tolower);  // 转小写
		wordVec.clear();
		splitString(strline, "|", wordVec);  // 字符串分割
		if (wordVec.size() < 2) continue;
		word = wordVec[0];
		if (word == "") continue;
		len = utf8_to_len(word);
		if (len > m_synonym_maxlen) m_synonym_maxlen = len;  // 最大长度
		for (int i = 1; i < (int)wordVec.size(); ++i){
			if (wordVec[i] == "") continue;
			m_synonym_1toN_map[word].insert(wordVec[i]);
		} // end for(i)
	} // end while
	fpin_syn1toN.close();
	//---------------------------------------

	// 停用词字典，m_stopword_set
	ifstream fpin_stop(r_stopwordFile.c_str());
	if ( !fpin_stop ){
		cerr << "停用词字典读取错误!" << endl;
		fpin_stop.close();
		exit(0);
	}
	while (getline(fpin_stop, strline)){
		transform(strline.begin(), strline.end(), strline.begin(), ::tolower);  // 转小写
		if (strline == "") continue;
		m_stopword_set.insert(strline);
	} // end while
	fpin_stop.close();
	//---------------------------------------
	
	// term权重字典，m_termweight_map
	ifstream fpin_weight(r_termweightFile.c_str());
	if ( !fpin_weight ){
		cerr << "term权重字典读取错误!" << endl;
		fpin_weight.close();
		exit(0);
	}
	while (getline(fpin_weight, strline)){
		transform(strline.begin(), strline.end(), strline.begin(), ::tolower);  // 转小写
		if (strline == "") continue;
		wordVec.clear();
		splitString(strline, "\t", wordVec);
		if (wordVec.size() != 2) continue;
		if (wordVec[0] == "" || wordVec[1] == "") continue;
		m_termweight_map[wordVec[0]] = atof(wordVec[1].c_str());
	}
	fpin_weight.close();
	//---------------------------------------
	
	return;
} // GetMap

/************************************************
 * Function    : GetSynonymList
 * Description : 生成同义词列表
 * Date        : 2017.8.9
 ***********************************************/
void SynonymTermweight::GetSynonymList(vector<string>& r_segVec, int r_segMode, vector< vector<string> >& r_syntermVec){
	unset<string>::iterator it_set;
	string phrase = "";
	string segline;
	vector<string> segVec;
	int i;
	for (i = 0; i < (int)r_segVec.size(); ++i) phrase += r_segVec[i];

	// 一对多同义词
	if (m_synonym_1toN_map.find(phrase) != m_synonym_1toN_map.end()){
		
		vector<string> tmpVec;
		segline = SegString(phrase, r_segMode);
		if (segline != "") tmpVec.push_back(segline);  // 原phrase
		for (it_set = m_synonym_1toN_map[phrase].begin(); it_set != m_synonym_1toN_map[phrase].end(); ++it_set){
			segline = SegString(phrase, r_segMode);
			if (segline != "") tmpVec.push_back(segline);  // 同义词
		} // end for(it_set)
		r_syntermVec.push_back(tmpVec);
		return;
	}

	// 互译同义词
	int beg = 0;
	int local, len;
	vector<string> phraseVec;
	unset<string> wordSet;  // 判断term中是否重复
	bool judge;
	while (beg < (int)r_segVec.size()){
		judge  = true;
		phrase = "";
		phraseVec.clear();
		vector<string> tmpVec;
		for (local = beg; local < (int)r_segVec.size(); ++local){ // 获取短语
			phrase += r_segVec[local];
			len = utf8_to_len(phrase);
			if (len > m_synonym_maxlen) break;  // 大于同义词最大长度，退出
			phraseVec.push_back(phrase);
		} // end for(local)

		for (i = (int)phraseVec.size()-1; i >= 0; --i){ // 从最长的phrase找同义词
			phrase = phraseVec[i];
			if (m_synonym_NtoN_map.find(phrase) != m_synonym_NtoN_map.end() &&
				m_stopword_set.find(phrase) == m_stopword_set.end()){  // 找到同义词(并且不是停用词)
				beg += i;
				judge = false;
				if (wordSet.find(phrase) != wordSet.end()) break; // 若phrase与之前term重复，不放入
				wordSet.insert(phrase);
				segline = SegString(phrase, r_segMode);
				if (segline != "") tmpVec.push_back(segline);  // 原phrase
				for (it_set = m_synonym_NtoN_map[phrase].begin(); it_set != m_synonym_NtoN_map[phrase].end(); ++it_set){
					if (wordSet.find(*it_set) != wordSet.end()) continue; // 若同义词与之前term重复，不放入
					wordSet.insert(*it_set);
					string segline = SegString(*it_set, r_segMode);
					if (segline != "") tmpVec.push_back(segline);  // 同义词
				} // end for(it_set)
				r_syntermVec.push_back(tmpVec);
				break;
			}
		} // end for(i)
		if ( judge && m_stopword_set.find(r_segVec[beg]) == m_stopword_set.end() ){
			tmpVec.push_back(r_segVec[beg]);
			r_syntermVec.push_back(tmpVec);
		}
		++beg;
	} // end while

	return;
} // GetSynonyList

/************************************************
 * Function    : GetTermweight
 * Description : 生成term权重
 * Date        : 2017.8.9
 ***********************************************/
void SynonymTermweight::GetTermweight(vector< vector<string> >& r_syntermVec,
									vector< pair<string, double> >& r_termweightVec){
	string term;
	vector<string> word_vec;
	for (int i = 0; i < (int)r_syntermVec.size(); ++i){
		for (int j = 0; j < (int)r_syntermVec[i].size(); ++j){
			term = r_syntermVec[i][j];
			word_vec.clear();
			splitString(term, " ", word_vec);
			for (int t = 0; t < (int)word_vec.size(); ++t){
				r_termweightVec.push_back(make_pair(word_vec[t], m_termweight_map[word_vec[t]]));
			}
		} // end for(j)
	} // end for(i)
	return;
} // GetTermweight

/************************************************
 * Function    : SegString
 * Description : 对字符串分词，并用字符连接
 * Date        : 2017.8.9
 ***********************************************/
string SynonymTermweight::SegString(string r_str, int r_segMode){
	vector<string> segVec;
	string segline = "";

	segment_inside(r_str, segVec, r_segMode);  // 分词
	if (segVec.size() == 0) return segline;
	segline = segVec[0];
	for (int i = 1; i < (int)segVec.size(); ++i) segline += " " + segVec[i];

	return segline;
} // SegString

/************************************************
 * Function    : MergeString
 * Description : 合并同义term为一个字符串(AND OR)
 * Date        : 2017.8.9
 ***********************************************/
string SynonymTermweight::MergeString(vector< vector<string> >& r_syntermVec){
	stringstream mergeStr;
	for (int i = 0; i < (int)r_syntermVec.size(); ++i){
		if (i == 0) mergeStr << "((";
		else mergeStr << " AND ((";
		for (int j = 0; j < (int)r_syntermVec[i].size(); ++j){
			if (j == 0) mergeStr << r_syntermVec[i][j];
			else mergeStr << ") OR (" << r_syntermVec[i][j];
		} // end for(j)
		mergeStr << "))";
	} // end for(i)

	return mergeStr.str();
} // MergeString
