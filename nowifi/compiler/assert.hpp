#pragma once

namespace nw {

	template <bool b>
	struct compile_assert {};

	template <>
	struct compile_assert<true>
	{
		static inline void assert() {}
	};

} // namespace nw