#include <codex/mux/context.hpp>

namespace codex { namespace mux {

  interest::interest( void ) 
    : _flags(0)
  {
  }

  interest::interest( int ev ) 
    : _flags(0)
  {
    _flags = ev;
  }

  bool interest::check( interest::events e ){
    return _flags & static_cast<int>(e);
  }

  void interest::set( interest::events e ){
    _flags |= static_cast<int>(e);
  }

  void interest::clear( interest::events e ){
    _flags &= ~static_cast<int>(e);
    _flags & static_cast<int>(e);
  }

  uint16_t interest::lib_flags( void ) const {
    return ( _flags >> 16 ) & 0xffff;
  }
  
  void interest::lib_flags( const uint16_t d ) {
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

}}
