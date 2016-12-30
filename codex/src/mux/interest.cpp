#include <codex/mux/interest.hpp>

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

}}
