#pragma once

#include <nowifi/compiler/class.hpp>
#include <vector>

namespace nw {

	template <typename Ty, Ty MOD>
	class basic_ModularMath
	{
	public:
		NW_CLASS_MAKE_STATIC(basic_ModularMath, <Ty, MOD>);

		[[NODISCARD]]
		static constexpr Ty add(const Ty& a, const Ty& b)
		{
			return (a + b) % MOD;
		}

		[[NODISCARD]]
		static constexpr Ty safe_add(const Ty& a, const Ty& b)
		{
			return add(a % MOD, b % MOD);
		}

		[[NODISCARD]]
		static constexpr Ty multiply(const Ty& a, const Ty& b)
		{
			return (a * b) % MOD;
		}

		[[NODISCARD]]
		static constexpr Ty safe_multiply(const Ty& a, const Ty& b)
		{
			return multiply(a % MOD, b % MOD);
		}

		[[NODISCARD]]
		static constexpr Ty subtract(const Ty& a, const Ty& b)
		{
			return ((a - b) % MOD + MOD) % MOD;
		}

		[[NODISCARD]]
		static constexpr Ty divide(const Ty& a, const Ty& b)
		{
			return multiply(a, power(b, MOD - 2));
		}

		[[NODISCARD]]
		static constexpr Ty safe_divide(const Ty& a, const Ty& b)
		{
			return safe_multiply(a, power(b, MOD - 2));
		}

		[[NODISCARD]]
		static constexpr Ty power(Ty a, Ty b)
		{
			int res = 1;
			while (b > 0)
			{
				if (b % 2) res = multiply(res, a);
				a = multiply(a, a);
				b /= 2;
			}
			return res;
		}

		[[NODISCARD]]
		static constexpr Ty inverse(const Ty& a, const Ty& b)
		{
			return power(a, b - 2);
		}

		[[NODISCARD]]
		static constexpr Ty factorial_fast(Ty n)
		{
			std::array<Ty, (int)MOD> f{};
			f[0] = 1;
			for (int i = 1; i < (int)MOD; i++)
				f[i] = multiply(f[i - 1], i);

			Ty res = 1;
			while (n > 1)
			{
				if ((n / MOD) % 2)
					res = MOD - res;
				res = multiply(res, f[(int)n % MOD]);
				n /= MOD;
			}
			return res;
		}

		[[NODISCARD]]
		static constexpr Ty factorial_nomem(Ty n)
		{
			Ty res = 1;
			for (int i = 2; i <= n; i++)
				res = multiply(res, i);
			return res;
		}

		[[NODISCARD]]
		static constexpr Ty multiplicity_factorial(Ty n)
		{
			Ty count = 0;
			do {
				n /= MOD;
				count += n;
			} while (n);
			return count;
		}

	}; // class basic_ModularMath

	template <int MOD>
	using ModularMath_Int = basic_ModularMath<int, MOD>;

	template <long long MOD>
	using ModularMath_LL = basic_ModularMath<long long, MOD>;

} // namespace nw