#include "basic_types.h"
#ifndef nlp_word_tag_common
#define nlp_word_tag_common
#include <string>
#include <vector>
#include "word_dict.h"
#include <map>

namespace nlp {
  enum WordTagType {
    CORE = 1,
    DISCARD,
  };

  typedef struct _WordTagInfo {
    std::string word;
    WordProperty property;
    WordTagType type;
  } WordTagInfo;

  
  enum WordClassForGoods {
  INVALID = 0,
  // 品牌 apple
  BRAND = 1,
  // 型号 MC505
  MODEL = 2,
  // 系列 MacBook air
  SERY = 3,
  // 规格 16G
  SPECIFICATION = 4,
  // 颜色
  COLOR = 5,
  // 产品
  PRODUCT = 6,
  // 款式 磨砂
  STYLE = 7,
  // 材质 金属
  MATERIAL = 8 ,
  // 风格 韩版
  MANNER = 9,
  // 人群 男
  TARGET = 10,
  FUNCTION = 11,

  HUMANNAME = 12,
  BOOKNAME = 13,

  };

enum GoodsClass {
  INVALIDCLASS = 0,
  DIGITAL = 1,
  COMPUTER = 2,
  ELECTRICS = 3,
  BEAUTY = 4,
  HOME = 5,
  SPORTS = 6,
  CLOTHING = 7,
  OLDCLASS = 8,
  CLASSEND = 9,
};

typedef struct _GoodInfo {
  std::vector<int> sim_core_product_vect;
  std::vector<std::string> keywords;
  std::vector<WordClassForGoods> word_class; 
  std::vector<double> weight;
  std::vector<bool> in_bracket;
  std::map<std::string, double> normal_weight;
  std::map<std::string, int> tf;
  std::vector<WordTagInfo> word_tag_vect;
  std::vector<WordClassForGoods> word_class_vect;

  int brand_index;
  int product_index; 
  int style_index;
} GoodInfo;


const char* GetWordClassName(WordClassForGoods word_class);
uint64 Mix32(uint32 int1, uint32 int2);

extern const int MAX_LINE; 

extern const char* raw_property_fn ;
extern const char* raw_brand_class_fn ;
extern const char* raw_standard_good_fn ; 
extern const char* raw_standard_good_etao ; 


extern const char* word_class_fn;
extern const char* brand_class_fn;
extern const char* standard_good_fn; 
extern const char* standard_good_etao; 
extern const char* cate_idf_fn; 

extern const char* brand_class_id_fn;
extern const char* brand_class_id_fn_new;
extern const char* new_brand_class_fn;
extern const char* discard_brand_fn;


//extern const char* new_product_class_fn
extern const char* synonym_fn;

extern char str_gb_number[10][3];

// for chongzi stragety
extern const double CZ_IMPROVE_RATE; 
extern const char* C1_CONGZHI; 

#define IsCharAlphaNumber(c) ((c) >= 'a' && (c) <= 'z' || \
                              (c) >= 'A' && (c) <= 'Z' || \
                              (c) >= '0' && (c) <= '9')
#define IsCharAlpha(c) ((c) >= 'a' && (c) <= 'z' || \
                        (c) >= 'A' && (c) <= 'Z')

#define IsCharNumber(c) ((c) >= '0' && (c) <= '9')
char* StripBlank(char* input);
bool IsAlphaNum(const char * pstr);
bool IsNum(const char * pstr);
bool IsRealNum(const char * pstr); 
bool IsGBNumber(const char * pstr);
bool IsAlpha(const char* pstr);
bool IsAlphaPlusNum(const char* pstr);
bool IsSpliter(std::string& str); 

void SplitString(const std::string& str,
                 const std::string& delim,
                 std::vector<std::string>* output);

void trim(char* str); 
} // end of namespace

#endif
