#pragma once


#include <nowifi/math/math.hpp>
#include <utility>
#include <type_traits>


namespace nw {

	namespace Compare {
		
		template <class Ty1, class Ty2>
		_NODISCARD _CONSTEXPR17 bool less(Ty1 val1, Ty2 val2)
		{
			return val1 < val2;
		}

		template <class Ty1, class Ty2, class... Args>
		_NODISCARD _CONSTEXPR17 bool less(Ty1 val1, Ty2 val2, Args... args)
		{
			return less(val1, val2) && less(val2, args...);
		}

		template <class Ty1, class Ty2>
		_NODISCARD _CONSTEXPR17 bool less_eq(Ty1 val1, Ty2 val2)
		{
			return val1 <= val2;
		}

		template <class Ty1, class Ty2, class... Args>
		_NODISCARD _CONSTEXPR17 bool less_eq(Ty1 val1, Ty2 val2, Args... args)
		{
			return less_eq(val1, val2) && less_eq(val2, args...);
		}

		template <class Ty1, class Ty2>
		_NODISCARD _CONSTEXPR17 bool equal(Ty1 val1, Ty2 val2)
		{
			return val1 == val2;
		}

		template <class Ty1, class Ty2, class... Args>
		_NODISCARD _CONSTEXPR17 bool equal(Ty1 val1, Ty2 val2, Args... args)
		{
			return equal(val1, val2) && equal(val2, args...);
		}

		template <class Ty1, class Ty2>
		_NODISCARD _CONSTEXPR17 bool greater(Ty1 val1, Ty2 val2)
		{
			return val1 > val2;
		}

		template <class Ty1, class Ty2, class... Args>
		_NODISCARD _CONSTEXPR17 bool greater(Ty1 val1, Ty2 val2, Args... args)
		{
			return greater(val1, val2) && greater(val2, args...);
		}

		template <class Ty1, class Ty2>
		_NODISCARD _CONSTEXPR17 bool greater_eq(Ty1 val1, Ty2 val2)
		{
			return val1 >= val2;
		}

		template <class Ty1, class Ty2, class... Args>
		_NODISCARD _CONSTEXPR17 bool greater_eq(Ty1 val1, Ty2 val2, Args... args)
		{
			return greater_eq(val1, val2) && greater_eq(val2, args...);
		}

		template <class... Args>
		_NODISCARD _CONSTEXPR17 bool all_true(Args... args)
		{
			return (true && ... && args);
		}

		template <class... Args>
		_NODISCARD _CONSTEXPR17 bool any_true(Args... args)
		{
			return (false || ... || args);
		}

		template <class Ty, class... Args>
		_NODISCARD _CONSTEXPR17 Ty min(Ty val1, Args... args)
		{
			return (val1, ..., (val1 = (args < val1 ? args : val1)));
		}

		template <class Ty, class... Args>
		_NODISCARD _CONSTEXPR17 Ty max(Ty val1, Args... args)
		{
			return (val1, ..., (val1 = (args > val1 ? args : val1)));
		}

		namespace constref {
		
			template <class Ty1, class Ty2>
			_NODISCARD bool less(const Ty1& val1, const Ty2& val2)
			{
				return val1 < val2;
			}

			template <class Ty1, class Ty2, class... Args>
			_NODISCARD bool less(const Ty1& val1, const Ty2& val2, const Args&... args)
			{
				return less(val1, val2) && less(val2, args...);
			}

			template <class Ty1, class Ty2>
			_NODISCARD bool less_eq(const Ty1& val1, const Ty2& val2)
			{
				return val1 <= val2;
			}

			template <class Ty1, class Ty2, class... Args>
			_NODISCARD bool less_eq(const Ty1& val1, const Ty2& val2, const Args&... args)
			{
				return less_eq(val1, val2) && less_eq(val2, args...);
			}

			template <class Ty1, class Ty2>
			_NODISCARD bool equal(const Ty1& val1, const Ty2& val2)
			{
				return val1 == val2;
			}

			template <class Ty1, class Ty2, class... Args>
			_NODISCARD bool equal(const Ty1& val1, const Ty2& val2, const Args&... args)
			{
				return equal(val1, val2) && equal(val2, args...);
			}

			template <class Ty1, class Ty2>
			_NODISCARD bool greater(const Ty1& val1, const Ty2& val2)
			{
				return val1 > val2;
			}

			template <class Ty1, class Ty2, class... Args>
			_NODISCARD bool greater(const Ty1& val1, const Ty2& val2, const Args&... args)
			{
				return greater(val1, val2) && greater(val2, args...);
			}

			template <class Ty1, class Ty2>
			_NODISCARD bool greater_eq(const Ty1& val1, const Ty2& val2)
			{
				return val1 >= val2;
			}

			template <class Ty1, class Ty2, class... Args>
			_NODISCARD bool greater_eq(const Ty1& val1, const Ty2& val2, const Args&... args)
			{
				return greater_eq(val1, val2) && greater_eq(val2, args...);
			}

			template <class... Args>
			_NODISCARD bool all_true(const Args&... args)
			{
				return (true && ... && args);
			}

			template <class... Args>
			_NODISCARD bool any_true(const Args&... args)
			{
				return (false || ... || args);
			}

			template <class Ty>
			_NODISCARD const Ty& min(const Ty& val1)
			{
				return val1;
			}

			template <class Ty, class... Args>
			_NODISCARD const Ty& min(const Ty& val1, const Ty& val2, const Args&... args)
			{
				return (val1 < val2) ?
					constref::min<Ty>(val1, args...) :
					constref::min<Ty>(val2, args...);
			}

			template <class Ty>
			_NODISCARD const Ty& max(const Ty& val1)
			{
				return val1;
			}

			template <class Ty, class... Args>
			_NODISCARD const Ty& max(const Ty& val1, const Ty& val2, const Args&... args)
			{
				return (val1 > val2) ?
					constref::max<Ty>(val1, args...) :
					constref::max<Ty>(val2, args...);
			}

		} // namespace constref

		namespace ref {
		
			template <class Ty>
			_NODISCARD constexpr Ty&& min(Ty&& val1, Ty&& val2)
			{
				return ((val1 < val2) ? std::forward<Ty>(val1) : std::forward<Ty>(val2));
			}

			template <class Ty, class... Args>
			_NODISCARD constexpr Ty&& min(Ty&& val1, Args&&... args)
			{
				return std::forward<Ty>(ref::min(std::forward<Ty>(val1), std::forward<Ty>(ref::min(std::forward<Args>(args)...))));
			}

			template <class Ty>
			_NODISCARD constexpr Ty&& max(Ty&& val1, Ty&& val2)
			{
				return ((val1 > val2) ? std::forward<Ty>(val1) : std::forward<Ty>(val2));
			}

			template <class Ty, class... Args>
			_NODISCARD constexpr Ty&& max(Ty&& val1, Args&&... args)
			{
				return std::forward<Ty>(ref::max(std::forward<Ty>(val1), std::forward<Ty>(ref::max(std::forward<Args>(args)...))));
			}
		
		} // namespace ref
		
	} // namespace Compare

} // namespace nw