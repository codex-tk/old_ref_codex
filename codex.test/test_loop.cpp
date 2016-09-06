#include <gtest/gtest.h>
#include <codex/loop.hpp>

TEST( loop , post ) {
  codex::loop l;
  int test_value = 0;
  bool in_loop = false;
  l.post( [&] {
        test_value = 1;
        in_loop = l.in_loop();
      });

  ASSERT_EQ( test_value , 0 );
  l.run();
  ASSERT_EQ( test_value , 1 );
  ASSERT_EQ( in_loop , true );

  
}


