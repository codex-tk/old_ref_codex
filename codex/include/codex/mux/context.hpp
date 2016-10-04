/*
 */
#ifndef __codex_mux_context_h__
#define __codex_mux_context_h__

#include <cstdint>

namespace codex { namespace mux {

  class interest{
  public:
    enum events {
      k_ev_read = 0x01 ,
      K_ev_write = 0x02 , 
    };
  public:
    interest( void );
    interest( int ev );

    bool check( const interest::events e );
    void set( const interest::events e );
    void clear( const interest::events e );

    uint16_t lib_flags( void ) const;
    void lib_flags( const uint16_t d ); 
  private:
    int _flags;
  };

  class context;

  typedef void (*callback)( context* ctx , const mux::interest& intr ); 

  class context{
  public:
    context( void );
    void handler( callback handler ) ;
    mux::interest& interest( void );
    void operator()( const mux::interest& intr );
  private:
    callback _handler;
    mux::interest _interest;
  };

}}

#endif
