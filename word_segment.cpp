#include "word_segment.h"

static nlp::WordDict * wd;
static nlp::Segmenter * segmenter;

// 分词初始化
void word_segment_init(const char* word_dict_path){
	wd = new nlp::WordDict();
	wd->LoadFromDir(word_dict_path);
	ul_ccode_load((char *)word_dict_path);
	segmenter = new nlp::Segmenter(wd);
}

// 调用内部分词工具
string segment_inside(string r_segline, vector<string>& r_segmentVec, int r_mode){
	string input;
	char change_input[102400];
	ul_trans2gb((char *)r_segline.c_str(), change_input, CODETYPE_UTF8);
	input = change_input;
	ul_trans2lower(input.c_str(), change_input);
	input = change_input;

	segmenter->Segment(input.c_str(), input.size(), nlp::GBK, nlp::ALL);  // 分词

	string segmentline = "";
	char utfbuf[10240] = "";
	int len;
	vector<string> all_results;
	for (uint32 i = 0; i < segmenter->ResultCount(); ++i){
		std::string word;
		segmenter->ResultAt(i, &word);
		all_results.clear();
		segmenter->GetSegmentResult()->GetPhraseTerms(i, &all_results);  // 细粒度结果获取

		if (r_mode % 2 == 0 && (segmenter->GetSegmentResult()->IsMark(i) || word == " ")){  // r_mode == 0/2 时不保留标点符号
			continue;
		}else if ((r_mode == 2 || r_mode == 3) && all_results.size() > 0){  // 细粒度
			for (uint32 j = 0; j < (uint32)all_results.size(); ++j){
				strcpy(utfbuf, "");
				len = g2u((char *)all_results[j].c_str(), (int)all_results[j].size(), utfbuf, (int)10240);
				if (len == -1)return "";
				word = utfbuf;
				segmentline += word;
				r_segmentVec.push_back(word);
			}
		}else{  // 粗粒度
			strcpy(utfbuf, "");
			len = g2u((char *)word.c_str(), (int)word.size(), utfbuf, (int)10240);
			if (len == -1) return "";
			word = utfbuf;
			segmentline += word;
			r_segmentVec.push_back(word);
		}

	}

	return segmentline;
}
