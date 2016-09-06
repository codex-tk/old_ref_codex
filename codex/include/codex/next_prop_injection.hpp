/*!
 */
#ifndef __codex_next_prop_injection_h__
#define __codex_next_prop_injection_h___

namespace codex {

  template < class T >
  struct next_prop_injection {
    class impl_type: public T {
    public:
      template < class ...Args >
      impl_type( Args&&... arg ) 
      : T( std::forward< Args >(arg)...)
        , _next(nullptr)
      {
      }
      T* next( void ) { return _next;}
      T* next( T* n ) { std::swap( _next , n ); return n; }
    private:
      T* _next;
    };
    typedef impl_type type;
  };

}

#endif
