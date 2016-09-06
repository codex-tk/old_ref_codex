/*!
 */
#ifndef __codex_convenience_stirng_h__
#define __codex_convenience_stirng_h__

#include <string>
#include <vector>
#include <cstdarg>

#include <codex/codex.hpp>

namespace codex {

  class string {
  public:
    template < class String , class BackInserter >
    static std::size_t split( const String& msg , 
        const String& sep ,
        BackInserter bs )
    {
      std::size_t cnt = 0;
      auto end = msg.length();
      auto start = msg.find_first_not_of( sep );
      while ( true ) {
        if ( start >= end ) 
          break;
        auto stop = msg.find_first_of( sep , start );
        if ( stop == String::npos )
          stop = end;

        *bs = msg.substr( start , stop - start );
        ++bs;++cnt;
        start = msg.find_first_not_of( sep , stop + 1 );
      }
      return cnt; 
    }

    template < class String >
    static std::vector< String > split( const String& msg 
        , const String& sep ) 
    {
      std::vector< String > splitvec;
      codex::string::split( msg , sep , std::back_inserter( splitvec ));
      return splitvec;
    }

    template < class String >
    static std::vector< String > split( const String& msg 
        , const String& sep , const int n )
    {
      // todo
    }

    template < class String >
    static std::vector< String > rsplit( const String& msg 
        , const String& sep , const int n )
    {
      // todo
    }

    static std::string hex( const void* ptr , int sz ) {
      static const char _hex[] = "0123456789abcdef";
      const char* inptr = static_cast< const char* >(ptr); 
          //const_cast<void*>(ptr));
      std::string value; value.reserve( sz  * 2 );
      for ( int i = 0 ; i < sz ; ++i ) {
        value.push_back( _hex[ inptr[i] >>   4 ] );
        value.push_back( _hex[ inptr[i] & 0x0f ] );
      }
      return value;
    }

    template < class String >
    static String replace( const String& msg 
        , const String& pattern 
        , const String& replace )
    {
      String replaced;
      typename String::size_type pos = 0 , find_begin = 0;
      while ( true ) {
        pos = msg.find( pattern , find_begin ); 
        if ( pos == String::npos ){
          std::copy( msg.begin() + find_begin , msg.end() 
              , std::back_inserter(replaced));
          break;
        }
        std::copy( msg.begin() + find_begin , msg.begin() + pos  
            , std::back_inserter(replaced));
        std::copy( replace.begin() , replace.end()
            , std::back_inserter(replaced));
        find_begin = pos + pattern.length();
      }
      return replaced;
    }

    template < class String >
    static void ltrim( String& msg , const String& trstr ) {
      auto begin = msg.find_first_not_of( trstr );
      if ( begin == String::npos ){
        msg.resize(0);
        return;
      }
      auto end = msg.length();
      int pos = 0;
      for ( int i = begin ; i < end ; ++i ) {
        msg[pos++] = msg[i];
      }
      msg.resize(pos);
    }
    
    template < class String >
    static void rtrim( String& msg , const String& trstr ) {
      auto end = msg.find_last_not_of( trstr );
      if ( end == String::npos ){
        msg.resize(0);
        return;
      }
      msg.resize(end+1);
    }

    template < class String >
    static void trim( String& msg , const String& trstr ) {
      auto begin = msg.find_first_not_of( trstr );
      if ( begin == String::npos ){
        msg.resize(0);
        return;
      }
      auto end = msg.find_last_not_of( trstr );
      int pos = 0;
      for ( int i = begin ; i <= end ; ++i ) {
        msg[pos++] = msg[i];
      }
      msg.resize(pos);
    }

    static std::string format( const char* fmt , ... ) {
      char buf[4096] = { 0 , };
      va_list args;
      va_start( args , fmt );
      int ret = vsnprintf( buf , 4095 , fmt , args );
      va_end( args );
      if ( ret < 0 ) ret = 0;
      return std::string( buf , ret );
    }
  };

}

#endif
