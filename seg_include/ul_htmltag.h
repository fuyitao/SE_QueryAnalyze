/**
 * @file
 * @brief 解析网页中的tag
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
 * doxygen文档回归
 *
 * Revision 1.2.12.1  2007/01/31 03:45:20  wangjp2
 * doxygen文档回归cvs
 *
 * Revision 1.2  2006/08/09 11:50:40  qiuzd
 * 修改代码，以支持32位/64位环境
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
 *  解析出网页中tag的name-value对，存储在ul_taginfo_t结构中
 *  
 *  @param[in]  piece    tag区域开始的位置(start behind the '<', not include the '<')
 *  @param[in]  ptaginfo 存储tag结构的地址
 *  @param[out] ptaginfo 输出tag的name-value的结构
 *  @param[out] pend     当前tag区域结束位置(the remainder string after the tag,just behind the '>')
 *  @return 操作结果
 * - 1 得到tag的信息
 * - 2 得到tag的信息，但是name-value对太多，无法完全存入ptaginfo结构
 * - -1 传入的参数错误，或其他error
 * - -2 缺少tagname，例如"<>",此时，pend将被设置到'>'的后面
 * - -3 tagname过长，此时，pend将被设置到'>'的后面
 * - -4 类似于"<tagname =value>"的错误，此时，pend将被设置到'>'的后面
 */
int ul_get_taginfo( char* piece,ul_taginfo_t* ptaginfo,char** pend);
#endif
