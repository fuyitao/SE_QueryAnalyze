#include"utf8.hpp"

namespace utf8{
std::string encode(unsigned int * unicode_string , int len){
    std::string s(1024,'\0');
    for(int i = 0 ; i < len ; i ++ ){
        unsigned int u = unicode_string[i];
        if( u >= 0 && u <= 0x007f ){
            s += u & 0x7f ;
        }else if( u <= 0x07ff){
            s += ( ( u >> 6 ) & 0x1f ) | 0xc0 ;
            s += ( u & 0x3f ) | 0x80 ;
        }else if( u <= 0xffff ){
            s += ( ( u >> 12 ) & 0x0f ) | 0xe0 ;
            s += ( ( u >> 6  ) & 0x3f ) | 0x80 ;
            s += ( u & 0x3f ) | 0x80 ;
        }else if( u <= 0x1fffff ){
            s += ( ( u >> 18 ) & 0x07 ) | 0xf0 ;
            s += ( ( u >> 12 ) & 0x3f ) | 0x80 ;
            s += ( ( u >> 6  ) & 0x3f ) | 0x80 ;
            s += ( u & 0x3f ) | 0x80 ;
        }else if( u <= 0x03ffffff ){
            s += ( ( u >> 24 ) & 0x03 ) | 0xf8 ;
            s += ( ( u >> 18 ) & 0x3f ) | 0x80 ;
            s += ( ( u >> 12 ) & 0x3f ) | 0x80 ;
            s += ( ( u >> 6  ) & 0x3f ) | 0x80 ;
            s += ( u & 0x3f ) | 0x80 ;
        }else if( u <= 0x7fffffff ){
            s += ( ( u >> 30 ) & 0x01 ) | 0xf8 ;
            s += ( ( u >> 24 ) & 0x3f ) | 0x80 ;
            s += ( ( u >> 18 ) & 0x3f ) | 0x80 ;
            s += ( ( u >> 12 ) & 0x3f ) | 0x80 ;
            s += ( ( u >> 6  ) & 0x3f ) | 0x80 ;
            s += ( u & 0x3f ) | 0x80 ;
        }else{
            s += ' ' ;
        }
    }
    return s ;
}

int decode(std::string utf8_string, unsigned int * unicode_string, int len){
    unsigned int u = 0 ;
    int uidx = 0 ;
    for(size_t i=0;i<utf8_string.length();){
        char c = utf8_string[i];
        if(uidx > len){ break;}
        if( ( c & 0x80 ) == 0x00 ){ // ascii
            unicode_string[uidx++]=(unsigned int)c;
            i++;
        }else if( ( c & 0xc0 ) == 0x80 ){ // bad code
            unicode_string[uidx++]=(unsigned int)' ';
            i++;
        }else if( ( c & 0xe0 ) == 0xc0 ){ // two char
            if( ( i + 1 < utf8_string.length() ) && ( (utf8_string[i+1] & 0xc0 ) == 0x80 ) ){
                char c1 = utf8_string[i+1];
                u  = 0 ;
                u |= ( (unsigned int)( c & 0x1f ) ) << 6 ;
                u |= ( c1 & 0x3f );
                unicode_string[uidx++]=u;
                i += 2;
            }else{
                unicode_string[uidx++]=(unsigned int)' ';
                i++;
            }
        }else if( ( c & 0xf0 ) == 0xe0 ){ // three char
            if( ( i + 2 < utf8_string.length() ) && ( (utf8_string[i+1] & 0xc0 ) == 0x80 ) && ( (utf8_string[i+2] & 0xc0 ) == 0x80 ) ){
                char c1 = utf8_string[i+1];
                char c2 = utf8_string[i+2];
                u = 0 ;
                u |= ( (unsigned int )( c & 0x0f ) ) << 12 ;
                u |= ( (unsigned int )( c1 & 0x3f ) ) << 6 ;
                u |= ( c2 & 0x3f ) ;
                unicode_string[uidx++]=u;
                i += 3;
            }else{
                unicode_string[uidx++]=(unsigned int)' ';
                i++;
            }
        }else if( ( c & 0xf8 ) == 0xf0 ){ // four char
            if( ( i + 3 < utf8_string.length() ) && ( (utf8_string[i+1] & 0xc0 ) == 0x80 ) \
                                     && ( (utf8_string[i+2] & 0xc0 ) == 0x80 ) \
                                     && ( (utf8_string[i+3] & 0xc0 ) == 0x80 ) ){
                char c1 = utf8_string[i+1];
                char c2 = utf8_string[i+2];
                char c3 = utf8_string[i+3];
                u = 0 ;
                u |= ( (unsigned int )( c & 0x07 ) ) << 18 ;
                u |= ( (unsigned int )( c1 & 0x3f ) ) << 12 ;
                u |= ( (unsigned int )( c2 & 0x3f ) ) << 6 ;
                u |= ( c3 & 0x3f ) ;
                unicode_string[uidx++]=u;
                i += 4;
            }else{
                unicode_string[uidx++]=(unsigned int)' ';
                i++;
            }
        }else if( ( c & 0xfc ) == 0xf8 ){ // five char
            if( ( i + 4 < utf8_string.length() ) && ( (utf8_string[i+1] & 0xc0 ) == 0x80 ) \
                                     && ( (utf8_string[i+2] & 0xc0 ) == 0x80 ) \
                                     && ( (utf8_string[i+3] & 0xc0 ) == 0x80 ) \
                                     && ( (utf8_string[i+4] & 0xc0 ) == 0x80 ) ){
                char c1 = utf8_string[i+1];
                char c2 = utf8_string[i+2];
                char c3 = utf8_string[i+3];
                char c4 = utf8_string[i+4];
                u = 0 ;
                u |= ( (unsigned int )( c & 0x03 ) ) << 24 ;
                u |= ( (unsigned int )( c1 & 0x3f ) ) << 18 ;
                u |= ( (unsigned int )( c2 & 0x3f ) ) << 12 ;
                u |= ( (unsigned int )( c3 & 0x3f ) ) << 6 ;
                u |= ( c4 & 0x3f ) ;
                unicode_string[uidx++]=u;
                i += 5;
            }else{
                unicode_string[uidx++]=(unsigned int)' ';
                i++;
            }
        }else if( ( c & 0xfe ) == 0xfc ){ // six char
            if( ( i + 5 < utf8_string.length() ) && ( (utf8_string[i+1] & 0xc0 ) == 0x80 ) \
                                     && ( (utf8_string[i+2] & 0xc0 ) == 0x80 ) \
                                     && ( (utf8_string[i+3] & 0xc0 ) == 0x80 ) \
                                     && ( (utf8_string[i+4] & 0xc0 ) == 0x80 ) ){
                char c1 = utf8_string[i+1];
                char c2 = utf8_string[i+2];
                char c3 = utf8_string[i+3];
                char c4 = utf8_string[i+4];
                char c5 = utf8_string[i+5];
                u = 0 ;
                u |= ( (unsigned int )( c & 0x01 ) ) << 30 ;
                u |= ( (unsigned int )( c1 & 0x3f ) ) << 24 ;
                u |= ( (unsigned int )( c2 & 0x3f ) ) << 18 ;
                u |= ( (unsigned int )( c3 & 0x3f ) ) << 12 ;
                u |= ( (unsigned int )( c4 & 0x3f ) ) << 6 ;
                u |= ( c5 & 0x3f ) ;
                unicode_string[uidx++]=u;
                i += 6;
            }else{
                unicode_string[uidx++]=(unsigned int)' ';
                i++;
            }
        }else{
            unicode_string[uidx++]=(unsigned int)' ';
            i++;
        }
    }
    return uidx;
}

}//namspace utf8


