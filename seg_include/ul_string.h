/**
 * @file
 * @brief 字符及字符串处理
 */

/* Description:
 *   These are functions used in string operation.
 *
 * Author: Cui Shanshan
 *         scui@baidu.com
 */
#ifndef _UL_MODULE_STRING_
#define _UL_MODULE_STRING_

extern char legal_char_set[256];
extern char url_eng_set[256];
extern char legal_word_set[256];
#define PATH_SIZE 256
extern char work_path[PATH_SIZE];

/**
 *  从字符串中取出第一个单词，并返回下一个单词的位置
 *  
 *  @param[in]  ps_src    源字符串
 *  @param[in]  ps_result 得到的单词
 *  @param[in]  charset   转换使用的矩阵
 *  @param[out] 无
 *  @return 下一个单词的位置
 */
char *ul_sgetw(char *ps_src, char *ps_result, char *charset);

/**
 *  从字符串中取出第一个单词，并返回下一个单词的位置，支持双字节编码
 *  
 *  @param[in]  ps_src    源字符串
 *  @param[in]  ps_result 得到的单词
 *  @param[in]  charset   转换使用的矩阵
 *  @param[out] 无
 *  @return 下一个字符串的位置
 */             
char *ul_sgetw_ana(char *ps_src, char *ps_result, char *charset);    

 
/**
 *  不区分大小写字符串比较(利用map实现)
 *  
 *  @param[in]  s1 字符串1 
 *  @param[in]  s2 字符串2
 *  @param[in]  n  待比较长度
 *  @param[out] 无
 *  @return 是否相等
 * - 1 相等
 * - 0 不相等
 */
int ul_strncasecmp(const char *s1,const char *s2, size_t n);

#endif

   
