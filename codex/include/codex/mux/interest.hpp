/*
 */
#ifndef __codex_mux_interest_h__
#define __codex_mux_interest_h__

#include <cstdint>
#include <codex/handler.hpp>

namespace codex { namespace mux {

  class interest;

  typedef codex::callback< void ( const interest& i ) > completion_handler; 

  class interest{
  public:
    enum events {
      k_read = 0x01 ,
      k_write = 0x02 , 
    };
  public:
    interest( void );
    interest( int ev );

    interest( const interest& rhs );
    interest& operator=( const interest& rhs );

    bool check( const interest::events e ) const;
    void set( const interest::events e );
    void clear( const interest::events e );
  private:
    int _flags;
  };

}}

#endif
