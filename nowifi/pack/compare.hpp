#pragma once


namespace nw {

	namespace Compare {
		
		template <class Ty1, class Ty2>
		bool less(const Ty1 arg1, const Ty2 arg2)
		{
			return arg1 < arg2;
		}

		template <class Ty1, class Ty2, class... Args>
		bool less(const Ty1 arg1, const Ty2 arg2, const Args... args)
		{
			return (arg1 < arg2) && less(arg2, args...);
		}

		template <class Ty1, class Ty2>
		bool less_eq(const Ty1 arg1, const Ty2 arg2)
		{
			return arg1 <= arg2;
		}

		template <class Ty1, class Ty2, class... Args>
		bool less_eq(const Ty1 arg1, const Ty2 arg2, const Args... args)
		{
			return (arg1 <= arg2) && less_eq(arg2, args...);
		}

		template <class Ty1, class Ty2>
		bool equal(const Ty1 arg1, const Ty2 arg2)
		{
			return arg1 == arg2;
		}

		template <class Ty1, class Ty2, class... Args>
		bool equal(const Ty1 arg1, const Ty2 arg2, const Args... args)
		{
			return (arg1 == arg2) && equal(arg2, args...);
		}

		template <class Ty1, class Ty2>
		bool greater(const Ty1 arg1, const Ty2 arg2)
		{
			return arg1 > arg2;
		}

		template <class Ty1, class Ty2, class... Args>
		bool greater(const Ty1 arg1, const Ty2 arg2, const Args... args)
		{
			return (arg1 > arg2) && greater(arg2, args...);
		}

		template <class Ty1, class Ty2>
		bool greater_eq(const Ty1 arg1, const Ty2 arg2)
		{
			return arg1 >= arg2;
		}

		template <class Ty1, class Ty2, class... Args>
		bool greater_eq(const Ty1 arg1, const Ty2 arg2, const Args... args)
		{
			return (arg1 >= arg2) && greater_eq(arg2, args...);
		}

		template <class... Args>
		bool all_true(const Args... args)
		{
			return (true && ... && args);
		}

		template <class... Args>
		bool any_true(const Args... args)
		{
			return (false || ... || args);
		}

		namespace ref {
		
			template <class Ty1, class Ty2>
			bool less(const Ty1& arg1, const Ty2& arg2)
			{
				return arg1 < arg2;
			}

			template <class Ty1, class Ty2, class... Args>
			bool less(const Ty1& arg1, const Ty2& arg2, const Args&... args)
			{
				return (arg1 < arg2) && less(arg2, args...);
			}

			template <class Ty1, class Ty2>
			bool less_eq(const Ty1& arg1, const Ty2& arg2)
			{
				return arg1 <= arg2;
			}

			template <class Ty1, class Ty2, class... Args>
			bool less_eq(const Ty1& arg1, const Ty2& arg2, const Args&... args)
			{
				return (arg1 <= arg2) && less_eq(arg2, args...);
			}

			template <class Ty1, class Ty2>
			bool equal(const Ty1& arg1, const Ty2& arg2)
			{
				return arg1 == arg2;
			}

			template <class Ty1, class Ty2, class... Args>
			bool equal(const Ty1& arg1, const Ty2& arg2, const Args&... args)
			{
				return (arg1 == arg2) && equal(arg2, args...);
			}

			template <class Ty1, class Ty2>
			bool greater(const Ty1& arg1, const Ty2& arg2)
			{
				return arg1 > arg2;
			}

			template <class Ty1, class Ty2, class... Args>
			bool greater(const Ty1& arg1, const Ty2& arg2, const Args&... args)
			{
				return (arg1 > arg2) && greater(arg2, args...);
			}

			template <class Ty1, class Ty2>
			bool greater_eq(const Ty1& arg1, const Ty2& arg2)
			{
				return arg1 >= arg2;
			}

			template <class Ty1, class Ty2, class... Args>
			bool greater_eq(const Ty1& arg1, const Ty2& arg2, const Args&... args)
			{
				return (arg1 >= arg2) && greater_eq(arg2, args...);
			}

			template <class... Args>
			bool all_true(const Args&... args)
			{
				return (true && ... && args);
			}

			template <class... Args>
			bool any_true(const Args&... args)
			{
				return (false || ... || args);
			}

		} // namespace ref
		
	} // namespace Compare

} // namespace nw