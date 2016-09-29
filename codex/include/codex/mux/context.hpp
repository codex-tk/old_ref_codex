/*
 */
#ifndef __codex_mux_context_h__
#define __codex_mux_context_h__

#include <cstdint>

namespace codex { namespace mux {

  class interest{
  public:
    interest( void );
    interest( bool rd , bool wr );

    bool readable( void ) const ;
    void readable( bool value ) ;
    bool writable( void ) const ;
    void writable( bool value ) ;
    uint16_t user_data( void ) const;
    void user_data( const uint16_t d ); 
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
    bool registered( void );
    void registered( bool v );
  private:
    callback _handler;
    mux::interest _interest;
  };

}}

#endif
