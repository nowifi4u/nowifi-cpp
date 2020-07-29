#pragma once

namespace nw {

	template <bool state>
	struct ternary_exec
	{
		template <class Func1, class Func2>
		static inline void exec(Func1 f1, Func2 f2);
	};

	template <>
	struct ternary_exec <true>
	{
		template <class Func1, class Func2>
		static inline void exec(Func1 f1, Func2 f2)
		{
			f1();
		}
	};

	template <>
	struct ternary_exec <false>
	{
		template <class Func1, class Func2>
		static inline void exec(Func1 f1, Func2 f2)
		{
			f2();
		}
	};

} // namespace nw