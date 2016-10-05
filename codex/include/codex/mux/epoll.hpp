/**
 */
#ifndef __codex_mux_epoll_h__
#define __codex_mux_epoll_h__

#include <codex/mux/context.hpp>
#include <chrono>

namespace codex { namespace mux { 

  class epoll{
  public:
    epoll( void );
    ~epoll( void );

    int bind( int fd , context* ctx );
    void unbind( int fd , context* ctx );

    int wait( const std::chrono::milliseconds& ms );

    void notify( void );
  private:
    int _handle;
    int _event_fd; 
  };

}}

#endif
