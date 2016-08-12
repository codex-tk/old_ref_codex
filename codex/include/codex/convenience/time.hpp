/*!
 */
#ifndef __codex_convenience_time_h__
#define __codex_convenience_time_h__ 

#include <codex/codex.hpp>

#include <chrono>
#include <ctime>

namespace codex { namespace time {

  struct systemtime
#if defined( __codex_win32__ )
    : public SYSTEMTIME
#endif
    {
    public:
      systemtime( void );
      systemtime( const std::chrono::system_clock::time_point& tp );

      std::chrono::system_clock::time_point to_time_point( void ) const;
    public:
#if !defined( __codex_win32__ )
      uint16_t wYear;
      uint16_t wMonth;
      uint16_t wDayOfWeek;
      uint16_t wDay;
      uint16_t wHour;
      uint16_t wMinute;
      uint16_t wSecond;
      uint16_t wMilliseconds;
#endif
    };

  //
  bool is_leap_year( const int year );
  // [ begin , end )
  int days_between_year( const int year_begin , const int year_end );
  // [ begin , end )
  // month range : 1 ~ 12
  int days_between_month( const int year , const int month_begin , const int month_end );
  //
  int days_in_a_month( const int year , const int month );
  //
  void convert( const std::time_t t , struct tm& tm );

}}

#endif
