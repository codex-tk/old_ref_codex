/*!
 */
#ifndef __codex_loop_h__
#define __codex_loop_h__

#include <codex/handler.hpp>
#include <codex/slist.hpp>
#include <mutex>
#include <thread>

namespace codex {

  class loop {
  public:
    typedef codex::callback0< void () > operation_type;

    loop( void );
    ~loop( void );

    template < class Callback >
    void post( Callback&& c0 ) {
      post0( operation_type::wrap( std::forward< Callback >(c0))); 
    }

    void post0( operation_type* op );
    
    template < class Callback >
    void dispatch( Callback&& c0 ) {
      if ( in_loop() ) {
        c0(); 
      } else {
        post( std::forward< Callback >(c0));
      }
    }

    void run( void );

    bool in_loop( void );
  private:
    std::mutex _lock;
    codex::slist< operation_type > _ops; 
    std::thread::id _tid;
  };

}

#endif
