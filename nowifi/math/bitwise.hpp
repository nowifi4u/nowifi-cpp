#pragma once

namespace nw {

	namespace Bitwise {

		// a=target variable, b=bit number to act upon 0-n
		template<typename T1, typename T2>
		constexpr inline auto bit_set(const T1 a, const T2 b)
		{
			return ((a) |= (1ULL << (b)));
		}

		// a=target variable, b=bit number to act upon 0-n
		template<typename T1, typename T2>
		constexpr inline auto bit_clear(const T1 a, const T2 b)
		{
			return ((a) &= ~(1ULL << (b)));
		}

		// a=target variable, b=bit number to act upon 0-n
		template<typename T1, typename T2>
		constexpr inline auto bit_flip(const T1 a, const T2 b)
		{
			return ((a) ^= (1ULL << (b)));
		}

		// a=target variable, b=bit number to act upon 0-n
		template<typename T1, typename T2>
		constexpr inline auto bit_check(const T1 a, const T2 b)
		{
			return (!!((a) & (1ULL << (b))));
		}



		// x=target variable, y=mask
		template<typename T1, typename T2>
		constexpr inline auto bitmask_set(const T1 x, const T2 y)
		{
			return ((x) |= (y));
		}

		// x=target variable, y=mask
		template<typename T1, typename T2>
		constexpr inline auto bitmask_clear(const T1 x, const T2 y)
		{
			return ((x) &= (~(y)));
		}

		// x=target variable, y=mask
		template<typename T1, typename T2>
		constexpr inline auto bitmask_flip(const T1 x, const T2 y)
		{
			return ((x) ^= (y));
		}

		// x=target variable, y=mask
		template<typename T1, typename T2>
		constexpr inline auto bitmask_check_all(const T1 x, const T2 y)
		{
			return ((bitmask_check_any((x), (y))) == (y));
		}

		// x=target variable, y=mask
		template<typename T1, typename T2>
		constexpr inline auto bitmask_check_any(const T1 x, const T2 y)
		{
			return ((x) & (y));
		}

		static const char _log2_32_LogTable256[256] =
		{
		#define _log2_32_LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
			- 1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
			_log2_32_LT(4), _log2_32_LT(5), _log2_32_LT(5), _log2_32_LT(6), _log2_32_LT(6), _log2_32_LT(6), _log2_32_LT(6),
			_log2_32_LT(7), _log2_32_LT(7), _log2_32_LT(7), _log2_32_LT(7), _log2_32_LT(7), _log2_32_LT(7), _log2_32_LT(7), _log2_32_LT(7)
		};

		constexpr inline unsigned log2_32_lookup(unsigned int v)
		{
			register unsigned int tt = 0;

			if (tt = v >> 24)
			{
				return 24 + _log2_32_LogTable256[tt];
			}
			else if (tt = v >> 16)
			{
				return 16 + _log2_32_LogTable256[tt];
			}
			else if (tt = v >> 8)
			{
				return 8 + _log2_32_LogTable256[tt];
			}
			else
			{
				return _log2_32_LogTable256[v];
			}
		}

	} // namespace Bitwise

	namespace Log2 {
	
	
	
	} // namespace Log2

} // namespace nw