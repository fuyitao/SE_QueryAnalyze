#pragma once

#define INIT_PROPERTY(property) property.high_property = 0;property.low_property = 0;

#define IS_PHRASE(property)     ((property.high_property)& 0x00000001)   
#define DEL_PHRASE(property)    ((property.high_property)& 0x11111110)
#define SET_PHRASE(property)    ((property.high_property)|= 0x00000001)

#define IS_MARK(property)       ((property.high_property)& 0x00000002)  
#define SET_MARK(property)      ((property.high_property)|= 0x00000002)

#define IS_ALNUM(property)      ((property.high_property)& 0x00000004) 
#define SET_ALNUM(property)     ((property.high_property)|= 0x00000004)

#define IS_ONEWORD(property)    ((property.high_property)& 0x00000008) 
#define SET_ONEWORD(property)   ((property.high_property)|= 0x00000008)

#define IS_ASCIIWORD(property)  ((property.high_property)& 0x00000010) 
#define SET_ASCIIWORD(property) ((property.high_property)|= 0x00000010)

#define IS_ASCIINUM(property)   ((property.high_property)&0x00000020) 
#define SET_ASCIINUM(property)  ((property.high_property)|=0x00000020)

#define IS_HUMAN_NAME(property) ((property.high_property)& 0x00000040)  
#define SET_HUMAN_NAME(property)((property.high_property)|=0x00000040)

#define IS_TIME(property)       ((property.high_property)& 0x00000080) 
#define SET_TIME(property)      ((property.high_property)|= 0x00000080)

#define IS_CNUMBER(property)    ((property.high_property)& 0x00000100)
#define SET_CNUMBER(property)   ((property.high_property)|= 0x00000100)

#define IS_SURNAME(property)    ((property.high_property)& 0x00000200)
#define SET_SURNAME(property)   ((property.high_property)|= 0x00000200)

#define IS_QUANTITY(property)   ((property.high_property)& 0x00000400)
#define SET_QUANTITY(property)  ((property.high_property)|=0x00000400)

#define IS_LOC(property)        ((property.high_property)& 0x00000800)
#define SET_LOC(property)       ((property.high_property)|= 0x00000800)

#define IS_ORGNAME(property)    ((property.high_property)& 0x00001000)
#define SET_ORGNAME(property)   ((property.high_property)|= 0x00001000)

#define IS_PLACE_SUFFIX(property)      ((property.high_property)& 0x00800000)
#define SET_PLACE_SUFFIX(property)     ((property.high_property)|= 0x00800000)

#define IS_HZ(property)      ((property.high_property)& 0x01000000)
#define SET_HZ(property)     ((property.high_property)|= 0x01000000)

#define IS_DI(property)  ((property.high_property)& 0x02000000)
#define SET_DI(property)  ((property.high_property)|=0x02000000)

#define IS_BOOKNAME(property)   ((property.high_property)& 0x08000000)
#define SET_BOOKNAME(property)  ((property.high_property)|= 0x08000000)

#define IS_BOOKNAME_START(property) ((property.high_property)&0x20000000)
#define SET_BOOKNAME_START(property) ((property.high_property)|=0x20000000)

#define IS_BOOKNAME_END(property)       ((property.high_property)&0x40000000)
#define SET_BOOKNAME_END(property)      ((property.high_property)|=0x40000000)

#define IS_UNIVERSITY(property)        ((property.low_property)& 0x00000001)
#define SET_UNIVERSITY(property)       ((property.low_property) |= 0x00000001)

#define IS_SOFTNAME(property)        ((property.low_property)& 0x00000002)
#define SET_SOFTNAME(property)       ((property.low_property) |= 0x00000002)

#define IS_FMNAME(property)        ((property.low_property)& 0x00000004)
#define SET_FMNAME(property)       ((property.low_property) |= 0x00000004)

#define IS_LOC_SMALL(property)        ((property.low_property)& 0x00000008)
#define SET_LOC_SMALL(property)       ((property.low_property) |= 0x00000008)

#define IS_BRAND(property)        ((property.low_property)& 0x00000010)
#define SET_BRAND(property)       ((property.low_property) |= 0x00000010)

#define IS_TEMP(property)        ((property.low_property)& 0x00000020)
#define SET_TEMP(property)       ((property.low_property) |= 0x00000020)

#define IS_SPEC_ENSTR(property)  ((property.low_property)& 0x00000080)
#define SET_SPEC_ENSTR(property)  ((property.low_property)|= 0x00000080)

#define IS_NAMEMID(property)      ((property.high_property)& 0x00002000)
#define SET_NAMEMID(property)     ((property.high_property)|= 0x00002000)

#define IS_NAMEEND(property)     ((property.high_property)& 0x00004000)
#define SET_NAMEEND(property)        ((property.high_property)|= 0x00004000)

#define IS_SPACE(property)        ((property.low_property)& 0x00000040)
#define SET_SPACE(property)       ((property.low_property) |= 0x00000040)

/* property for Chinese */
#define IS_NAME_STICK(property)     ((property.high_property)& 0x00008000)
#define SET_NAME_STICK(property)    ((property.high_property)|= 0x00008000)

#define IS_QIANZHUI(property)       ((property.high_property)& 0x00010000)
#define SET_QIANZHUI(property)      ((property.high_property)|= 0x00010000)

#define IS_HOUZHUI(property)        ((property.high_property)& 0x00020000)
#define SET_HOUZHUI(property)       ((property.high_property)|= 0x00020000)

#define IS_QIANDAO(property)        ((property.high_property)& 0x00040000)
#define SET_QIANDAO(property)       ((property.high_property)|= 0x00040000)

#define IS_HOUDAO(property)         ((property.high_property)& 0x00080000)
#define SET_HOUDAO(property)        ((property.high_property)|= 0x00080000)

#define IS_CFOREIGN(property)       ((property.high_property)& 0x00100000)
#define SET_CFOREIGN(property)      ((property.high_property)|= 0x00100000)

#define IS_STOPWORD(property)       ((property.high_property)& 0x00200000)
#define SET_STOPWORD(property)      ((property.high_property)|= 0x00200000)

#define IS_SPECIAL(property)        ((property.high_property)& 0x00400000)
#define SET_SPECIAL(property)       ((property.high_property)|= 0x00400000)

#define IS_QYPD(property)       ((property.high_property)& 0x04000000)
#define SET_QYPD(property)       ((property.high_property)|=0x04000000)

#define IS_2WHPREFIX(property) ((property.high_property)& 0x10000000)
#define SET_2WHPREFIX(property) ((property.high_property)|= 0x10000000)
 
#define IS_CH_NAME(property)  ((property.high_property)&0x80000000)
#define SET_CH_NAME(property)  ((property.high_property)|=0x80000000)

#define IS_LOC_FOLLOW(property)  ((property.low_property)&0x00000100)
#define SET_LOC_FOLLOW(property)  ((property.low_property)|=0x00000100)

#define IS_FNAMEBGN(property)      ((property.low_property)& 0x00000200)
#define SET_FNAMEBGN(property)     ((property.low_property)|= 0x00000200)

#define IS_FNAMEMID(property)      ((property.low_property)& 0x00000400)
#define SET_FNAMEMID(property)     ((property.low_property)|= 0x00000400)

#define IS_FNAMEEND(property)     ((property.low_property)& 0x00000800)
#define SET_FNAMEEND(property)        ((property.low_property)|= 0x00000800)

#define IS_2FNAMEEND(property)     ((property.low_property)& 0x00001000)
#define SET_2FNAMEEND(property)        ((property.low_property)|= 0x00001000)

#define IS_1W_NAMEEND(property)  ((property.high_property&0x00000008) && (property.high_property&0x00004000))

#define IS_1W_SUFFIX(property) ((property.low_property) & 0x01000000)
#define SET_1W_SUFFIX(property) ((property.low_property) |= 0x01000000)

#define IS_VIDEO(property)    ((property.low_property) & 0x80000000)
#define SET_VIDEO(property)    ((property.low_property) |= 0x80000000)

#define IS_GAME(property)     ((property.low_property) & 0x40000000)
#define SET_GAME(property)     ((property.low_property) |= 0x40000000)

#define IS_SONG(property)     ((property.low_property) & 0x20000000)
#define SET_SONG(property)    ((property.low_property) |= 0x20000000)

#define IS_PRODUCT(property)      ((property.low_property) & 0x10000000)
#define SET_PRODUCT(property)      ((property.low_property) |= 0x10000000)

#define IS_STATIC_BOOK(property)      ((property.low_property) & 0x02000000)
#define SET_STATIC_BOOK(property)      ((property.low_property) |= 0x02000000)

#define IS_NUM_QUALITY(property) ((property.low_property) & 0x00100000)
#define SET_NUM_QUALITY(property) ((property.low_property) |= 0x00100000) 

#define IS_PHRASE_TERM(property) ((property.low_property) & 0x00200000)
#define SET_PHRASE_TERM(property) ((property.low_property) |= 0x00200000) 


/*==== for chinese */

#define CHN_CHAR_NUM	6768

#define SYM_HIMIN	0xA1	/* GB symbol : minmum value of first byte */
#define SYM_HIMAX	0xF7	/* GB symbol : maxmum value of first byte */
#define SYM_LOMIN	0xA1	/* GB symbol : minmum value of second byte */
#define SYM_LOMAX	0xFE	/* GB symbol : maxmum value of second byte */

#define CHAR_HIMIN	0xB0	/* GB char   : min - 1st byte */
#define CHAR_HIMAX	0xF7	/* GB char   : max - 1st byte */
#define CHAR_LOMIN	0xA1	/* GB char   : min - 2nd byte */
#define CHAR_LOMAX	0xFE	/* GB char   : max - 2nd byte */

#define CHAR_HINUM      0x48	/* (0xF7-0xB0+1) */
#define CHAR_LONUM      0x5E	/* (0xFE-0xA1+1) */

#define MARK_HIMIN	0xA1	/* GB mark   : min - 1st byte */
#define MARK_HIMAX	0xAF	/* GB mark   : max - 1st byte */
#define MARK_LOMIN	0xA1	/* GB mark   : min - 2nd byte */
#define MARK_LOMAX	0xFE	/* GB mark   : max - 2nd byte */

#define SMARK_HIMIN      0xA3    /* simple GB mark   : min - 1st byte */
#define SMARK_HIMAX      0xA3    /* simple GB mark   : max - 1st byte */
#define SMARK_LOMIN      0xA1    /* simple GB mark   : min - 2nd byte */
#define SMARK_LOMAX      0xFE    /* simple GB mark   : max - 2nd byte */

#define DIGIT_HIMIN     0xa3    /* GB 0---9 */
#define DIGIT_HIMAX     0xa3
#define DIGIT_LOMIN     0xb0
#define DIGIT_LOMAX     0xb9
 
#define HI_HIMIN        0xa3    /* GB A---Z */   
#define HI_HIMAX        0xa3
#define HI_LOMIN        0xc1
#define HI_LOMAX        0xda
                        
#define LOW_HIMIN       0xa3    /* GB a---z */ 
#define LOW_HIMAX       0xa3
#define LOW_LOMIN       0xe1
#define LOW_LOMAX       0xfa

#define GBK_HIMIN       0x81
#define GBK_HIMAX       0xfe
#define GBK_LOMIN       0x40
#define GBK_LOMAX       0xfe

/* define the range of gb */
#define IN_RANGE(ch, min, max) ( (((unsigned char)(ch))>=(min)) && (((unsigned char)(ch))<=(max)) )

#define IS_GB(cst)	( IN_RANGE((cst)[0], SYM_HIMIN, SYM_HIMAX) && IN_RANGE((cst)[1], SYM_LOMIN, SYM_LOMAX) )

#define IS_GBK(cst)      ( IN_RANGE((cst)[0], GBK_HIMIN, GBK_HIMAX) && IN_RANGE((cst)[1], GBK_LOMIN, GBK_LOMAX) )

#define IS_GB_CODE(cst)	( IN_RANGE((cst)[0], CHAR_HIMIN, CHAR_HIMAX) && IN_RANGE((cst)[1], CHAR_LOMIN, CHAR_LOMAX) )

#define IS_GB_MARK(cst)	( IN_RANGE((cst)[0], MARK_HIMIN, MARK_HIMAX) && IN_RANGE((cst)[1], MARK_LOMIN, MARK_LOMAX) )

#define IS_GB_SMAEK(cst) ( IN_RANGE((cst)[0], SMARK_HIMIN, SMARK_HIMAX) && IN_RANGE((cst)[1], SMARK_LOMIN, SMARK_LOMAX) )

#define IS_GB_SPACE(cst) ( (((unsigned char)((cst)[0]))==SYM_HIMIN) && (((unsigned char)((cst)[1]))==SYM_LOMIN) )

#define IS_GB_NOBREAK(cst) ( (unsigned char)(cst)[0]==0xa3 && ((unsigned char)(cst)[1]==0xa6 ||(unsigned char)(cst)[1]==0xad ||(unsigned char)(cst)[1]==0xdf) )

#define IS_GB_1234(cst) (IN_RANGE((cst)[0],DIGIT_HIMIN,DIGIT_HIMAX) && IN_RANGE((cst)[1],DIGIT_LOMIN,DIGIT_LOMAX) )

#define IS_GB_ABCD(cst) ( (IN_RANGE((cst)[0],HI_HIMIN,HI_HIMAX) && IN_RANGE((cst)[1],HI_LOMIN,HI_LOMAX) ) || (IN_RANGE((cst)[0],LOW_HIMIN,LOW_HIMAX) && IN_RANGE((cst)[1],LOW_LOMIN,LOW_LOMAX) ) ) 

//Other gb characters can not displayed properly:
//A9: F5--F6
//A8: EA--F6
//    96--A0
//A7: F2--F6
//    C2--D0
//A6: B9--C0
//    D9--DF
//    F6--FE
//A4: F3--F7
//A2: FE
//A2: FD--FE
#define IS_GB_UNDEFINED(cst) ( (IN_RANGE((cst)[0], 0xaa, 0xaf) && IN_RANGE((cst)[1], 0xa1, 0xfe) ) || (IN_RANGE((cst)[0], 0xf8, 0xfe) && IN_RANGE((cst)[1], 0xa1, 0xfe) ) || (IN_RANGE((cst)[0], 0xa1, 0xa7) && IN_RANGE((cst)[1], 0x40, 0xa0) ) || ( IN_RANGE((cst)[0], 0xa4, 0xa9) && IN_RANGE((cst)[1], 0xf7, 0xfe)) ) 

const static char kAalNumMap[256] = 
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

