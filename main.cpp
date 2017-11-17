#include "QueryPreprocess.h"
#include "Synonym_Termweight.h"
#include <iostream>
using namespace std;

void Output(PreproType& preStruct, TermweightType& termStruct);
string path = "../dict/queryAnalyze_dict/";

int main(){
	// 分词工具初始化
	string word_dictFile = path + "seg_dict/";
	word_segment_init(word_dictFile.c_str());

	// 字典
	string synNtoNFile  = path + "Synonym_NtoNResult";
	string syn1toNFile  = path + "Synonym_1toNResult";
	string stopwordFile = path + "stopwords.txt";
	string id_sourcenameFile = path + "xihuan_id_sourcename";
	string termweightFile = path + "xihuan_idf";

	// 结构体
	PreproType preStruct;       // 预处理结构体
	TermweightType termStruct;  // term结构体(同义词、结构体)

	// 类对象
	QueryPreprocess queryPre(id_sourcenameFile);
	SynonymTermweight queryTerm(synNtoNFile, syn1toNFile, stopwordFile, termweightFile);

	string query;
	while (1){
		cerr << "query:";
		getline(cin, query);
		if (query == "-1") break;

		queryPre.Preprocess(query, "basic", preStruct);
		queryTerm.GetTermList(preStruct, termStruct);

		// output
		Output(preStruct, termStruct);
	}

	return 0;
}

void Output(PreproType& preStruct, TermweightType& termStruct){
	// preStruct
	string segline = "";
	for (int i = 0; i < (int)preStruct.pre_segVec.size(); ++i){
		segline += preStruct.pre_segVec[i] + " ";
	}
	// termStruct
	string weightStr;
	string term;
	stringstream css;
	for (int i = 0; i < (int)termStruct.termweightVec.size(); ++i){
		term = termStruct.termweightVec[i].first;
		css.str("");
		css << termStruct.termweightVec[i].second;
		if (i == 0) weightStr = term + ":" + css.str();
		else weightStr += "\n	    " + term + ":" + css.str();
	}

	// output
	cout << "segline    :" << segline << endl;
	cout << "termline   :" << termStruct.termStr << endl;
	cout << "sourcename :" << preStruct.sourcename << endl;
	cout << "weightline :" << weightStr << endl;
}
