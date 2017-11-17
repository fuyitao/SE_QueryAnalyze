/**
 * @file
 * @brief 字符串操作
 */

#ifndef __UL_CHAR_H_
#define __UL_CHAR_H_
extern int UL_CHAR_SPACE[];
/**
 *  将字符串中的大写字母转换为小写字母
 *  
 *  @param[in]  pstr 待转换的字符串
 *  @param[out] pstr 转换后的字符串
 *  @return 返回处理结果
 *  - 0 表示转换失败
 *  - 1 表示转换成功
 *  @note 如果用来转换gbk字符串,gbk单词可能被修改,慎用,建议中文改用ul_trans2lower
 */
 
int ul_tolowerstr_singlebuf(unsigned char *pstr);

 
/**
 *  将大写字母转换为小写字母，非大写字母则返回字母本身
 *  
 *  @param[in]  srcchar 待转换的字符
 *  @param[out] 无
 *  @return 返回转换后的字符
 */
int ul_tolower(unsigned char srcchar);

/**
 *  将字符串中的大写字母转换为小写，并将转换后的\n
 *  字符串存放到dststr中，srcstr保持不变
 *  
 *  @param[in]  srcstr 待转换的字符串
 *  @param[in]  dststr 存放转换后的字符串的缓冲区
 *  @param[out] dststr 转换后的字符串
 *  @return 返回处理结果
 *  - 0 表示转换失败
 *  - 1 表示转换成功
 *  @note 注意dststr的大小>=strlen(srcstr)+1
 */ 
int ul_tolowerstr(unsigned char *dststr,unsigned char *srcstr);

/**************************************************************************
 * function : check the char is  space or not
 * argu-in  : ch, the unsigned char
 * return   : 1 if yes, 0 if not
 * NOTICE   : the space chars inclde '\0', it is different as isspace.
 *          : BE CAREFUL
 **************************************************************************/
 
 
/**
 *  判断给定的字符是否为空格\n
 *  字符串存放到dststr中，srcstr保持不变
 *  
 *  @param[in]  ch 待检测的字符
 *  @return 返回判断结果
 *  - 0 表示不是空格
 *  - 1 表示是空格
 *  @note 注意space字符包括'\0',这与函数isspace不同
 */ 
#define ul_isspace(ch) UL_CHAR_SPACE[(unsigned char)(ch)]
#endif
