#include <gtest/gtest.h>
#include <codex/handler.hpp>

TEST( handler , h0 ) {
  auto func = codex::callback< int () >::wrap( [] () -> int  {
        return 81;
      });

  codex::handler< int () > h( [] () -> int  {
        return 82;
      });

  ASSERT_EQ( (*func)() , 81 ); 
  ASSERT_EQ( h() , 82 ); 
}
