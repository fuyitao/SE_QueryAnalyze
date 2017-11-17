#include "QueryPreprocess.h"

QueryPreprocess::QueryPreprocess(string r_id_sourcenameFile){
	GetMap(r_id_sourcenameFile);
} // QueryPreprocess

QueryPreprocess::~QueryPreprocess(){
} // ~QueryPreprocess

/************************************************
 * Function    : Preprocess(主函数)
 * Description : 对query预处理，分词、空格处理
 * Date        : 2017.8.8
 ***********************************************/
void QueryPreprocess::Preprocess(string r_query, string r_segMode, PreproType& r_preStruct){
	r_preStruct.pre_segVec.clear();  // 初始化
	r_preStruct.sourcename = "";     // 初始化
	if (r_query == "") return;

	// 预处理
	string newquery;

	int len = clean_utf8((char*)r_query.c_str());  // 字符串清洗
	newquery = r_query.substr(0, len);
	transform(newquery.begin(), newquery.end(), newquery.begin(), ::tolower);  // 转小写
	newquery = Space_Process(newquery);  // 空格处理

	// 分词(0:粗粒度(不保留标点)、1:粗粒度(保留标点)、2:细粒度(不保留标点)、3:细粒度(保留标点))
	if (r_segMode == "basic") r_preStruct.pre_segMode = 0;  // 粗粒度
	else r_preStruct.pre_segMode = 2;              // 细粒度

	segment_inside(newquery, r_preStruct.pre_segVec, r_preStruct.pre_segMode);  // 分词

	r_preStruct.sourcename = Get_Sourcename(r_preStruct.pre_segVec);  // 获取来源

	return;
} // Preprocess

/************************************************
 * Function    : GetMap
 * Description : 获取字典
 * Date        : 2017.9.1
 ***********************************************/
void QueryPreprocess::GetMap(string r_id_sourcenameFile){
	string strline;
	string sourcename;
	vector<string> word_vec;

	ifstream fpin_idsource(r_id_sourcenameFile.c_str());
	if ( !fpin_idsource ){
		cerr << "id 来源字典读取错误!" << endl;
		fpin_idsource.close();
		exit(0);
	}
	while (getline(fpin_idsource, strline)){
		transform(strline.begin(), strline.end(), strline.begin(), ::tolower);  // 转小写
		word_vec.clear();
		splitString(strline, "\t", word_vec);
		sourcename = word_vec[1];
		if (sourcename == "") continue;

		m_sourcenameSet.insert(sourcename); // 插入来源词
	} // end while(getline)

	fpin_idsource.close();
	return;
} // GetMap

/************************************************
 * Function    : Space_Process
 * Description : 对query的空格处理(连续空格变一个、前后连续空格删除)
 * Date        : 2017.8.8
 ***********************************************/
string QueryPreprocess::Space_Process(string r_query){
	string newquery = "";
	// 连续空格变一个
	vector<string> wordVec;
	int i;
	splitString(r_query, " ", wordVec);
	for (i = 0; i < (int)wordVec.size()-1; ++i) newquery += wordVec[i] + " ";
	newquery += wordVec[i];

	// 前后连续空格删除
	int it, beg, end;
	for (it = 0; it < (int)newquery.length(); ++it) if (newquery[it] != ' ') break;
	beg = it;
	for (it = (int)newquery.length()-1; it >= 0; --it) if (newquery[it] != ' ') break;
	end   = it;

	newquery = newquery.substr(beg, end-beg+1);

	return newquery;
} // Space_Process

/************************************************
 * Function    : Get_Sourcename
 * Description : 获取query来源
 * Date        : 2017.9.1
 ***********************************************/
string QueryPreprocess::Get_Sourcename(vector<string>& r_segVec){
	string sourcename = "";
	string phrase;
	vector<string> phraseVec;

	// 以最长串判断是否为来源词，依次减少
	for (int i = 0; i < (int)r_segVec.size(); ++i){
		phrase = "";
		phraseVec.clear();
		for (int j = i; j < (int)r_segVec.size(); ++j){
			phrase += r_segVec[j];
			phraseVec.insert(phraseVec.begin(), phrase);
		} // end for(j)
		for (int t = 0; t < (int)phraseVec.size(); ++t){
			if (m_sourcenameSet.find(phraseVec[t]) != m_sourcenameSet.end()){
				sourcename = phraseVec[t];
				break;
			}
		} // end for(t)
		if (sourcename != "") break;
	} // end for(i)

	return sourcename;
} // Get_Sourcename
