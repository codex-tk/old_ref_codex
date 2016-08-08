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
#define gprintf(...)  do {\
  testing::internal::ColoredPrintf(\
      testing::internal::COLOR_YELLOW, "[   USER   ] "); \
  testing::internal::ColoredPrintf(\
      testing::internal::COLOR_DEFAULT, __VA_ARGS__); } while(0)

#endif
