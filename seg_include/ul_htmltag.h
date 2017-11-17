/**
 * @file
 * @brief ������ҳ�е�tag
 */
/********************************************************************
 * Baidu Copyright. All rights reserved.
 * Filename    : $Id: ul_htmltag.h,v 1.3 2007/02/09 10:09:53 wangjp2 Exp $
 * Author      : $Author: wangjp2 $
 * Create Date : 
 * Description : Some functions used for frame composition
 * Recently Update : $Date: 2007/02/09 10:09:53 $
 * Version     : $Revision: 1.3 $
 * Update log list here : 
 * $Log: ul_htmltag.h,v $
 * Revision 1.3  2007/02/09 10:09:53  wangjp2
 * doxygen�ĵ��ع�
 *
 * Revision 1.2.12.1  2007/01/31 03:45:20  wangjp2
 * doxygen�ĵ��ع�cvs
 *
 * Revision 1.2  2006/08/09 11:50:40  qiuzd
 * �޸Ĵ��룬��֧��32λ/64λ����
 *
 * Revision 1.1  2003/08/04 02:48:46  chenjk
 * Add htmltag to ulib.
 *
 * Revision 1.3  2003/03/06 10:20:02  chenjk
 * Finish the functions.
 *
 * Revision 1.2  2003/03/06 01:52:14  chenjk
 * The work at home.
 *
 * Revision 1.1  2003/03/05 09:53:33  chenjk
 * Work backup for 2003-03-05.
 *
 ********************************************************************/         

#ifndef __UL_HTMLTAG_H_
#define __UL_HTMLTAG_H_

#define MAX_NVNAME_LEN               256
#define MAX_NVVALUE_LEN              1024
#define MAX_TAG_LEN                  256
#define MAX_NVCOUNT_IN_TAG           64

/* tag status defined here */
#define TAG_NVSTATUS_OK              0
#define TAG_NVSTATUS_ONLYNAME        1
#define TAG_NVSTATUS_LONGVALUE       2
#define TAG_NVSTATUS_TRUNCATEDNAME   4

/* the name-value pair in tag */
typedef struct HTMLTAG_NAMEVALUE_T
{
    int m_status;      // the tag status, see constant defination
    char m_name[MAX_NVNAME_LEN];  // the name of nvpair
    char m_value[MAX_NVVALUE_LEN]; // the value of the nvpair
}ul_nvpair_t;

typedef struct HTMLTAG_INFO_T
{
    char m_tagname[MAX_TAG_LEN];  // the name of the tag
    int  m_nvcount;    // the name-value pair count in this tag
    ul_nvpair_t m_nvlist[MAX_NVCOUNT_IN_TAG]; // the name-value pair list
}ul_taginfo_t;

/**
 *  ��������ҳ��tag��name-value�ԣ��洢��ul_taginfo_t�ṹ��
 *  
 *  @param[in]  piece    tag����ʼ��λ��(start behind the '<', not include the '<')
 *  @param[in]  ptaginfo �洢tag�ṹ�ĵ�ַ
 *  @param[out] ptaginfo ���tag��name-value�Ľṹ
 *  @param[out] pend     ��ǰtag�������λ��(the remainder string after the tag,just behind the '>')
 *  @return �������
 * - 1 �õ�tag����Ϣ
 * - 2 �õ�tag����Ϣ������name-value��̫�࣬�޷���ȫ����ptaginfo�ṹ
 * - -1 ����Ĳ������󣬻�����error
 * - -2 ȱ��tagname������"<>",��ʱ��pend�������õ�'>'�ĺ���
 * - -3 tagname��������ʱ��pend�������õ�'>'�ĺ���
 * - -4 ������"<tagname =value>"�Ĵ��󣬴�ʱ��pend�������õ�'>'�ĺ���
 */
int ul_get_taginfo( char* piece,ul_taginfo_t* ptaginfo,char** pend);
#endif
