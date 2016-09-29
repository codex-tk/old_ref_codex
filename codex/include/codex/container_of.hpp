#ifndef __codex_container_of_h__
#define __codex_container_of_h__

#include <codex/predefs.hpp>

/// codex namespace
namespace codex {

	// from boost::intrinsic
	template<class Parent, class Member>
	std::ptrdiff_t offset_of(const Member Parent::*ptr_to_member) {
		const Parent * const parent = nullptr;
		const char *const member = static_cast<const char*>(
			static_cast<const void*>(&(parent->*ptr_to_member)));
		std::ptrdiff_t val(member - static_cast<const char*>(
			static_cast<const void*>(parent)));
		return val;
	}

  /**
   * struct sample{
   *    int context; 
   * };
   *
   * void sample_func( int* ctx ) {
   *    sample* psample = container_of( ctx , &sample::context );
   * }
   */

	template<class Parent, class Member>
	inline Parent* container_of(Member *member, const Member Parent::* ptr_to_member)
	{
		return static_cast<Parent*>(
			static_cast<void*>(
				static_cast<char*>(
					static_cast<void*>(member)) - offset_of(ptr_to_member)
				)
			);
	}

	template<class Parent, class Member>
	inline const Parent *container_of(const Member *member, const Member Parent::* ptr_to_member)
	{
		return static_cast<const Parent*>(
			static_cast<const void*>(
				static_cast<const char*>(static_cast<const void*>(member)) - offset_of(ptr_to_member)
				)
			);
	}
}

#endif
