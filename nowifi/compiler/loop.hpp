#pragma once

#define LOOP1(CODE) CODE
#define LOOP2(CODE) CODE LOOP1( CODE )
#define LOOP3(CODE) CODE LOOP2( CODE )

#define LOOP(N, CODE) LOOP ## n(a)

namespace nw {

	template <size_t N>
	struct loop
	{
		template <class Func>
		static inline void call(Func const& f)
		{
			f();
			loop<N - 1>::call(f);
		}
	};

	template <>
	struct loop <0u>
	{
		template <class Func>
		static inline void call(Func const& f) { }
	};

} // namespace nw