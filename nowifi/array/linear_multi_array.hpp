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

		template <size_t Dim>
		friend class linear_multi_array<Dim>;

	protected:

		using below_type = linear_multi_array<Dim - 1>;

		template <size_t HiDim>
		using index_type_any = std::array<size_t, HiDim>;

	public:

		//Array size / position type
		using index_type = index_type_any<Dim>;

		template <class Ty>
		using iterator = Ty*;
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

		template <size_t Dim>
		friend class linear_multi_array<Dim>;

	protected:

		template <size_t HiDim>
		using index_type_any = std::array<size_t, HiDim>;

	public:

		//Array size / position type
		using index_type = index_type_any<1>;

		template <class Ty>
		using iterator = Ty*;

		static inline index_type multSize(const index_type& size)
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

		template <size_t Dim>
		friend class linear_multi_array<Dim>;

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