#include <codex/loop.hpp>

namespace codex {

  loop::loop( void ) {
  }

  loop::~loop( void ) {
  }

  void loop::post0( loop::operation_type* op ) {
    std::lock_guard< std::mutex > guard( _lock );
    _ops.add_tail( op );
    _mux.notify();
  }

  void loop::run( void ) {
    _tid = std::this_thread::get_id();
    _mux.wait( std::chrono::milliseconds(-1));
    codex::slist< loop::operation_type > drain_ops;
    do {
      std::lock_guard< std::mutex > guard( _lock );
      _ops.swap(drain_ops);
    }while(0);
    while ( drain_ops.head() ) {
      operation_type* op = drain_ops.head();
      drain_ops.remove_head();
      (*op)();
      delete op;
    }
    _tid = std::thread::id();
  }

  bool loop::in_loop( void ) {
    return _tid == std::this_thread::get_id();
  }

  codex::mux::implementation& loop::mux( void ){  
    return _mux;
  }
}
