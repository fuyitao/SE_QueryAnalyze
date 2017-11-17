//***********************************************************************
//			Signature Utilities (SU) 1.0
//
//   programmed by Ming Lei, Jul, 2000
//***********************************************************************


#ifndef __UL_SIGN_H__
#define __UL_SIGN_H__

// description
//
// input :
//    psrc : src data
//    slen : length of the src data, range : 0-256
//
// output :
//    return value : failed = -1, success = 1
//    psign1 : first 4 bytes of signature
//    psign2 : second 4 bytes of signature
//
// notice :
//    if slen==0            --> sign = 0:0
//    if slen>256 or slen<0 --> sign = 0xFFFFFFFF: 0xFFFFFFFF
//

// int creat_sign_t256(char *psrc, int slen, u_int* psign1, u_int* psign2);
// description
//
// input: 
//    psrc : src data
//    slen : length of the src data, range : 0--
//
// output :
//    return value : failed = -1, success = 1
//    sign1 : first 4 bytes of signature
//    sign2 : second 4 bytes of signature
//
// notice :
//    if slen==0            --> sign = 0:0
//
#include <ul_func.h>

int creat_sign_f64 (char* psrc, int slen, u_int* sign1 , u_int* sign2);
int creat_sign_fs64 (char* psrc, int slen, u_int* sign1 , u_int* sign2);
int creat_sign_7_host (char* psrc, int slen, u_int* sign1 , u_int* sign2);
int creat_sign_md64(char* psrc,int slen,u_int* sign1,u_int*sign2);
int creat_sign_mds64(char* psrc,int slen,u_int* sign1,u_int*sign2);

#endif
