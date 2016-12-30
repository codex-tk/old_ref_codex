/**
 */
#ifndef __codex_mux_epoll_h__
#define __codex_mux_epoll_h__

#include <codex/mux/interest.hpp>
#include <chrono>

namespace codex { namespace mux { 

  class epoll{
  public:
    epoll( void );
    ~epoll( void );

    int bind( int fd 
        , const interest& interest 
        , completion_handler* handler );
    void unbind( int fd );

    int wait( const std::chrono::milliseconds& ms );

    void notify( void );
  private:
    int _handle;
    int _event_fd;
    std::shared_ptr< completion_handler > _event_fd_handler;
  };
}}

#endif
