#include <gtest/gtest.h>
#include <codex/convenience/string.hpp>
#include "gprintf.hpp"

TEST( string , split ) {
  const char* src = "split test 0 1";
  const char* srcs[] = {
    "split" , "test" , "0"  , "1"
  };
  std::vector< std::string > splits;
  ASSERT_EQ( 4 , codex::string::split( 
        std::string(src) 
        , std::string( " " ) 
        , std::back_inserter(splits)));
  auto splits0 = codex::string::split( 
      std::string(src) 
      , std::string( " " ));

  ASSERT_EQ( splits0.size() , 4 );
  
  for ( int i = 0 ; i< 4 ; ++i ) {
    ASSERT_STREQ( splits[i].c_str() , splits0[i].c_str());
    ASSERT_STREQ( splits[i].c_str() , srcs[i]);
    gprintf( splits[i] );
  }
}

TEST( string , hex ) {
  char ch = 0x2f;
  ASSERT_STREQ( codex::string::hex(&ch,1).c_str() , "2f");
  int i = 0x12345678;
  ASSERT_STREQ( codex::string::hex(&i,4).c_str() , "78563412");
  gprintf( codex::string::hex(&i , 4));
}

TEST( string , replace ) {
  std::string src( "010010" );
  ASSERT_STREQ( codex::string::replace<std::string>( src , "0" , "1" ).c_str() 
      , "111111");
  ASSERT_STREQ( codex::string::replace<std::string>( src , "1" , "0" ).c_str() 
      , "000000");

  src = "test replace value rep";
  std::string t0 = codex::string::replace< std::string >( src , "test" , "" );
  std::string t1 = codex::string::replace< std::string >( src , "rep" , "0" );
  gprintf( t0 );
  gprintf( t1 );
}


TEST( string ,trim ){
  std::string src( "    " );
  codex::string::trim< std::string >( src , " " );
  ASSERT_STREQ( src.c_str() , "" );
  gprintf( src );
  
  src = "  trim";
  codex::string::trim< std::string >( src , " " );
  gprintf( src );
  ASSERT_STREQ( src.c_str() , "trim" );

  src = "  trim";
  codex::string::ltrim< std::string >( src , " " );
  gprintf( src );
  ASSERT_STREQ( src.c_str() , "trim" );

  src = "  trimaaa";
  codex::string::rtrim< std::string >( src , "a" );
  gprintf( src );
  ASSERT_STREQ( src.c_str() , "  trim" );

  src = "  trimabab";
  codex::string::rtrim< std::string >( src , "ab" );
  gprintf( src );
  ASSERT_STREQ( src.c_str() , "  trim" );

  gprintf( codex::string::format( "fmt %d %s" , 88 , "test"));
}
