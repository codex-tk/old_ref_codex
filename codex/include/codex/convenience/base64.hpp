/*!
 */
#ifndef __codex_convenience_base64_h__
#define __codex_convenience_base64_h__

namespace codex {

  class base64{
  public:
    static int encode( const char* inptr , const int insz , char* outptr , const int outsz );
    static int decode( const char* inptr , const int insz , char* outptr , const int outsz );
  };

}

#endif
