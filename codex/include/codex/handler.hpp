/*!
 */
#ifndef __codex_handler_h__
#define __codex_handler_h__

#include <memory>

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
      class callback0 : public callback{
        public:
          callback0( Callback&& c ) 
            : _callback( std::forward<Callback>( c ) ){
          }
          virtual ~callback0( void ) {
          }
          virtual R operator()( Args&&... arg ) {
            return _callback( std::forward< Args >(arg)... );  
          }
        private:
          Callback _callback;
      };
      return std::make_shared< callback0 >( std::forward< Callback >( c0 )); 
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
    // if requred impl assign / copy .. blah blah blah ..
  private:
    std::shared_ptr< callback_type > _callback;
  };
}

#endif
