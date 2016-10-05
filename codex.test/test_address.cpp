#include <gtest/gtest.h>
#include <codex/codex.hpp>
#include <codex/ip/address.hpp>
#include "gprintf.hpp"

TEST( address , base ){
  codex::ip::tcp::address addr;
  ASSERT_EQ( addr.type() , SOCK_STREAM );
}

TEST( address , ip ){
  codex::ip::tcp::address addr = codex::ip::tcp::address::from_ip( "192.168.1.1" , 32 );
  ASSERT_TRUE( addr.to_string() ==  std::string( "192.168.1.1") );
  ASSERT_EQ( addr.port() , 32 );
}

TEST( address , resolve ){
  auto addrs = codex::ip::tcp::address::resolve(
      "google.co.kr" , 80 );
  for( auto it : addrs ) {
    gprintf( "Address : %s (%d)\n"
        , it.to_string().c_str()
        , it.port()
        );
  }
}
