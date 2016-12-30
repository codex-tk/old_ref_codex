#include <gtest/gtest.h>
#include <codex/codex.hpp>
#include <codex/container_of.hpp>
#include <codex/mux/epoll.hpp>
#include <thread>

TEST( epoll , notify ){
  codex::mux::epoll ep;
  std::thread thr([&] {
        for ( int i = 0 ; i < 5 ; ++i ) {
          std::this_thread::sleep_for( std::chrono::milliseconds(30));
          ep.notify();
        }
      });

  for ( int i = 0 ; i < 5 ; ++i ) {
    ASSERT_EQ( ep.wait( std::chrono::milliseconds(-1) ) , 1 );
  }
  thr.join();
}

namespace {

struct context0 {
  int value;
};

}

TEST( epoll , ev ) {
  codex::mux::epoll ep;
  int p[2];
  pipe(p);
  context0 c;
  c.value = 0;
  codex::mux::interest interest;
  interest.set( codex::mux::interest::k_read );
  codex::mux::completion_handler* handler 
    = codex::mux::completion_handler::wrap( [&c]( const codex::mux::interest& i ) {
          if ( i.check( codex::mux::interest::k_read )){
            c.value += 1; 
          }
        });
  ep.bind( p[0] , interest ,  handler );

  ASSERT_EQ( ep.wait( std::chrono::milliseconds(20)) , 0 );
  ASSERT_EQ( ep.wait( std::chrono::milliseconds(20)) , 0 );
  write( p[1] , p , 1 );

  ASSERT_EQ( ep.wait( std::chrono::milliseconds(20)) , 1 );
  ASSERT_EQ( c.value , 1 );
  ASSERT_EQ( ep.wait( std::chrono::milliseconds(20)) , 1 );
  ASSERT_EQ( c.value , 2 );

  int buf;
  read( p[0] , &buf , 1 );

  ASSERT_EQ( ep.wait( std::chrono::milliseconds(20)) , 0 );
  ASSERT_EQ( ep.wait( std::chrono::milliseconds(20)) , 0 );

  delete handler;
}
