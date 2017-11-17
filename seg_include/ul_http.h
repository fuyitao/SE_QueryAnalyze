/**
 * @file
 * @brief HTTP��ҳ���
 */
//**********************************************************
//			HTTP Utility 1.0
//
//  HTTP functions... 
//  ZhouXin,xzhou@baidu.com
//  2000.9.30
//    
//**********************************************************

#ifndef __UL_HTTPLIB_H__
#define	__UL_HTTPLIB_H__

//******************************************
//include area 
//*****************************************
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <endian.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "ul_net.h"
/*Max url length*/
#define    MAXURL        256 

/*Max url host part length*/
#define    MAXHOST       64 

/*Max url file part length*/
#define    MAXFILE        192

/*Max http page length*/
#define    MAXPAGE        256000

/*Mac http head length*/
#define    MAXHEAD        4096

/*Max http command length*/
#define    MAXGETCMD      1256

/*Max ip string length*/
#define    MAXIP          16

#define    MAXPORTS        8

/*Write, read and connection timeout for socket*/
#define    WRITETIMEOUT   60
#define    READTIMEOUT    300
#define    CONNECTTIMEOUT 30

/*Retry times for tcp connection*/
#define    RETRYTIME      1

#define    SITE_LEN 100
#define    PORT_LEN 10

/*
 * WARNING : check_URL is out of data,  using functions
 * defined in ul_url.h instead
 */
extern int check_URL(char *url);

/*
 * WARNING : check_hostname is out of data,
 * using functions defined in ul_url.h instead
 */
extern int check_hostname(char *host_name);


/***********************************************************************
 * NOTICE   : this function is out of data, see functions in libhttp 
 *          : instead
 * functoin : Get html page
 * argu-in  :  url
 *          :  ip(if ip is not NULL,use this ip address instead of lookup 
 *          :     from DNS Server) 
 * argu-out : lastmod(if Last-Modified http head exists,copy to lastmod) 
 *          : page(if get success,put the http heads and html page to page) 
 *          : redirurl(if meet redirect,put the new url to redirurl)
 **********************************************************************/
extern int  ul_gethttpcontent(char *, char *, int *pagesize, char *, char *, char *, char*);


/***********************************************************************
 * function : Check the page is content redirection or not
 * in-argu  : char* page : the page
 *          : int size   : the size of the page
 * out-argu : char* redir: the target url of the redirection
 * return   : 1 if the page is a redirection page
 *          : 0 if not
 ***********************************************************************/
int isconredir(char *page, int size, char *redir);

/*
	liumh add for condition get
*/

#define MAX_ETAG_LEN 64
#define METHOD_GET 1
#define METHOD_CHK 2

#define LASTMOD_FLAG 1
#define ETAG_FLAG 2

/*
 * WARNING: the struct and the functions about this are out of date.
 *          Using libhttp instead
 */

typedef struct __page_item
{
	int method;
	int orilen;
	int head_flag;
	char url[MAXURL];
	char ip[MAXIP];
	char protocol[4];
	int pagesize;
	int status;
	int conlen;
	char lastmod[MAXLINE];
	char contyp[MAXLINE];
	char trnenc[MAXLINE];
	char etag[MAX_ETAG_LEN];
	char redir[MAXURL];
	char *page;
	int proxy_flag;
}PAGE_ITEM;
/**
 *  ץȡ��ҳ��������chunkedת��
 *  
 *  @param[in]  pageitem ����url,ip,port����Ϣ
 *  @param[out] pageitem ����ȡ�õ���ҳ
 *  @return �����������
 * - >=0 ��ҳ��status
 * - -1  ʧ��
 * - -2  ��ʱ
 */
extern int  ul_gethttpcontent_new(PAGE_ITEM *pageitem);

/**
 *  ץȡ��ҳ��������chunkedת��
 *  
 *  @param[in]  pageitem ����url,ip,port����Ϣ
 *  @param[out] pageitem ����ȡ�õ���ҳ
 *  @return �����������
 * - >=0 ��ҳ��status
 * - -1  ʧ��
 * - -2  ��ʱ
 *  @note ��::ul_gethttpcontent_new_notpt�������ǣ�ץȡ��ҳ��get���ͬ������chunk�ķ�ʽҲ��������ϸ��::ul_gethttpcontent_new_notpt
 */
 
 
/**
 *  ץȡ��ҳ��������chunkedת��
 *  
 *  @param[in]  pageitem ����url,ip,port����Ϣ
 *  @param[out] pageitem ����ȡ�õ���ҳ
 *  @return �����������
 * - >=0 ��ҳ��status
 * - -1  ʧ��
 * - -2  ��ʱ
 *  @note ��ul_gethttpcontent_new�������ǣ�ץȡ��ҳ��get���ͬ��������If-Modified-Since��If-None-Match�����������chunk�ķ�ʽҲ������
 */
extern int  ul_gethttpcontent_new_notpt(PAGE_ITEM *pageitem);

#endif
