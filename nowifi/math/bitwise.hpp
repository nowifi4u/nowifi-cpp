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

	} // namespace Bitwise

} // namespace nw