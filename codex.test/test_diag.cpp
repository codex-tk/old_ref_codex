#include <gtest/gtest.h>
#include <codex/diag/error.hpp>

TEST( diag , error ) {
  std::error_code ec = codex::make_error_code( 
      codex::errc::fail );
  ASSERT_TRUE( ec );
  ASSERT_EQ( ec , codex::errc::fail );
  ASSERT_NE( ec , codex::errc::success );
}

TEST( diag , error_condition ) {
  std::error_code ec = codex::make_error_code( 
      codex::errc::invalid_argument );
  std::error_condition ec2 = codex::make_error_condition( codex::errc::invalid_argument);

  // equivalent( int code , std::error_condition ) 
  ASSERT_EQ( ec , ec2 );
  // equivalent( int code , std::error_condition ) 
  ASSERT_EQ( ec , std::errc::invalid_argument );
  // equivalent( std::error_code , int cond ) 
  ASSERT_EQ( ec2 ,std::make_error_code( std::errc::invalid_argument ));
}
