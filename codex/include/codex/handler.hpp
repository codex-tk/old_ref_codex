/*!
 */
#ifndef __codex_handler_h__
#define __codex_handler_h__

#include <memory>
#include <codex/next_prop_injection.hpp>

namespace codex {

  /*!
   * variadic template sample code
   * use std::function< Signature > instead of codex::handler< Signature >
   */
  template < class Signature >
  class callback;

  template < class R , class ...Args>
  class callback< R ( Args... ) > {
  public:
    callback( void ) = default; 
    virtual ~callback( void ) = default;
    virtual R operator()( Args&&... arg ) = 0; 
  public:
    template < class Callback >
    static std::shared_ptr< callback > wrap( Callback&& c0 ){
      class callback_impl : public callback{
      public:
        callback_impl( Callback&& c ) 
          : _callback( std::forward<Callback>( c ) ){
        }
        virtual ~callback_impl( void ) {
        }
        virtual R operator()( Args&&... arg ) {
          return _callback( std::forward< Args >(arg)... );  
        }
      private:
        Callback _callback;
      };
      return std::make_shared< callback_impl >( std::forward< Callback >( c0 )); 
    }
  };

  template < class Signature >
  class handler;

  template < class R , class ...Args>
  class handler< R ( Args... ) > {
  public:
    typedef callback< R ( Args ... ) > callback_type;

    handler( void ) {
    }

    template < class Callback >
    handler( Callback&& c0 ) 
       : _callback( callback_type::wrap( std::forward< Callback >(c0)))
    {
    }

    ~handler( void ) = default;

    R operator()( Args&&... arg ){
      if ( !_callback ) 
        return R();
      return (*_callback)( std::forward< Args >( arg )... );
    }
  private:
    std::shared_ptr< callback_type > _callback;
  };

  template < class Signature >
  class callback0;

  template < class R , class ...Args >
  class callback0< R ( Args... ) > {
  public:
    callback0( void ) : _next( nullptr ) {}
    virtual ~callback0( void ) = default;
    virtual R operator()( Args&&... arg ) = 0; 
    callback0* next( void ) { return _next;}
    callback0* next( callback0* n ) { std::swap( _next , n ); return n; }
  private:
    callback0* _next;
  public:
    template < class Callback >
    static callback0* wrap( Callback&& c0 ){
      class callback_impl : public callback0{
      public:
        callback_impl( Callback&& c ) 
          : _callback( std::forward<Callback>( c ) ){
        }
        virtual ~callback_impl( void ) {
        }
        virtual R operator()( Args&&... arg ) {
          return _callback( std::forward< Args >(arg)... );  
        }
      private:
        Callback _callback;
      };
      return new callback_impl( std::forward< Callback >( c0 )); 
    }
  };
}

#endif
