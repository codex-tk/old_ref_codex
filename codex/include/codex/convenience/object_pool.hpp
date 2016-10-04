/*!
 */
#ifndef __codex_object_pool_h__
#define __codex_object_pool_h__

#include <cstdint>
#include <mutex>

namespace codex {

  template < class Object , int AllocCount = 64 >
  class object_pool {
  protected:
    ~object_pool( void ) {
    }
  public:
    static void* operator new( size_t obj_size ){
      std::lock_guard< std::mutex > guard( _lock );
      static_assert( sizeof(Object) >= sizeof(void*)
          ,"Object Size Must be Greater than or Equal To Size Of void*" );
      if ( nullptr == _free_list ) {
        Object* ptr = static_cast< Object* >(
            std::malloc( sizeof( Object ) * AllocCount ));
        for ( int i = 0; i<AllocCount;++i){
          _push( ptr + i );
        }
      }
      uint8_t* ptr = _free_list;
      _free_list = *reinterpret_cast<uint8_t**>(ptr);
      *reinterpret_cast<uint8_t**>(ptr) = nullptr;
      return ptr; 
    }

    static void operator delete( void* obj ) {
      std::lock_guard< std::mutex > guard( _lock );
      _push( obj ); 
    }

  private:
    static void _push( void* ptr ){
      *reinterpret_cast< uint8_t**>(ptr) = _free_list; 
      _free_list = static_cast< uint8_t* >(ptr);
    }
  private:
    static std::mutex _lock;
    static uint8_t* _free_list;
  };

  template < class Object , int  AllocCount >
  uint8_t* object_pool< Object , AllocCount >::_free_list = nullptr;

  template < class Object , int  AllocCount >
  std::mutex object_pool< Object , AllocCount >::_lock;


}

#endif
