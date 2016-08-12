#include <codex/convenience/base64.hpp>
#include <cctype>

namespace codex {
  namespace {
    static const char BASE64_TABLE[65] 
      = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    static const char RBASE64_TABLE[128] = {
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
      64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
      52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
      64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
      15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
      64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
      41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
    };
  }
  
  int base64::encode( const char* inptr , const int insz , char* outptr , const int outsz ){
    int end = ((( insz + 2  ) / 3 ) * 4 );
    if ( outsz < end ) 
      return -1;
    int it = 0;
    unsigned int bits = 0;
    unsigned int bits_remain = 0;
    for ( int i = 0; i < insz ; ++i ) {
      bits = ( bits << 8 ) | inptr[i];
      bits_remain += 8;
      while ( bits_remain >= 6 ) {
        bits_remain -= 6;
        outptr[it++] = BASE64_TABLE[ ( bits >> bits_remain ) & 0x3f];
      }
    }
    if ( bits_remain > 0 ) {
      bits <<= ( 6 - bits_remain );
      outptr[it++] = BASE64_TABLE[ bits & 0x3f ];
    }
    while( it < end ) {
        outptr[it++] = '=';
    }
    return end;
  }

  int base64::decode( const char* inptr , const int insz , char* outptr , const int outsz ){
    int end = (( insz  * 3 ) / 4 ); 
    if ( outsz < end )
      return -1;
    int it = 0;
    int bits = 0;
    int bits_remain = 0;
    for ( int i = 0 ; i < insz ; ++i ) {
      const int ch = inptr[i];
      if ( std::isspace(ch) || (ch == '=') || ( ch < 0 ) || ( ch > 127 ))
        continue;
      bits = ( bits << 6 ) | RBASE64_TABLE[ch];
      bits_remain += 6;
      if ( bits_remain >= 8 ) {
        bits_remain -= 8;
        outptr[it++] = static_cast<char>( ( bits >> bits_remain ) & 0xff );
      }
    }
    return it;
  }

}
