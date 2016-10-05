/*!
 */
#ifndef __codex_ip_address_h__
#define __codex_ip_address_h__

#include <codex/codex.hpp>
#if !defined( __codex_win32__ )
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/un.h>
#endif

namespace codex { namespace ip {

  namespace detail{
    template < class Sockaddr >
    class string_helper;
  }

  template < int Type , int Proto , class SockAddr = struct sockaddr_storage >
  class address {
  public:
    address( void )
      : _length( sizeof( _impl )) {
      memset( &_impl , 0x00 , _length );
    }
    address( const struct sockaddr* ptr , const socklen_t len )
      : _length( len )
    {
      memcpy( &_impl , ptr , _length ); 
    }
    address( const address& rhs )
      : _length( rhs._length )
    {
      memcpy( &_impl , &rhs._impl , _length ); 
    }

    address( int af , int port ){
      switch( af ) { 
        case AF_INET: {
          struct sockaddr_in addr; 
          memset( &addr , 0x00 , sizeof(addr));
          addr.sin_addr.s_addr = INADDR_ANY;
          addr.sin_port = htons( (uint16_t)port);
          addr.sin_family = AF_INET;
          memcpy( &_impl , &addr , sizeof(addr));
          _length = sizeof(addr);
        }
          break;
        case AF_INET6:{
          // todo
        }
          break;
      }
    }

    address& operator=( const address& rhs ){
      memcpy( &_impl , &rhs._impl , rhs._length );
      _length = rhs._length;
      return *this;
    }

    ~address( void ){
    }

    struct sockaddr* sockaddr( void ) const{
      return reinterpret_cast< struct sockaddr* >(
          const_cast< SockAddr* >( &_impl ));
    }
    socklen_t& length( void ){
      return length();
    }

    int address_family( void ) const{
      return static_cast< struct sockaddr_in* >(sockaddr())->sin_family;
    }
    int port( void ) const{
      return ntohs(reinterpret_cast< struct sockaddr_in* >(sockaddr())->sin_port);
    }
    int type( void ) const{
      return Type;
    }

    int protocol( void ) const{
      return Proto;
    }

    std::string to_string( void ) const{
      return ip::detail::string_helper<SockAddr>::to_string( _impl );
    }
  public:
    static std::vector< address > resolve( const char* name 
        , int port , int address_family = AF_UNSPEC )
    {
      struct addrinfo hints;
      struct addrinfo* result = nullptr;
      struct addrinfo* rp = nullptr;

      memset( &hints , 0x00 , sizeof( hints ));

      hints.ai_flags = AI_PASSIVE;
      hints.ai_family = address_family;
      hints.ai_socktype = SOCK_STREAM;

      char port_s[16];

      sprintf( port_s , "%d" , port );

      std::vector< address > resolved;
      if ( getaddrinfo( name , port_s , &hints , &result ) != 0 )
        return resolved;

      for ( rp = result ; rp != nullptr ; rp = rp->ai_next ){
        address a( rp->ai_addr , (int)(rp->ai_addrlen));
        resolved.push_back( a );
      }
      freeaddrinfo( result );
      return resolved;  
    }

    static address from_ip( const char* ip , const int port ){
      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip);
      addr.sin_port = htons( port );
      return address( reinterpret_cast< struct sockaddr* >(&addr) , sizeof(addr));
    }
  private:
    SockAddr _impl; 
    socklen_t _length;
  };

  namespace tcp {
    using address = ip::address< SOCK_STREAM , IPPROTO_TCP >;
  }
  namespace udp{
    using address = ip::address< SOCK_DGRAM , IPPROTO_UDP >;
  }

  namespace detail{
    
    template < class Sockaddr >
    class string_helper;

    template <>
    class string_helper< struct sockaddr_storage >{
    public:
      static const char* inet_ntop(int af, const void *src, char *dst, socklen_t cnt) {
        sockaddr_storage storage;
        int size = 0;
        switch( af ) {
          case AF_INET:
            {
              sockaddr_in* addr = reinterpret_cast< sockaddr_in* >(&storage);
              addr->sin_family = AF_INET;
              size = sizeof( sockaddr_in );
              memcpy(&addr->sin_addr, src, sizeof(in_addr));
            }
            break;
          case AF_INET6:
            {
              sockaddr_in6* addr = reinterpret_cast< sockaddr_in6* >(&storage);
              addr->sin6_family = AF_INET6;
              size = sizeof( sockaddr_in6 );
              memcpy(&addr->sin6_addr, src, sizeof(in6_addr));
            }
            break;
          default:
            return dst;
        }
#if defined( _WIN32 )
        if ( GetNameInfoA(  
#else
        if ( getnameinfo(
#endif                
            reinterpret_cast< struct sockaddr*>(&storage) , 
            size , dst , 
            cnt , nullptr , 
            0 , NI_NUMERICHOST ) != 0 ) {
        }
        return dst;
      }

      static std::string to_string( const sockaddr_storage& impl ){
        char str[NI_MAXHOST] = { 0 , };
        struct sockaddr_in* addr = reinterpret_cast< struct sockaddr_in* >(
            const_cast< sockaddr_storage* >( &impl ));
        return std::string( inet_ntop( addr->sin_family 
              , &(addr->sin_addr )
              , str 
              , NI_MAXHOST ));
      }
    };

    template <>
    class string_helper< struct sockaddr_un >{
    public:
      static std::string to_string( const sockaddr_un& impl ){
        return std::string( impl.sun_path ); 
      }
    };
  }

}}

#endif
