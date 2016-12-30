#include <codex/mux/epoll.hpp>

#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

namespace codex { namespace mux {
namespace detail{

  static mux::interest event_to_interest( const epoll_event& e ) {
    mux::interest interest(( e.events & EPOLLIN ? mux::interest::k_read : 0 ) |
      ( e.events & EPOLLOUT ? mux::interest::k_write : 0 ));
    return interest;
  }

  static epoll_event interest_to_event( const interest& i ) {
    struct epoll_event e;
    e.events = 0;
    if ( i.check( mux::interest::events::k_read ) ) {
      e.events = EPOLLIN; 
    }
    if ( i.check( mux::interest::events::k_write ) ) {
      e.events |= EPOLLOUT; 
    }
    return e;
  }
}

  epoll::epoll( void ) 
    : _handle( epoll_create(256))
    , _event_fd( eventfd( 0 , O_NONBLOCK ))
    , _event_fd_handler( completion_handler::wrap_shared( 
          [this]( const interest& i ) {
            if ( i.check( interest::k_read ) ) {
              eventfd_t val = 0;
              eventfd_read( _event_fd , &val );
            }
          }))
  {
    struct epoll_event e;
    e.events = EPOLLIN;
    e.data.ptr = _event_fd_handler.get();
    epoll_ctl( _handle , EPOLL_CTL_ADD , _event_fd , &e );
  }

  epoll::~epoll( void ){
    ::close( _handle );
    ::close( _event_fd );
  }

  int epoll::bind( int fd 
      , const interest& interest 
      , completion_handler* handler )
  {
    struct epoll_event e = detail::interest_to_event( interest ); 
    e.data.ptr = handler;
    if ( epoll_ctl( _handle , EPOLL_CTL_MOD , fd , &e ) == 0 ){
      return 0;
    }
    if ( errno == ENOENT ) {
      if ( epoll_ctl( _handle , EPOLL_CTL_ADD , fd , &e ) == 0 ){
        return 0;
      }
    }
    return -1;  
  }

  void epoll::unbind( int fd ) {
    epoll_ctl( _handle , EPOLL_CTL_DEL , fd , nullptr );
  }

  int epoll::wait( const std::chrono::milliseconds& ms )
  {
    struct epoll_event events[256];
    int result = epoll_wait( _handle , events , 256 , ms.count() );
    if ( result == -1 ) {
      if ( errno == EINTR || errno == ETIMEDOUT ) 
        return 0;
      return -1;
    }
    for ( int i = 0 ; i < result ; ++i ) {
      interest intrst = detail::event_to_interest( events[i] );
      completion_handler* handler = static_cast< completion_handler* >( events[i].data.ptr );
      if ( handler ) {
        (*handler)( intrst );
      }
      }
    return result;
  }

  void epoll::notify( void ) {
    eventfd_t val = 1;
    eventfd_write( _event_fd , val );
  }

}}
