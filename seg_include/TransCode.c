#include"TransCode.h"

/*代码转换:从一种编码转为另一种编码*/
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
{
    iconv_t cd;
    char **pin = &inbuf;
    char **pout = &outbuf;
    size_t in_len_t,out_len_t;
    in_len_t=(size_t)inlen;
    out_len_t=(size_t)outlen;
    cd = iconv_open(to_charset,from_charset);
    if (cd==0){
        fprintf(stdout,"iconv open failed.\n");
        fflush(stderr);
        return -1;
    }
    memset(outbuf,0,outlen);
    /*outbuf[0]=0;*/
    if (iconv(cd,pin,&in_len_t,pout,&out_len_t)==(size_t)-1){
        fprintf(stderr,"iconv convert failed.\n");
        fflush(stderr);
        return -1;
    }
    iconv_close(cd);
    return 0;
}

/*UNICODE码转为GB2312码*/
int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
    return code_convert((char*)"utf-8",(char*)"gbk",inbuf,inlen,outbuf,outlen);
}


/*GB2312码转为UNICODE码*/
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
    return code_convert((char*)"gbk",(char*)"utf-8",inbuf,inlen,outbuf,outlen);
}
#if 0
int main(){
    char utf8[100]="";
    strcpy(utf8,"我吃饭");
    char gbk[100]="";
    u2g(utf8,(int)100,gbk,(int)100);
    printf("%s\n",gbk);
}
#endif

