#include <gtest/gtest.h>
#include <codex/convenience/base64.hpp>
#include "gprintf.hpp"

TEST( base64 , encode ) {
  const char* plain = "base64testtextmessge";
  const char* encode= "YmFzZTY0dGVzdHRleHRtZXNzZ2U=";
  int outlen = (((strlen( plain ) + 2 ) / 3 ) * 4 ) ; 
  char output[ outlen ] = { 0 , };
  ASSERT_EQ( strlen( encode ) , codex::base64::encode( plain , strlen( plain ) , output , outlen ));
  ASSERT_EQ( 0 , memcmp( encode , output , strlen( encode ))  );
}

TEST( base64 , decode ) {
  const char* encode = "YmFzZTY0dGVzdHRleHRtZXNzZ2U=";
  const char* decode = "base64testtextmessge";
  int outlen = ((strlen( encode ) * 3 ) / 4 ); 
  char output[ outlen ] = { 0 , };
  ASSERT_EQ( strlen( decode ) , codex::base64::decode( encode , strlen( encode ) , output , outlen ));
  ASSERT_EQ( 0 , memcmp( decode , output , strlen( decode ))  );
}
