#pragma once

namespace nw {

	//template <bool b>
	//struct compile_assert {};

	//template <>
	//struct compile_assert<true>
	//{
	//	static inline void assert() {}
	//};

#define static_assert_vararg_type(vararg, type, message) \
static_assert((std::is_same<vararg, type>::value && ...), message)

#define static_assert_vararg_size(vararg, size, message) \
static_assert(sizeof...(vararg) == size, message)

} // namespace nw