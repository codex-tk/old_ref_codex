#include <codex/time/convenience.hpp>

#include <chrono>
#include <ctime>

namespace codex { namespace time {

  systemtime::systemtime( void ){
    memset( this , 0x00 , sizeof(*this));
  }

  systemtime::systemtime( const std::chrono::system_clock::time_point& tp ){
    std::time_t tick = std::chrono::system_clock::to_time_t(tp);
    struct tm tm_date;
    convert( tick , tm_date );
    wHour     = tm_date.tm_hour;
    wMinute   = tm_date.tm_min ;
    wDay      = tm_date.tm_mday;
    wMonth    = tm_date.tm_mon + 1;
    wSecond   = tm_date.tm_sec ;
    wYear     = tm_date.tm_year + 1900;
    wMilliseconds = std::chrono::duration_cast< std::chrono::milliseconds >(
        tp.time_since_epoch()).count() % 1000 ;    
  }
  
  std::chrono::system_clock::time_point systemtime::to_time_point( void ) const{
    std::time_t val = codex::time::days_between_year( 1970 , wYear );
    val += codex::time::days_between_month( wYear , 1 , wMonth );
    val += ( wDay - 1 );
    val *= ( 24 * 60 * 60 );
    val += ( wHour * 60 * 60 );
    val += ( wMinute * 60 );
    val += ( wSecond );
    std::chrono::system_clock::time_point tp = 
      std::chrono::system_clock::from_time_t( val );
    return tp + std::chrono::milliseconds( wMilliseconds );
  }
  namespace {
    static const int MONTH_TABLE [2][12] = {
      { 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 } , // common year
      { 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 } , // leap year
    };
  }
  //
  bool is_leap_year( const int year ) {
    if ( (year%4) == 0 ) {
      if ( (year%100) == 0 ) {
        if ( (year%400) == 0 ) {
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
  }

  // [ begin , end )
  int days_between_year( const int year_begin , const int year_end ){
    if ( year_end < year_begin )
      return 0;
    int year = year_begin;
    int tot = 0;
    while ( year < year_end ) {
      tot += is_leap_year( year ) ? 366 : 365;
      ++year;
    }
    return tot;
  }
  // [ begin , end )
  // month range : 1 ~ 12
  int days_between_month( const int year , const int month_begin , const int month_end ){
    if ( month_end < month_begin)
      return 0;
    int idx = is_leap_year(year) ? 1 : 0;
    int mon = month_begin;
    int tot = 0;
    while ( mon < month_end ) {
      tot += MONTH_TABLE[idx][mon-1];
      ++mon;
    }
    return tot;
  }
  //
  int days_in_a_month( const int year , const int month ){
    return MONTH_TABLE[ is_leap_year(year) ? 1 : 0][month-1];
  }

  void convert( const std::time_t t , struct tm& tm ){
    tm.tm_sec  = ( t % 60 );
    tm.tm_min  = ( t % ( 60 * 60 ) ) / 60;
    tm.tm_hour = ( t % ( 60 * 60 * 24 )) / ( 60 * 60 );
    tm.tm_wday = ((t / ( 60 * 60 * 24 )) + 4 ) % 7; // 0 day thursday

    int32_t daycount = static_cast< int32_t >( t / ( 60 * 60 * 24 ));
    int32_t year     = 1970;

    for(;;) {
      int32_t dayPerYear = is_leap_year( year ) ? 366 : 365;
      if ( daycount < dayPerYear )
        break;
      ++year;
      daycount -= dayPerYear;
    }

    tm.tm_year = static_cast< int > (year - 1900);
    tm.tm_yday = static_cast< int > (daycount);
    int32_t month = 0;
    int monthTableIndex =  is_leap_year( year ) ? 1 : 0;
    for(;;) {
      if ( daycount < MONTH_TABLE[ monthTableIndex ][ month ] ){
        break;
      }
      daycount -= MONTH_TABLE[ monthTableIndex ][ month ];
      ++month;
    }
    tm.tm_mon  = static_cast< int > (month);
    tm.tm_mday = static_cast< int > (daycount + 1);
    tm.tm_isdst = 0;
  }

}}
