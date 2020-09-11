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

		_NODISCARD inline
			static index_type calcMultipliers(const index_type& size)
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

	protected:

		template <size_t HiDim> _NODISCARD inline
			static size_t _layerOffset(const index_type_any<HiDim>& size, size_t pos, size_t offset)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			return (offset + pos) * size[HiDim - Dim + 1];
		}

		template <size_t HiDim> _NODISCARD inline
			static size_t _layerOffset(const index_type_any<HiDim>& size, const index_type_any<HiDim>& pos, size_t offset)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			return (offset + pos[HiDim - Dim]) * size[HiDim - Dim + 1];
		}

		template <size_t HiDim> _NODISCARD inline
			static size_t _impl_calcOffset(const index_type_any<HiDim>& size, const index_type_any<HiDim>& pos, size_t offset = 0)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			return below_type::_impl_calcOffset(size, pos, _layerOffset(size, pos, offset));
		}

	public:

		template <size_t HiDim> _NODISCARD inline
			static size_t calcOffset(const index_type_any<HiDim>& size, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			return _impl_calcOffset(size, pos);
		}

		//-------------------- Memory managing operations --------------------//

		template <class Ty> _NODISCARD inline
			static iterator<Ty> allocate(const index_type& size)
		{
			return new Ty[calcMultipliers(size)[0]];
		}

		template <class Ty> inline
			static void deallocate(iterator<Ty> arr)
		{
			delete[] arr;
		}

		template <class Ty, size_t HiDim> _NODISCARD inline
			static Ty& get(Ty* arr, const index_type_any<HiDim>& size, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			return arr[calcOffset(size, pos)];
		}

		template <class Ty, size_t HiDim> _NODISCARD inline
			static const Ty& get(const Ty* arr, const index_type_any<HiDim>& size, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			return arr[calcOffset(size, pos)];
		}

		//-------------------- Non-modifying sequence operations --------------------//

	protected:

		template <class Ty, size_t HiDim> _NODISCARD inline
			static bool _impl_all(const Ty* arr, const index_type_any<HiDim>& size, const Ty& val, size_t offset = 0)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				if (!below_type::template _impl_all<Ty>(arr, size, _layerOffset(size, idx, offset))) return false;
			}
			return true;
		}

	public:

		template <class Ty, size_t HiDim> _NODISCARD inline
			static bool all(const Ty* arr, const index_type_any<HiDim>& size, const Ty& val)
		{
			return _impl_all(arr, size, val);
		}

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

		_NODISCARD inline
			static index_type calcMultipliers(const index_type& size)
		{
			index_type result;
			result[0] = size[0];
			return result;
		}

	protected:

		template <size_t HiDim> _NODISCARD inline
			static size_t _layerOffset(const index_type_any<HiDim>& size, size_t pos, size_t offset)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return offset + pos;
		}

		template <size_t HiDim> _NODISCARD inline
			static size_t _layerOffset(const index_type_any<HiDim>& size, const index_type_any<HiDim>& pos, size_t offset)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return offset + pos[HiDim - 1];
		}

		template <size_t HiDim> _NODISCARD inline
			static size_t _impl_calcOffset(const index_type_any<HiDim>& size, const index_type_any<HiDim>& pos, size_t offset = 0)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return offset + pos[HiDim - 1];
		}

	public:

		template <size_t HiDim> _NODISCARD inline
			static size_t calcOffset(const index_type_any<HiDim>& size, const index_type_any<HiDim>& pos)
		{
			return _impl_calcOffset(size, pos);
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
			static Ty& get(Ty* arr, const index_type_any<HiDim>& size, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return arr[calcOffset(size, pos)];
		}

		template <class Ty, size_t HiDim> _NODISCARD inline
			static const Ty& get(const Ty* arr, const index_type_any<HiDim>& size, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return arr[calcOffset(size, pos)];
		}

		//-------------------- Non-modifying sequence operations --------------------//

	protected:

		template <class Ty, size_t HiDim> _NODISCARD inline
			static bool _impl_all(const Ty* arr, const index_type_any<HiDim>& size, const Ty& val, size_t offset = 0)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (arr[offset + idx] != val) return false;
			}
			return true;
		}

	public:

		template <class Ty, size_t HiDim> _NODISCARD inline
			static bool all(const Ty* arr, const index_type_any<HiDim>& size, const Ty& val)
		{
			return _impl_all(arr, size, val);
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