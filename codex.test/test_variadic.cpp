#include <gtest/gtest.h>
#include "gprintf.hpp"

struct opt0{
  opt0(){}
  opt0( int o ){
    val = o;
  }
  int val;
};

struct opt1{
  opt1(){}
  opt1( int o ){
    val = o;
  }
  int val;
};

struct opt2{
  opt2( void ) {}
};

struct setting{
  template < class ... Args >
  setting( Args&& ... args ){
    impl( std::forward< Args >( args ) ... );
  }

  void impl( const opt0& o ) {
    gprintf( "opt0\n" ); 
    o0.val = o.val;
  }

  void impl( const opt1& o ) {
    gprintf( "opt1\n" ); 
    o1.val = o.val;
  }

  void impl( const opt2& o ) {
    gprintf( "opt2\n" ); 
  }

  template < class T , class ... Args >
  void impl( const T& t , Args&& ... args ){
    impl( t );
    impl( std::forward< Args >( args ) ... );
  }
  opt0 o0;
  opt1 o1;
};

TEST( variadic , opt ) {
  setting s( opt0( 1 ) , opt1( 2 ) ); 
  setting s2( opt1( 1 ) , opt1( 2 ) , opt2()); 
  ASSERT_EQ ( s.o0.val , 1 );
  ASSERT_EQ ( s.o1.val , 2 );
}
/*
template < class ... Types >
class Inherit;

template < class A , template < class T2 > class B , class ... Types >
class Inherit< A , B< A > , Types ... > : public Inherit< B< A > , Types ... >{
};

template < class A , template < class T > class B >
class Inherit< A , B<A> > : public Inherit < B< A > >{
};

template < class A >
class Inherit<A> : public A {
};


class I0 {
public:
  void i0(void){}
};

template < class T >
class I1 : public T {
public:
  void i1( void ){}
};

template < class T >
class I2 : public T {
public:
  void i2( void ){}
};

class Host : public Inherit< I0 , I1 , I2 >{

};

TEST( host , inherit ) {
  Host hos;
}
*/

