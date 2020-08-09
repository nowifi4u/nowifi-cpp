#pragma once


#include <nowifi/math/math.hpp>
#include <utility>
#include <type_traits>


namespace nw {

	namespace Compare {
		
		template <class Ty1, class Ty2>
		_NODISCARD _CONSTEXPR17 inline bool less(Ty1 arg1, Ty2 arg2)
		{
			return arg1 < arg2;
		}

		template <class Ty1, class Ty2, class... Args>
		_NODISCARD _CONSTEXPR17 inline bool less(Ty1 arg1, Ty2 arg2, Args... args)
		{
			return less(arg1, arg2) && less(arg2, args...);
		}

		template <class Ty1, class Ty2>
		_NODISCARD _CONSTEXPR17 inline bool less_eq(Ty1 arg1, Ty2 arg2)
		{
			return arg1 <= arg2;
		}

		template <class Ty1, class Ty2, class... Args>
		_NODISCARD _CONSTEXPR17 inline bool less_eq(Ty1 arg1, Ty2 arg2, Args... args)
		{
			return less_eq(arg1, arg2) && less_eq(arg2, args...);
		}

		template <class Ty1, class Ty2>
		_NODISCARD _CONSTEXPR17 inline bool equal(Ty1 arg1, Ty2 arg2)
		{
			return arg1 == arg2;
		}

		template <class Ty1, class Ty2, class... Args>
		_NODISCARD _CONSTEXPR17 inline bool equal(Ty1 arg1, Ty2 arg2, Args... args)
		{
			return equal(arg1, arg2) && equal(arg2, args...);
		}

		template <class Ty1, class Ty2>
		_NODISCARD _CONSTEXPR17 inline bool greater(Ty1 arg1, Ty2 arg2)
		{
			return arg1 > arg2;
		}

		template <class Ty1, class Ty2, class... Args>
		_NODISCARD _CONSTEXPR17 inline bool greater(Ty1 arg1, Ty2 arg2, Args... args)
		{
			return greater(arg1, arg2) && greater(arg2, args...);
		}

		template <class Ty1, class Ty2>
		_NODISCARD _CONSTEXPR17 inline bool greater_eq(Ty1 arg1, Ty2 arg2)
		{
			return arg1 >= arg2;
		}

		template <class Ty1, class Ty2, class... Args>
		_NODISCARD _CONSTEXPR17 inline bool greater_eq(Ty1 arg1, Ty2 arg2, Args... args)
		{
			return greater_eq(arg1, arg2) && greater_eq(arg2, args...);
		}

		template <class... Args>
		_NODISCARD _CONSTEXPR17 inline bool all_true(Args... args)
		{
			return (true && ... && args);
		}

		template <class... Args>
		_NODISCARD _CONSTEXPR17 inline bool any_true(Args... args)
		{
			return (false || ... || args);
		}

		template <class Ty, class... Args>
		_NODISCARD _CONSTEXPR17 inline Ty min(Ty arg1, Args... args)
		{
			return (arg1, ..., (arg1 = (args < arg1 ? args : arg1)));
		}

		template <class Ty, class... Args>
		_NODISCARD _CONSTEXPR17 inline Ty max(Ty arg1, Args... args)
		{
			return (arg1, ..., (arg1 = (args > arg1 ? args : arg1)));
		}

		template <class Ty, class... Args>
		_NODISCARD _CONSTEXPR17 inline std::pair<Ty, Ty> minmax(Ty arg1, Args... args)
		{
			return std::make_pair<Ty, Ty>(
				Compare::min(arg1, args...), 
				Compare::max(arg1, args...)
				);
		}

		namespace constref {
		
			template <class Ty1, class Ty2>
			_NODISCARD inline bool less(const Ty1& arg1, const Ty2& arg2)
			{
				return arg1 < arg2;
			}

			template <class Ty1, class Ty2, class... Args>
			_NODISCARD inline bool less(const Ty1& arg1, const Ty2& arg2, const Args&... args)
			{
				return less(arg1, arg2) && less(arg2, args...);
			}

			template <class Ty1, class Ty2>
			_NODISCARD inline bool less_eq(const Ty1& arg1, const Ty2& arg2)
			{
				return arg1 <= arg2;
			}

			template <class Ty1, class Ty2, class... Args>
			_NODISCARD inline bool less_eq(const Ty1& arg1, const Ty2& arg2, const Args&... args)
			{
				return less_eq(arg1, arg2) && less_eq(arg2, args...);
			}

			template <class Ty1, class Ty2>
			_NODISCARD inline bool equal(const Ty1& arg1, const Ty2& arg2)
			{
				return arg1 == arg2;
			}

			template <class Ty1, class Ty2, class... Args>
			_NODISCARD inline bool equal(const Ty1& arg1, const Ty2& arg2, const Args&... args)
			{
				return equal(arg1, arg2) && equal(arg2, args...);
			}

			template <class Ty1, class Ty2>
			_NODISCARD inline bool greater(const Ty1& arg1, const Ty2& arg2)
			{
				return arg1 > arg2;
			}

			template <class Ty1, class Ty2, class... Args>
			_NODISCARD inline bool greater(const Ty1& arg1, const Ty2& arg2, const Args&... args)
			{
				return greater(arg1, arg2) && greater(arg2, args...);
			}

			template <class Ty1, class Ty2>
			_NODISCARD inline bool greater_eq(const Ty1& arg1, const Ty2& arg2)
			{
				return arg1 >= arg2;
			}

			template <class Ty1, class Ty2, class... Args>
			_NODISCARD inline bool greater_eq(const Ty1& arg1, const Ty2& arg2, const Args&... args)
			{
				return greater_eq(arg1, arg2) && greater_eq(arg2, args...);
			}

			template <class... Args>
			_NODISCARD inline bool all_true(const Args&... args)
			{
				return (true && ... && args);
			}

			template <class... Args>
			_NODISCARD inline bool any_true(const Args&... args)
			{
				return (false || ... || args);
			}

			template <class Ty>
			_NODISCARD inline const Ty& min(const Ty& arg1)
			{
				return arg1;
			}

			template <class Ty, class... Args>
			_NODISCARD inline const Ty& min(const Ty& arg1, const Ty& arg2, const Args&... args)
			{
				return (arg1 < arg2) ?
					constref::min<Ty>(arg1, args...) :
					constref::min<Ty>(arg2, args...);
			}

			template <class Ty>
			_NODISCARD inline const Ty& max(const Ty& arg1)
			{
				return arg1;
			}

			template <class Ty, class... Args>
			_NODISCARD inline const Ty& max(const Ty& arg1, const Ty& arg2, const Args&... args)
			{
				return (arg1 > arg2) ?
					constref::max<Ty>(arg1, args...) :
					constref::max<Ty>(arg2, args...);
			}

		} // namespace constref

		namespace ref {
		
			template <class Ty>
			_NODISCARD inline Ty& min(Ty& arg1)
			{
				return arg1;
			}

			template <class Ty, class... Args>
			_NODISCARD inline Ty& min(Ty& arg1, Ty& arg2, Args&... args)
			{
				return (arg1 < arg2) ?
					ref::min<Ty>(arg1, args...) :
					ref::min<Ty>(arg2, args...);
			}

			template <class Ty>
			_NODISCARD inline Ty& max(Ty& arg1)
			{
				return arg1;
			}

			template <class Ty, class... Args>
			_NODISCARD inline Ty& max(Ty& arg1, Ty& arg2, Args&... args)
			{
				return (arg1 > arg2) ?
					ref::max<Ty>(arg1, args...) :
					ref::max<Ty>(arg2, args...);
			}
		
		} // namespace ref
		
	} // namespace Compare

} // namespace nw