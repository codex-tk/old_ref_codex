#include <gtest/gtest.h>
#include <chrono>
#include <ctime>
#include <codex/convenience/time.hpp>
#include "gprintf.hpp"

TEST( chrono , conv ){
  std::chrono::system_clock::time_point tp = 
    std::chrono::system_clock::now();
  std::time_t epoch = std::chrono::system_clock::to_time_t(tp);
  gprintf( "%s" , std::ctime( &epoch ));
  struct tm* local = std::localtime( &epoch );
  gprintf( "local %d\n" , local->tm_hour );
  struct tm* gm = std::gmtime( &epoch );
  gprintf( "gm %d\n" , gm->tm_hour );
  codex::time::systemtime st( tp + std::chrono::hours(9));
  gprintf( "%d/%d/%d %d:%d:%d\n" , 
     st.wYear   , 
     st.wMonth  , 
     st.wDay    , 
     st.wHour   , 
     st.wMinute , 
     st.wSecond );

  std::chrono::system_clock::time_point ntp = st.to_time_point();
  codex::time::systemtime nst( ntp );
  gprintf( "%d/%d/%d %d:%d:%d\n" , 
     nst.wYear   , 
     nst.wMonth  , 
     nst.wDay    , 
     nst.wHour   , 
     nst.wMinute , 
     nst.wSecond );

}

TEST( time , convenience ) {
  ASSERT_TRUE( codex::time::is_leap_year( 2016 ));
  ASSERT_FALSE( codex::time::is_leap_year( 2017 ));
  ASSERT_EQ( 366 , codex::time::days_between_year( 2016 , 2017 ));
  ASSERT_EQ( 365 , codex::time::days_between_year( 2014 , 2015 ));
  ASSERT_EQ( 31 , codex::time::days_in_a_month( 2016 , 1 ));
  ASSERT_EQ( 29 , codex::time::days_in_a_month( 2016 , 2 ));
  ASSERT_EQ( 60 , codex::time::days_between_month( 2016 , 1 , 3 ));
}
