/**
 */
#ifndef __codex_mux_epoll_h__
#define __codex_mux_epoll_h__

#include <codex/mux/context.hpp>

namespace codex { namespace mux { 

  class epoll{
  public:
    epoll( void );
    ~epoll( void );

    int add( int fd , context* ctx );
    int mod( int fd , context* ctx );
    void del( int fd );

  private:
    int _handle;
  };

}}

#endif
