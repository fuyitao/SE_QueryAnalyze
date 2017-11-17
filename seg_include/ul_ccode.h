#ifndef __CCODE_H__
#define __CCODE_H__

#include <sys/types.h>

#define	TRBUF_SIZE	512

#define BIG5_NUM	0x3695	//13973

#define BIG5_1LO	0xa1	//161
#define	BIG5_1HI	0xf9	//249
#define BIG5_1NUM	0x59	//89
#define	BIG5_2LO1	0x40	//64
#define	BIG5_2HI1	0x7e	//126
#define	BIG5_2NUM1	0x3f	//63
#define	BIG5_2LO2	0xa1	//161
#define	BIG5_2HI2	0xfe	//254
#define	BIG5_2NUM2	0x5e	//94
#define	BIG5_2NUM	0x9d	//157

#define	GBK_NUM		0x5e02	//24066

#define GBK_1LO		0x81	//129
#define GBK_1HI		0xfe	//254
#define	GBK_1NUM	0x7e	//126
#define	GBK_2LO		0x40	//64
#define	GBK_2HI		0xfe	//254
#define	GBK_2NUM	0xbf	//191
#define GBK_2INV	0x7f	//127

#define CODETYPE_NONE -1
#define CODETYPE_ENG  0
#define CODETYPE_GB   1
#define CODETYPE_BIG5 2
#define CODETYPE_UTF8 3
#define CODETYPE_JPKR 4

#define PY_MAXPAGESIZE 512000
/*#ifndef u_char
#define u_char		unsigned char
#endif
*/
//============== for ccode_check ccode_check_content exit type =================
#define	MAX_CHECK_EXIT		19
#define	CCODE_CHECK_EXIT_1	1
#define	CCODE_CHECK_EXIT_2	2
#define	CCODE_CHECK_EXIT_3	3
#define	CCODE_CHECK_EXIT_4	4
#define	CCODE_CHECK_EXIT_5	5
#define	CCODE_CHECK_EXIT_6	6
#define	CCODE_CHECK_EXIT_7	7
#define	CCODE_CHECK_EXIT_8	8
#define	CCODE_CHECK_EXIT_9	9
#define	CCODE_CHECK_EXIT_10	10
#define	CCODE_CHECK_EXIT_11	11
#define	CCODE_CHECK_EXIT_12	12
#define	CCODE_CHECK_EXIT_13	13
#define	CCODE_CHECK_EXIT_14	14
#define	CCODE_CHECK_EXIT_15	15
#define	CCODE_CHECK_EXIT_16	16
#define	CCODE_CHECK_EXIT_17	17
#define	CCODE_CHECK_EXIT_18	18
#define	CCODE_CHECK_EXIT_19	19

#define	CCODE_CONT_URLNONE		101
#define	CCODE_CONT_SHORT		102
#define	CCODE_CONT_ENG2GB		103
#define	CCODE_CONT_GBBIG52ENG	104
#define	CCODE_CONT_UTF82NONE	105
#define	CCODE_CONT_NONE2ENG		106
#define	CCODE_CONT_REMAIN		107
//=========================================

/* You should specify the `path' to txt's files in which char-map tables are
 * allocated while using these functions.
 *
 * All tables are lying in path/code directory.
 */

/*
ul_ccode_load
return 0 when success
return -1 when error 
*/
int ul_ccode_load(char *path);


/*
return codetype
currently: 
it can be 
0: english
1: GBK
2: Big5
3: UTF-8 encoded chinese
-1: Other
*/

int ul_ccode_check_realtext(const char* pstr);
int ul_ccode_check(char *pstr);
int ul_ccode_check_notetype (char *pstr, int *out_type);

/*
check whether the main content of a URL is Chinese and should be indexed
Notice: MUST call ul_trans2gb before sending pTitle & pContent to this function
		old_codetype is the return of ul_ccode_check
return: new codetype
*/
int ul_ccode_check_content
	(const char* pTitle, const char* pContent, const char* pUrl, int old_codetype);
int ul_ccode_check_content_notetype
	(const char* pTitle, const char* pContent, const char* pUrl, int old_codetype, int *out_type);

int ul_ccode_del();

 /*=============================================================================
  * Function:        ul_is_tradgbk_str       
  * 
  * Description:     judge whether a string is encoded in traditional gbk
  * 
  * Input:           const char* pstr, the string to be judged, it must be a
  * 				 
  * 				 zero ended string                
  * 
  * Return:          1, traditional gbk string; 0. simple gbk string 
  * 
  *============================================================================*/
int ul_is_tradgbk_str(const char* pstr);

/*
ul_trans2gb
return 0 when success
return -1 when error 
*/
int ul_trans2gb(char *input,char *output, int codetype);

 /*=============================================================================
  * Function:        ul_big5_gbk_str       
  * 
  * Description:     translate big5 encoding string into gbk encoding string
  * 
  * Input:           u_char* psrc, input big5 encoding string 
  *                  int len, the length of the psrc, len<=0, the the lenght 
  *                  will be calculated internally,  but must make sure that 
  *                  psrc ended with '\0';                
  * 
  * Output:          u_char* pDest, buffer to hold the gbk encoding string
  * 
  * Return:          <0, failed; >=0, succeed. the lengh of the input string; 
  * 
  * Others:          the buffer length of pdes must be larger than the length
  * 				 of input string.  ul_ccode_load() must be called before
  * 				 this function.
  *============================================================================*/
int ul_big5_gbk_str(u_char *psrc, u_char *pdes, int len);

int ul_big5_gbi_str(u_char *psrc, u_char *pdes, int len);

 /*=============================================================================
  * Function:        ul_gbk_big5_str       
  * 
  * Description:     translate gbk encoding string into big5 encoding string
  * 
  * Input:           u_char* psrc, input big5 encoding string 
  *                  int len, the length of the psrc, len<=0, the the lenght 
  *                  will be calculated internally,  but must make sure that 
  *                  psrc ended with '\0';                
  * 
  * Output:          u_char* pDest, buffer to hold the gbk encoding string
  * 
  * Return:          <0, failed; >=0, succeed. the lengh of the input string; 
  * 
  * Others:          the buffer length of pdes must be larger than the length
  * 				 of input string.  ul_ccode_load() must be called before
  * 				 this function.
  *============================================================================*/
int ul_gbk_big5_str(u_char *psrc, u_char *pdes, int len);

int ul_gbk_gbi_str(u_char *psrc, u_char *pdes, int len);
int ul_gbi_big5_str(u_char *psrc, u_char *pdes, int len);
int ul_gbi_gbk_str(u_char *psrc, u_char *pdes, int len);


// transfer quanjiao keyboard letter/number/symbol to banjiao 
// this transformation can be made in-place, i.e. szIn == szOut
void ul_trans2bj(const char *szIn, char *szOut);

// transfer some special chinese quanjiao symbols to its corresponding banjiao form
// this transformation can be made in-place, i.e. szIn == szOut
void ul_trans2bj_ext(const char *szIn, char *szOut);

// transfer from uppercase to lower case, for gbk-encoded string
// this transformation can be made in-place, i.e. szIn == szOut
void ul_trans2lower(const char *szIn, char *szOut);

/*
obsolete function, use ul_trans2bj/ul_trans2bj_ext/ul_trans2lower instead
* transfer quanjiao to banjiao and upper to lower

int ul_transfer_ch(char *input,char *output);
*/

/*=============================================================================
 * Function:		ul_gbk_to_utf8       
 *
 * Description:		translate gbk encoding string into utf8 encoding string
 *
 * Input:			const char* pSrc, input gbk encoding string 
 * 					const unsigned nDesCnt, the length of the dest buffer
 *
 * Output:			char* pDest, buffer to hold the utf8 encoding string
 *
 * Return:			<0, failed; >0, succeed. the lengh of the utf8 string; 
 *
 * Others:			nDestCnt must be larger than 3/2*strlen(pSrc);
 *
 *============================================================================*/
int ul_gbk_to_utf8(char* pDest, const unsigned nDesCnt, const char* pSrc);

/*=============================================================================
 * Function:		ul_utf8_to_gbk       
 *
 * Description:		translate utf8 encoding string into gbk encoding string
 *
 * Input:			const char* pSrc, input gbk encoding string 
 * 					const unsigned nDesCnt, the length of the dest buffer
 *
 * Output:			char* pDest, buffer to hold the gbk encoding string
 *
 * Return:			<0, failed; >0, succeed. the lengh of the gbk string; 
 *
 * Others:			nDestCnt must be larger than strlen(pSrc);
 *
 *============================================================================*/
int ul_utf8_to_gbk(char* pDest, const unsigned nDesDnt, const char* pSrc);

inline int is_big5( u_char *upstr )
{
	if ( (upstr[0]>=0xa1) && (upstr[0]<=0xf9) &&
	     ( (upstr[1]>=0x40) && (upstr[1]<=0x7e) ||
               (upstr[1]>=0xa1) && (upstr[1]<=0xfe)
	   ) ) {
		return 1;
	}
	else{
		return 0;
	}
}

inline int is_gbk( u_char *pstr )
{
	if ( (pstr[0]>=GBK_1LO) && (pstr[0]<=GBK_1HI) &&
	     (pstr[1]>=GBK_2LO) && (pstr[1]<=GBK_2HI) &&
             (pstr[1]!=GBK_2INV)
	   ) {
		return 1;
	}
	else{
		return 0;
	}
}

inline int is_gb(u_char* pstr)
{
	if ( (pstr[0]>=0xB0) && (pstr[0]<=0xF7) &&
	     (pstr[1]>=0xA1) && (pstr[1]<=0xFE) ) 
	{
		return 1;
	}
	else{
		return 0;
	}
}

inline int is_big5_str(const char* pstr)
{
	char szContent[1024];
	char* pSrc = (char*) pstr;
	char* pDest = szContent;
	char* pEnd = szContent + 256;
	u_char ch;
	int count = 0, len, i, real_count=0;
	short former_word = 0;

	// Get out the double bite words
	while( (ch = *pSrc) != 0 && pSrc[1] ){
		if ( ch <= 0x7f )
			++pSrc;
		else{
			if(*(short*)pSrc != former_word)
				++real_count;
			*pDest++ = ch;
			*pDest++ = pSrc[1];
			former_word= *(short*)pSrc;
			pSrc += 2;
			++count;
		}
        if( pDest >= pEnd )
		   break;
	}
	*pDest = 0;
	len = pDest - szContent;

	if(count == 0)
		return 0;

	for(i= 0;i<count; i++){
		if(!is_big5((u_char*)&szContent[i]))
			return 0;
		if(!is_gb((u_char*)&szContent[i]))
			return 1;
	}

	// can not judge from code range, make a choice of bigger probability
	return 0;
		
}

inline int is_gbk_str(const char* pSrc);

#endif
