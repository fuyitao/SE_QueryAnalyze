/**
 * @file
 * @brief url��ȡ
 */
#ifndef __UL_EXLINK_H__
#define __UL_EXLINK_H__
#include "ul_url.h"

#define  UL_MAX_LINK_NUM     2000
#define  UL_MAX_TEXT_LEN   100

typedef struct _link_info_t {
	char domain[UL_MAX_SITE_LEN];
	char port[UL_MAX_PORT_LEN];
	char path[UL_MAX_PATH_LEN];
	char text[UL_MAX_TEXT_LEN];
	char url[UL_MAX_URL_LEN];
} link_info_t;

#define UL_METHOD_BAIDU		0
#define UL_METHOD_WGET16	1
#define UL_METHOD_WGET18	2

/**
 *  ����url����Ե�url���ϳ��µ�url
 *  
 *  @param[in]  url ��url
 *  @param[in]  relurl ��ص�url�����url
 *  @param[in]  absurl �������ݵ�buf��ַ
 *  @param[out] absurl ���غϳɵ�url
 *  @return �������
 * - 1  �ɹ�
 * - 0  ʧ��
 *  @note ע�����buffer url�Ŀռ���Ҫ�㹻��ͨ��Ҫ����UL_MAX_URL_LENΪ����
 */
int ul_absolute_url(char *url, char *relurl, char *absurl);

 
/**
 *  ����url��Ӧ��page���ݣ��õ��µ�url(��ȡ����)
 *  
 *  @param[in]  url       page��url
 *  @param[in]  page      page������
 *  @param[in]  pagesize  page�Ĵ�С
 *  @param[in]  link_info ����link��Ϣ�Ļ���ṹָ��
 *  @param[in]  num       �ܹ��洢��url��Ϣ�ĸ���
 *  @param[in]  method    �����ķ���
 *  - UL_METHOD_BAIDU 
 *  - UL_METHOD_WGET16
 *  - UL_METHOD_WGET18	
 *  @param[out]  link_info ���ؽ��������µ�url�Ľṹ
 *  @return �������
 * - >=0   �ɹ�
 * - <0    ʧ��
 */
int extract_link(char *url, char *page,int pagesize, link_info_t *link_info, int num,int method);
#endif 
