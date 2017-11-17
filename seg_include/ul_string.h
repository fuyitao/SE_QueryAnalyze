/**
 * @file
 * @brief �ַ����ַ�������
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
 *  ���ַ�����ȡ����һ�����ʣ���������һ�����ʵ�λ��
 *  
 *  @param[in]  ps_src    Դ�ַ���
 *  @param[in]  ps_result �õ��ĵ���
 *  @param[in]  charset   ת��ʹ�õľ���
 *  @param[out] ��
 *  @return ��һ�����ʵ�λ��
 */
char *ul_sgetw(char *ps_src, char *ps_result, char *charset);

/**
 *  ���ַ�����ȡ����һ�����ʣ���������һ�����ʵ�λ�ã�֧��˫�ֽڱ���
 *  
 *  @param[in]  ps_src    Դ�ַ���
 *  @param[in]  ps_result �õ��ĵ���
 *  @param[in]  charset   ת��ʹ�õľ���
 *  @param[out] ��
 *  @return ��һ���ַ�����λ��
 */             
char *ul_sgetw_ana(char *ps_src, char *ps_result, char *charset);    

 
/**
 *  �����ִ�Сд�ַ����Ƚ�(����mapʵ��)
 *  
 *  @param[in]  s1 �ַ���1 
 *  @param[in]  s2 �ַ���2
 *  @param[in]  n  ���Ƚϳ���
 *  @param[out] ��
 *  @return �Ƿ����
 * - 1 ���
 * - 0 �����
 */
int ul_strncasecmp(const char *s1,const char *s2, size_t n);

#endif

   
