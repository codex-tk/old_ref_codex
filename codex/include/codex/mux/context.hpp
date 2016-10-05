/*
 */
#ifndef __codex_mux_context_h__
#define __codex_mux_context_h__

#include <cstdint>

namespace codex { namespace mux {

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

    uint16_t lib_flags( void ) const;
    void lib_flags( const uint16_t d ); 
  private:
    int _flags;
  };

  template < class Handler >
  class basic_context{
  public:
    basic_context( void ) {
    }
    void handler( const Handler handler ){
      _handler = handler;
    }
    mux::interest& interest( void ){
      return _interest;
    }
    void operator()( const mux::interest& intr ){
      _handler(this,intr);
    }
  private:
    Handler _handler;
    mux::interest _interest;
  };

  typedef void (*callback)( void* ctx , const mux::interest& intr ); 

  typedef basic_context< callback > context;


}}

#endif
