#pragma once

#include <nowifi/compiler/class.hpp>
#include <nowifi/array/std_array.hpp>
#include <algorithm>
#include <stdexcept>

namespace nw {

	////////////////////////////////                    ////////////////////////////////
	//------------------------------                    ------------------------------//
	//------------------------------ linear_multi_array ------------------------------//
	//------------------------------                    ------------------------------//
	////////////////////////////////                    ////////////////////////////////

	template <size_t Dim>
	class linear_multi_array
	{
	public:
		NW_CLASS_MAKE_STATIC(linear_multi_array, <Dim>);

		friend class linear_multi_array;

		template <size_t AnyDim>
		friend class linear_multi_array;

	protected:

		using below_type = linear_multi_array<Dim - 1>;

		template <size_t HiDim>
		using index_type_any = std::array<size_t, HiDim>;

	public:

		//Array size / position type
		using index_type = index_type_any<Dim>;

		template <class Ty>
		using iterator = Ty*;

		template <class Ty>
		using const_iterator = const iterator<Ty>;

		static inline index_type calcMultipliers(const index_type& size)
		{
			index_type result;
			size_t curr = 1;
			for_loop::raw_i<Dim>::call([&size, &result, &curr](size_t idx)
			{
				curr *= size[idx];
				result[idx] = curr;
			});
			return result;
		}

		//-------------------- Memory managing operations --------------------//

		template <class Ty> _NODISCARD inline
		static iterator<Ty> allocate(const index_type& multipliers)
		{
			return new Ty[multipliers[0]];
		}

		template <class Ty> inline
		static void deallocate(iterator<Ty> arr)
		{
			delete[] arr;
		}

		template <class Ty, size_t HiDim> _NODISCARD inline
		static Ty& get(Ty* arr, const index_type& multipliers, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <pos> too small");

			return below_type::template get<Ty>(arr + (multipliers[HiDim - Dim] * pos[HiDim - Dim]), multipliers, pos);
		}

		template <class Ty, size_t HiDim> _NODISCARD inline
		static const Ty& get(const Ty* arr, const index_type& multipliers, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <pos> too small");

			return below_type::template get<Ty>(arr + (multipliers[HiDim - Dim + 1] * pos[HiDim - Dim]), multipliers, pos);
		}

		//-------------------- Non-modifying sequence operations --------------------//


	};

	////////////////////////////////                       ////////////////////////////////
	//------------------------------                       ------------------------------//
	//------------------------------ linear_multi_array<1> ------------------------------//
	//------------------------------                       ------------------------------//
	////////////////////////////////                       ////////////////////////////////

	template <>
	class linear_multi_array <1U>
	{
	public:
		NW_CLASS_MAKE_STATIC(linear_multi_array, <1>);

		friend class linear_multi_array;

		template <size_t AnyDim>
		friend class linear_multi_array;

	protected:

		template <size_t HiDim>
		using index_type_any = std::array<size_t, HiDim>;

	public:

		//Array size / position type
		using index_type = index_type_any<1>;

		template <class Ty>
		using iterator = Ty*;

		static inline index_type calcMultipliers(const index_type& size)
		{
			index_type result;
			result[0] = size[0];
			return result;
		}

		//-------------------- Memory managing operations --------------------//

		template <class Ty> _NODISCARD inline
			static iterator<Ty> allocate(const index_type& multipliers)
		{
			return new Ty[multipliers[0]];
		}

		template <class Ty> inline
			static void deallocate(iterator<Ty> arr)
		{
			delete[] arr;
		}

		template <class Ty, size_t HiDim> _NODISCARD inline
		static Ty& get(Ty* arr, const index_type& multipliers, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <pos> too small");

			return *(arr + pos[HiDim - 1]);
		}

		template <class Ty, size_t HiDim> _NODISCARD inline
		static const Ty& get(const Ty* arr, const index_type& multipliers, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <pos> too small");

			return *(arr + pos[HiDim - 1]);
		}

		//-------------------- Non-modifying sequence operations --------------------//
	};

	////////////////////////////////                       ////////////////////////////////
	//------------------------------                       ------------------------------//
	//------------------------------ linear_multi_array<0> ------------------------------//
	//------------------------------                       ------------------------------//
	////////////////////////////////                       ////////////////////////////////

	template <>
	class linear_multi_array <0U>
	{
	public:
		NW_CLASS_MAKE_STATIC(linear_multi_array, <0>);

		friend class linear_multi_array;

		template <size_t AnyDim>
		friend class linear_multi_array;

		template <class Ty>
		using iterator = Ty*;
	};

	using linear_multi_array1D = linear_multi_array<1>;
	using linear_multi_array2D = linear_multi_array<2>;
	using linear_multi_array3D = linear_multi_array<3>;
	using linear_multi_array4D = linear_multi_array<4>;
	using linear_multi_array5D = linear_multi_array<5>;
	using linear_multi_array6D = linear_multi_array<6>;
	using linear_multi_array7D = linear_multi_array<7>;
	using linear_multi_array8D = linear_multi_array<8>;

} // namespace nw