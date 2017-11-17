#ifndef __TENGYU_TRANS_CODE__
#define __TENGYU_TRANS_CODE__

#ifdef __cplusplus
extern "C" {
#endif

#include<stdio.h>
#include<string.h>
#include<iconv.h>

/*代码转换:从一种编码转为另一种编码*/
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen);

/*UNICODE码转为GB2312码*/
int u2g(char *inbuf,int inlen,char *outbuf,int outlen);

/*GB2312码转为UNICODE码*/
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen);

#ifdef __cplusplus
}
#endif

#endif

