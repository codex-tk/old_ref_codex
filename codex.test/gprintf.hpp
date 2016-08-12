#ifndef __gprintf_h__
#define __gprintf_h__ 

#include <gtest/gtest.h>

namespace testing
{
  namespace internal
  {
    enum GTestColor {
      COLOR_DEFAULT,
      COLOR_RED,
      COLOR_GREEN,
      COLOR_YELLOW
    };
    extern void ColoredPrintf(GTestColor color, const char* fmt, ...);
  }
}

static void gprintf( const std::string& msg ) {
  testing::internal::ColoredPrintf(
    testing::internal::COLOR_YELLOW, "[   USER   ] "); 
  testing::internal::ColoredPrintf(
    testing::internal::COLOR_DEFAULT , "%s\n" ,  msg.c_str() ); 
}

template < class ...Args >
void gprintf( const char* fmt , Args&&... arg ) {
  testing::internal::ColoredPrintf(
    testing::internal::COLOR_YELLOW, "[   USER   ] "); 
  testing::internal::ColoredPrintf(
    testing::internal::COLOR_DEFAULT , fmt , std::forward<Args>(arg)... ); 
}

#endif
