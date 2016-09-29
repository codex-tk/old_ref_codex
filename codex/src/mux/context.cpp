#include <codex/mux/context.hpp>

namespace codex { namespace mux {
  static const int kReadFlag = 0x01;
  static const int kWriteFlag = 0x02;

  interest::interest( void ) 
    : _flags(0)
  {
  }
  interest::interest( bool rd , bool wr ) 
    : _flags(0)
  {
    if ( rd ) _flags |= kReadFlag;
    if ( wr ) _flags |= kWriteFlag;
  }

  bool interest::readable( void ) const {
    return _flags & kReadFlag;
  }

  void interest::readable( bool value ) {
    if ( value ) _flags |= kReadFlag;
    else _flags &= ~kReadFlag;
  }

  bool interest::writable( void ) const {
    return _flags & kWriteFlag;
  }

  void interest::writable( bool value ) {
    if ( value ) _flags |= kWriteFlag;
    else _flags &= ~kWriteFlag;
  }

  uint16_t interest::user_data( void ) const {
    return ( _flags >> 16 ) & 0xffff;
  }
  
  void interest::user_data( const uint16_t d ) 
  {
    _flags = (d << 16) | (_flags & 0xffff);
  }

  context::context( void )
    : _handler(nullptr)
  {
  }

  void context::handler( mux::callback handler ){
    _handler = handler;
  }

  mux::interest& context::interest( void ) {
    return _interest;
  }
  
  void context::operator()( const mux::interest& i ) {
    if ( _handler )
      _handler(this , i);
  }

  bool context::registered( void ){
    return _interest.user_data() != 0;
  }

  void context::registered( bool v ) {
    uint16_t value = v ? 1 : 0;
    _interest.user_data( value );
  }
}}
