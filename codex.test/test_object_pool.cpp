#include <gtest/gtest.h>
#include <codex/convenience/object_pool.hpp>
#include "gprintf.hpp"

class pooled_object : public codex::object_pool< pooled_object >{

private:
  void* _dummy;
};

TEST( object_pool , single ) {
  pooled_object* first_object = new pooled_object();

  delete first_object;

  pooled_object* second_object = new pooled_object();
  ASSERT_EQ( first_object , second_object );
}

TEST( object_pool , many ) {
  std::set< pooled_object* > pooled_objects;
  for( int i = 0 ; i < 1024 ; ++i ) {
    pooled_object* po = new pooled_object();
    ASSERT_TRUE( pooled_objects.find( po ) == pooled_objects.end());
    pooled_objects.insert( po );
  }
  for ( auto it : pooled_objects) {
    delete it;
  }
  std::vector< pooled_object* > pooled_objects0;
  for( int i = 0 ; i < 1024 ; ++i ) {
    pooled_object* po = new pooled_object();
    ASSERT_TRUE( pooled_objects.find( po ) != pooled_objects.end());
    pooled_objects.erase( po );
    pooled_objects0.push_back(po);
  }

  while ( !pooled_objects0.empty()){
    pooled_object* po = pooled_objects0.back();
    pooled_objects0.pop_back();
    delete po;
  }

}


