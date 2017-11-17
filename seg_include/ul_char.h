/**
 * @file
 * @brief �ַ�������
 */

#ifndef __UL_CHAR_H_
#define __UL_CHAR_H_
extern int UL_CHAR_SPACE[];
/**
 *  ���ַ����еĴ�д��ĸת��ΪСд��ĸ
 *  
 *  @param[in]  pstr ��ת�����ַ���
 *  @param[out] pstr ת������ַ���
 *  @return ���ش�����
 *  - 0 ��ʾת��ʧ��
 *  - 1 ��ʾת���ɹ�
 *  @note �������ת��gbk�ַ���,gbk���ʿ��ܱ��޸�,����,�������ĸ���ul_trans2lower
 */
 
int ul_tolowerstr_singlebuf(unsigned char *pstr);

 
/**
 *  ����д��ĸת��ΪСд��ĸ���Ǵ�д��ĸ�򷵻���ĸ����
 *  
 *  @param[in]  srcchar ��ת�����ַ�
 *  @param[out] ��
 *  @return ����ת������ַ�
 */
int ul_tolower(unsigned char srcchar);

/**
 *  ���ַ����еĴ�д��ĸת��ΪСд������ת�����\n
 *  �ַ�����ŵ�dststr�У�srcstr���ֲ���
 *  
 *  @param[in]  srcstr ��ת�����ַ���
 *  @param[in]  dststr ���ת������ַ����Ļ�����
 *  @param[out] dststr ת������ַ���
 *  @return ���ش�����
 *  - 0 ��ʾת��ʧ��
 *  - 1 ��ʾת���ɹ�
 *  @note ע��dststr�Ĵ�С>=strlen(srcstr)+1
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
 *  �жϸ������ַ��Ƿ�Ϊ�ո�\n
 *  �ַ�����ŵ�dststr�У�srcstr���ֲ���
 *  
 *  @param[in]  ch �������ַ�
 *  @return �����жϽ��
 *  - 0 ��ʾ���ǿո�
 *  - 1 ��ʾ�ǿո�
 *  @note ע��space�ַ�����'\0',���뺯��isspace��ͬ
 */ 
#define ul_isspace(ch) UL_CHAR_SPACE[(unsigned char)(ch)]
#endif
