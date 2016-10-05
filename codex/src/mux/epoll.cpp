#include <codex/mux/epoll.hpp>

#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

namespace codex { namespace mux {
namespace detail{

  static mux::interest events_to_interest( int events ) {
    return mux::interest(( events & EPOLLIN ? mux::interest::k_read : 0 ) |
      ( events & EPOLLOUT ? mux::interest::k_write : 0 ));
  }

}

  epoll::epoll( void ) 
    : _handle( epoll_create(256))
    , _event_fd( eventfd( 0 , O_NONBLOCK ))
  {
    struct epoll_event e;
    e.events = EPOLLIN;
    e.data.ptr = nullptr;
    epoll_ctl( _handle , EPOLL_CTL_ADD , _event_fd , &e );
  }

  epoll::~epoll( void ){
    ::close( _handle );
    ::close( _event_fd );
  }

  int epoll::bind( int fd , context* ctx ) {
    struct epoll_event e;
    e.events = 0;
    e.data.ptr = ctx;
    if ( ctx->interest().check( mux::interest::events::k_read ) ) {
      e.events = EPOLLIN; 
    }
    if ( ctx->interest().check( mux::interest::events::k_write ) ) {
      e.events |= EPOLLOUT; 
    }
    if ( ctx->interest().lib_flags() == 1 ) {
      if ( epoll_ctl( _handle , EPOLL_CTL_MOD , fd , &e ) == 0 ){
        return 0;
      }
    } 
    if ( epoll_ctl( _handle , EPOLL_CTL_MOD , fd , &e ) == 0 ){
      return 0;
    }
    if ( errno == ENOENT ) {
      if ( epoll_ctl( _handle , EPOLL_CTL_ADD , fd , &e ) == 0 ){
        ctx->interest().lib_flags(1);
        return 0;
      }
    }
    return -1;  
  }

  void epoll::unbind( int fd , context* ctx ) {
    ctx->interest().lib_flags(0);
    epoll_ctl( _handle , EPOLL_CTL_DEL , fd , nullptr );
  }

  int epoll::wait( const std::chrono::milliseconds& ms ){
    struct epoll_event events[256];
    int result = epoll_wait( _handle , events , 256 , ms.count() );
    if ( result == -1 ) {
      if ( errno == EINTR || errno == ETIMEDOUT ) 
        return 0;
      return -1;
    }
    
    for ( int i = 0 ; i < result ; ++i ) {
      mux::context* ctx = static_cast< mux::context* >( events[i].data.ptr );
      if ( ctx ) {
        (*ctx)( detail::events_to_interest( events[i].events ) );
      } else {
        eventfd_t val = 0;
        eventfd_read( _event_fd , &val );
      } 
    }
    return result;
  }

  void epoll::notify( void ) {
    eventfd_t val = 1;
    eventfd_write( _event_fd , val );
  }

}}
