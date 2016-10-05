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

  interest::interest( const interest& rhs ) 
    : _flags( rhs._flags ){}

  interest& interest::operator=( const interest& rhs ){
    _flags = rhs._flags;
    return *this;
  }
  bool interest::check( interest::events e ) const {
    return _flags & static_cast<int>(e);
  }

  void interest::set( interest::events e ){
    _flags |= static_cast<int>(e);
  }

  void interest::clear( interest::events e ){
    _flags &= ~static_cast<int>(e);
  }

  uint16_t interest::lib_flags( void ) const {
    return ( _flags >> 16 ) & 0xffff;
  }
  
  void interest::lib_flags( const uint16_t d ) {
    _flags = (d << 16) | (_flags & 0xffff);
  }

}}
