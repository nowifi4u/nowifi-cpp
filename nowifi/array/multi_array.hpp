#pragma once

#include <nowifi/compiler/class.hpp>
#include <nowifi/array/std_array.hpp>
#include <algorithm>
#include <stdexcept>

namespace nw {

	////////////////////////////////             ////////////////////////////////
	//------------------------------             ------------------------------//
	//------------------------------ multi_array ------------------------------//
	//------------------------------             ------------------------------//
	////////////////////////////////             ////////////////////////////////

	template <size_t Dim>
	class multi_array
	{
	public:
		NW_CLASS_MAKE_STATIC(multi_array, <Dim>);

		friend class multi_array;
		
		template <size_t Dim>
		friend class multi_array;

	protected:

		using below_type = multi_array<Dim - 1>;

		template <size_t HiDim>
		using index_type_any = std::array<size_t, HiDim>;

	public:

		//Array size / position type
		using index_type = index_type_any<Dim>;

		//Item type or top-level array for given item type
		template <class Ty>
		using item_type = typename below_type::template item_type<Ty> *const;

		//Pointer type for given item type
		template <class Ty>
		using free_iterator = item_type<Ty>*;

		template <class Ty>
		using iterator = typename below_type::template iterator<Ty> const*;

		template <class Ty>
		using const_iterator = iterator<Ty> const;

		template <class Ty>
		using iterator_allocatable = typename below_type::template iterator<Ty>*;

		//-------------------- iterator <=> free_iterator --------------------//

		template <class Ty> inline constexpr
		static free_iterator<Ty> pointer_remove_const_full(iterator<Ty> arr)
		{
			return const_cast<free_iterator<Ty>>(arr);
		}

		template <class Ty> inline constexpr
		static iterator<Ty> pointer_add_const_full(free_iterator<Ty> arr)
		{
			return const_cast<free_iterator<Ty>>(arr);
		}

		//-------------------- iterator <=> iterator_allocatable --------------------//

		template <class Ty> inline constexpr
		static iterator_allocatable<Ty> pointer_make_allocatable(iterator<Ty> arr)
		{
			return const_cast<iterator_allocatable<Ty>>(arr);
		}

		template <class Ty> inline constexpr
		static iterator<Ty> pointer_make_unallocatable(iterator_allocatable<Ty> arr)
		{
			return const_cast<iterator<Ty>>(arr);
		}

		//-------------------- Memory managing operations --------------------//

		/*
		 * Allocates a NEW ARRAY.
		 * 
		 * @param <Ty> [template] - Item type of NEW ARRAY
		 * @param <size> - Size of NEW ARRAY
		 * @return Pointer to NEW ARRAY
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static iterator<Ty> allocate(const index_type_any<HiDim>& size)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			size_t _size = size[HiDim - Dim];
			iterator<Ty> arr = new item_type<Ty>[_size];
#pragma omp parallel for
			for (int idx = 0; idx < _size; idx++)
			{
				pointer_make_allocatable(arr)[idx] = below_type::template allocate<Ty>(size);
			}
			return arr;
		}

		/*
		 * Deallocates memory of array.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, size_t HiDim> inline
		static void deallocate(iterator<Ty> arr, const index_type_any<HiDim>& size)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template deallocate<Ty>(arr[idx], size);
			}
			delete[] arr;
		}

		/*
		 * Return a reference to element on <pos> location.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <pos> - Position of item
		 * @return **See above**
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static Ty& get(iterator<Ty> arr, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <pos> too small");

			return below_type::template get<Ty>(arr[pos[HiDim - Dim]], pos);
		}

		template <class Ty, class... Args> _NODISCARD inline
		static Ty& get_pack(iterator<Ty> arr, Args&&... args)
		{
			static_assert(sizeof...(args) == Dim, "Invalid pack size");

			return get<Ty, Dim>(arr, index_type{ std::forward<Args>(args)... });
		}

		/*
		 * Return a constant reference to element on <pos> location.
		 * 
		 * @param <arr> - Pointer to multi_array
		 * @param <pos> - Position of item
		 * @return **See above**
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static const Ty& get_const(typename iterator<Ty> const arr, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			return below_type::template get_const<Ty>(arr[pos[HiDim - Dim]], pos);
		}

		//-------------------- Non-modifying sequence operations --------------------//

		/*
		 * Returns true if all the elements are equal to <val>
		 * or <size> has a zero, and false otherwise.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to search for
		 * @return **See above**
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static bool all(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty& val)
		{
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				if (below_type::template all<Ty>(arr[idx], size, val) == false) return false;
			}
			return true;
		}

		/*
		 * Returns true if <pred> returns true for all the elements
		 * or <size> has a zero, and false otherwise.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element
		 *                 and returns a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
			static bool all_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				if (below_type::template all_if<Ty, UnaryPredicate>(arr[idx], size, pred) == false) return false;
			}
			return true;
		}

		/*
		 * Returns true if any of the elements is equal to <val>,
		 * and false otherwise or <size> is empty.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to search for
		 * @return **See above**
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
			static bool any(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty& val)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				if (below_type::template any<Ty>(arr[idx], size, val) == true) return true;
			}
			return false;
		}

		/*
		 * Returns true if <pred> returns true for any of the elements, 
		 * and false otherwise or <size> is empty.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element
		 *                 and returns a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static bool any_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				if (below_type::template any_if<Ty, UnaryPredicate>(arr[idx], size, pred) == true) return true;
			}
			return false;
		}

		/* Returns true if all the elements are not equal to <val>
		 * or <size> has a zero, and false otherwise.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to search for
		 * @return **See above**
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static bool none(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty& val)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				if (below_type::template none<Ty>(arr[idx], size, val) == false) return false;
			}
			return false;
		}

		/* Returns true if <pred> returns false for all the elements. 
		 * or <size> has a zero, and false otherwise.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element
		 *                 and returns a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static bool none_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				if (below_type::template none_if<Ty, UnaryPredicate>(arr[idx], size, pred) == false) return false;
			}
			return true;
		}

		/*
		 * Applies function <fn> to each of the elements.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <fn> - Unary function that accepts an element as argument
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, class Function, size_t HiDim> inline
		static void for_each(iterator<Ty> arr, const index_type_any<HiDim>& size, Function fn)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template for_each<Ty, Function>(arr[idx], size, fn);
			}
		}

		/*
		 * Applies function <fn> to each of the elements.
		 * 
		 * @param <Layer> - Layer to stop at
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <fn> - Unary function that accepts an element as argument
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <size_t Layer, class Ty, class Function, size_t HiDim> inline
		static void for_each_layer(iterator<Ty> arr, const index_type_any<HiDim>& size, Function fn)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");
			static_assert(Layer <= Dim, "Template <Layer> too big");

			const auto cut_size = std_array::cut_back<Layer>(size);

			multi_array<Dim - Layer>::template for_each<multi_array<Layer>::template const_iterator<Ty>, Function>(arr, cut_size, fn);
		}

	protected:

		template <class Ty, class Function_i, size_t HiDim, size_t HiDim2> inline
		static void _impl_for_each_i(iterator<Ty> arr, const index_type_any<HiDim>& size, Function_i fn, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");
			static_assert(HiDim2 >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				pos[HiDim2 - Dim] = idx;
				below_type::template _impl_for_each_i<Ty, Function_i>(arr[idx], size, fn, pos);
			}
		}

	public:

		/*
		 * Applies function <fn> to each of the elements.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <fn> - Unary function that accepts an element and
		 *               its position as arguments
		 */
		template <class Ty, class Function_i, size_t HiDim> inline
		static void for_each_i(iterator<Ty> arr, const index_type_any<HiDim>& size, Function_i fn)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			index_type_any<HiDim> pos;
			_impl_for_each_i<Ty, Function_i>(arr, size, fn, pos);
		}

		/*
		 * Applies function <fn> to each of the elements.
		 *
		 * @param <Layer> - Layer to stop at
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <fn> - Unary function that accepts an element and
		 *               its position as arguments
		 */
		template <size_t Layer, class Ty, class Function, size_t HiDim> inline
		static void for_each_i_layer(iterator<Ty> arr, const index_type_any<HiDim>& size, Function fn)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");
			static_assert(Layer <= Dim, "Template <Layer> too big");

			const auto cut_size = std_array::cut_back<Layer>(size);
			index_type_any<Dim - Layer> pos;

			multi_array<Dim - Layer>::template _impl_for_each_i<multi_array<Layer>::template const_iterator<Ty>, Function>(arr, cut_size, fn, pos);
		}

		/*
		 * Returns a pointer to the first element that compares equal to <val>. 
		 * If no such element found, the function returns nullptr.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to search for
		 * @param <pos> - Parameter to save found element's position
		 * @return **See above**
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, class Ty2, size_t HiDim, size_t HiDim2> inline
		static Ty* find(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty2& val, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");
			static_assert(HiDim2 >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				Ty* result = below_type::template find<Ty, Ty2>(arr[idx], size, val, pos);
				if (result != nullptr)
				{
					pos[HiDim2 - Dim] = idx;
					return result;
				}
			}

			return nullptr;
		}

		/*
		 * Returns a pointer to the first element that compares equal to <val>. 
		 * If no such element found, the function returns nullptr.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to search for
		 * @return **See above**
		 */
		template <class Ty, class Ty2, size_t HiDim> _NODISCARD  inline
		static Ty* find(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty2& val)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				Ty* result = below_type::template find<Ty, Ty2>(arr[idx], size, val);
				if (result != nullptr)
				{
					return result;
				}
			}

			return nullptr;
		}

		/*
		 * Returns a pointer to the first element for which <pred> returns true. 
		 * If no such element found, the function returns nullptr.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @param <pos> - Parameter to save found element's position
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim, size_t HiDim2> inline
		static Ty* find_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");
			static_assert(HiDim2 >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				Ty* result = below_type::template find_if<Ty, UnaryPredicate>(arr[idx], size, pred, pos);
				if (result != nullptr)
				{
					pos[HiDim2 - Dim] = idx;
					return result;
				}
			}

			return nullptr;
		}

		/*
		 * Returns a pointer to the first element for which <pred> returns true. 
		 * If no such element found, the function returns nullptr.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static Ty* find_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");
			
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				Ty* result = below_type::template find_if<Ty, UnaryPredicate>(arr[idx], size, pred);
				if (result != nullptr)
				{
					return result;
				}
			}

			return nullptr;
		}

		/*
		 * Returns a pointer to the first element for which <pred> returns false. 
		 * If no such element found, the function returns nullptr.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @param <pos> - Parameter to save found element's position
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim, size_t HiDim2> inline
		static Ty* find_if_not(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");
			static_assert(HiDim2 >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				Ty* result = below_type::template find_if_not<Ty, UnaryPredicate>(arr[idx], size, pred, pos);
				if (result != nullptr)
				{
					pos[HiDim2 - Dim] = idx;
					return result;
				}
			}

			return nullptr;
		}

		/*
		 * Returns a pointer to the first element for which <pred> returns false. 
		 * If no such element found, the function returns nullptr.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static Ty* find_if_not(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				Ty* result = below_type::template find_if_not<Ty, UnaryPredicate>(arr[idx], size, pred);
				if (result != nullptr)
				{
					return result;
				}
			}

			return nullptr;
		}

		/*
		 * Returns the number of elements that compare equal to <val>.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to match
		 * @return **See above**
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, class Ty2, size_t HiDim> _NODISCARD inline
		static size_t count(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty2& val)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			size_t result = 0;

#pragma omp parallel for reduction(+:result)
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				result += below_type::template count<Ty, Ty2>(arr[idx], size, val);
			}

			return result;
		}

		/*
		 * Returns the number of elements for which <pred> is true.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @return **See above**
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static size_t count_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			size_t result = 0;

#pragma omp parallel for reduction(+:result)
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				result += below_type::template count_if<Ty, UnaryPredicate>(arr[idx], size, pred);
			}

			return result;
		}

		/*
		 * Compares the elements or two arrays and returns the first element of 
		 * <arr> that does not match.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @param <pos> - Parameter to save found element's position
		 * @return **See above**
		 */
		template <class Ty, class Ty2, size_t HiDim, size_t HiDim2> inline
		static Ty* mismatch(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");
			static_assert(HiDim2 >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				pos[HiDim2 - Dim] = idx;
				Ty* result = below_type::template mismatch<Ty, Ty2>(arr[idx], size, arr2[idx], pos);
				if (result != nullptr) return result;
			}

			return nullptr;
		}

		/*
		 * Compares the elements or two arrays and returns the first element of 
		 * <arr> that does not match.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @return **See above**
		 */
		template <class Ty, class Ty2, size_t HiDim> _NODISCARD inline
		static Ty* mismatch(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				Ty* result = below_type::template mismatch<Ty, Ty2>(arr[idx], size, arr2[idx]);
				if (result != nullptr) return result;
			}

			return nullptr;
		}

		/*
		 * Compares the elements or two arrays and returns true if the elements 
		 * of both arrays match.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @return **See above**
		 */
		template <class Ty, class Ty2, size_t HiDim> _NODISCARD inline
		static bool equal(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				if (below_type::template equal<Ty, Ty2>(arr[idx], size, arr2[idx]) == false) return false;
			}

			return true;
		}

		//-------------------- Modifying sequence operations --------------------//

		/*
		 * Copies the elements of <arr> into <arr2>.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr_result> - Pointer to result array
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class newTy, class Ty, size_t HiDim> inline
		static void copy(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<newTy> arr_result)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template copy<newTy, Ty>(arr[idx], size, arr_result[idx]);
			}
		}

		/*
		 * Copies the elements of <arr> into NEW ARRAY.
		 * 
		 * @param <newTy> [template] - item type of NEW ARRAY
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @return Pointer to NEW ARRAY
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class newTy, class Ty, size_t HiDim> _NODISCARD inline
		static iterator<newTy> copy_new(iterator<Ty> arr, const index_type_any<HiDim>& size)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			iterator<newTy> newarr = allocate<newTy>(size);
			copy<newTy, Ty>(arr, size, newarr);
			return newarr;
		}

		/*
		 * Copies the elements of <arr> into <arr2> from which <pred> returns true.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr_result> - Pointer to result array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> inline
		static void copy_if(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty> arr_result, UnaryPredicate pred)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template copy_if<Ty, UnaryPredicate>(arr[idx], size, arr_result[idx], pred);
			}
		}

		/*
		 * Moves the elements of <arr> into <arr2>.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, class Ty2, size_t HiDim> inline
		static void move(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template move<Ty, Ty2>(arr[idx], size, arr2[idx]);
			}
		}

		/*
		 * Moves the elements of <arr> into NEW ARRAY. 
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @return Pointer to NEW ARRAY
		 *
		 * @exception #pragma omp parallel for
		 */
		template <class newTy, class Ty, size_t HiDim> _NODISCARD inline
		static iterator<newTy> move_new(iterator<Ty> arr, const index_type_any<HiDim>& size)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			iterator<newTy> newarr = allocate<newTy>(size);
			move<Ty, newTy>(arr, size, newarr);
			return newarr;
		}

		/*
		 * Applies an operation sequentially to the elements of <arr> and 
		 * stores the result into <arr2>.
		 * 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr_result> - Pointer to result array
		 * @param <op> - Unary function that accepts an elements and
		 *               returns value convertible to the type pointed to by <arr_result>
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class newTy, class Ty, class UnaryOperation, size_t HiDim> inline
		static void transform(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<newTy> arr_result, UnaryOperation op)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template transform<newTy, Ty, UnaryOperation>(arr[idx], size, arr_result[idx], op);
			}
		}

		/*
		 * Applies an operation sequentially to the elements of <arr> and
		 * stores the result into NEW ARRAY.
		 *
		 * @param <newTy> [template] - item type of NEW ARRAY
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <op> - Unary function that accepts an elements and
		 *               returns value convertible to the type pointed to by <arr_result>
		 * @return Pointer to NEW ARRAY
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class newTy, class Ty, class UnaryOperation, size_t HiDim> _NODISCARD inline
		static iterator<newTy> transform_new(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryOperation op)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			iterator<newTy> newarr = allocate<newTy>(size);
			transform<newTy, Ty, UnaryOperation>(arr, size, newarr, op);
			return newarr;
		}

		/*
		 * Applies an operation sequentially to the elements of <arr> and <arr2> and
		 * stores the result into <arr2>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @param <arr_result> - Pointer to result array
		 * @param <binary_op> - Binary function that accepts two elements and
		 *                      returns value convertible to the type pointed to by <arr_result>
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class newTy, class Ty, class Ty2, class BinaryOperation, size_t HiDim> inline
		static void transform(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2, iterator<newTy> arr_result, BinaryOperation binary_op)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template transform<newTy, Ty, Ty2, BinaryOperation>(arr[idx], size, arr2[idx], arr_result[idx], binary_op);
			}
		}

		/*
		 * Applies an operation sequentially to the elements of <arr> and <arr2> and
		 * stores the result into NEW ARRAY.
		 *
		 * @param <newTy> [template] - item type of NEW ARRAY
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @param <binary_op> - Binary function that accepts two elements and
		 *                      returns value convertible to the type pointed to by <arr_result>
		 * @return Pointer to NEW ARRAY
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class newTy, class Ty, class Ty2, class BinaryOperation, size_t HiDim> _NODISCARD inline
		static iterator<newTy> transform_new(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2, BinaryOperation binary_op)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			iterator<newTy> newarr = allocate<newTy>(size);
			transform<newTy, Ty, Ty2, BinaryOperation>(arr, size, arr2, newarr, binary_op);
			return newarr;
		}

		/*
		 * Assigns <new_value> to all the elements that compare equal to <old_value>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <old_value> - Value to be replaced
		 * @param <new_value> - Replacement value
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, size_t HiDim> inline
		static void replace(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty& old_value, const Ty& new_value)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template replace<Ty>(arr[idx], size, old_value, new_value);
			}
		}

		/*
		 * Assigns <new_value> to all the elements for which <pred> returns true.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @param <new_value> - Value to assign to replaced elements
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> inline
		static void replace_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred, const Ty& new_value)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template replace_if<Ty, UnaryPredicate>(arr[idx], size, pred, new_value);
			}
		}

		/*
		 * Copies the elements in <arr> to <arr2>, replacing the appearances 
		 * of <old_value> by <new_value>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr_result> - Pointer to result array
		 * @param <old_value> - Value to be replaced
		 * @param <new_value> - Replacement value
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, size_t HiDim> inline
		static void replace_copy(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty> arr_result, const Ty& old_value, const Ty& new_value)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template replace_copy<Ty>(arr[idx], size, arr_result[idx], old_value, new_value);
			}
		}

		/*
		 * Copies the elements in <arr> to <arr2>, replacing those for which 
		 * <pred> returns true by <new_value>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr_result> - Pointer to array #2
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @param <new_value> - Value to assign to replaced elements
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> inline
		static void replace_copy_if(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty> arr_result, UnaryPredicate pred, const Ty& new_value)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template replace_copy_if<Ty, UnaryPredicate>(arr[idx], size, arr_result[idx], pred, new_value);
			}
		}

		/*
		 * Assigns <val> to all the elements in <arr>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to assign
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, size_t HiDim> inline
		static void fill(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty& val)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template fill<Ty>(arr[idx], size, val);
			}
		}

		/*
		 * Assigns <val> to all the elements in NEW ARRAY.
		 *
		 * @param <size> - Size of array
		 * @param <val> - Value to assign
		 * @return Pointer to NEW ARRAY
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static iterator<Ty> fill_new(const index_type_any<HiDim>& size, const Ty& val)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			iterator<Ty> newarr = allocate<Ty>(size);
			fill<Ty>(newarr, size, val);
			return newarr;
		}

		/*
		 * Assigns the value returned by successive calls to <gen> to the 
		 * elements in <arr>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <gen> - Generator function that is called with no arguments and 
		 *                returns a value of a type convertible to those pointed by <arr>
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, class Generator, size_t HiDim> inline
		static void generate(iterator<Ty> arr, const index_type_any<HiDim>& size, Generator gen)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

#pragma omp parallel for
			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				below_type::template generate<Ty, Generator>(arr[idx], size, gen);
			}
		}

		/*
		 * Assigns the value returned by successive calls to <gen> to the
		 * elements in NEW ARRAY. 
		 *
		 * @param <size> - Size of array
		 * @param <gen> - Generator function that is called with no arguments and
		 *                returns a value of a type convertible to those pointed by <arr>
		 * @return Pointer to NEW ARRAY
		 * 
		 * @exception #pragma omp parallel for
		 */
		template <class Ty, class Generator, size_t HiDim> _NODISCARD inline
		static iterator<Ty> generate_new(const index_type_any<HiDim>& size, Generator gen)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			iterator<Ty> newarr = allocate<Ty>(size);
			generate<Ty>(newarr, size, gen);
			return newarr;
		}

	protected:

		template <class Ty, class Generator, size_t HiDim, size_t HiDim2> inline
		static void _impl_generate_i(iterator<Ty> arr, const index_type_any<HiDim>& size, Generator gen, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");
			static_assert(HiDim2 >= Dim, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - Dim]; idx++)
			{
				pos[HiDim2 - Dim] = idx;
				below_type::template _impl_generate_i<Ty, Generator>(arr[idx], size, gen, pos);
			}
		}

	public:

		/*
		 * Assigns the value returned by successive calls to <gen> to the
		 * elements in <arr>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <gen> - Generator function that is called with a position arguments and
		 *                returns a value of a type convertible to those pointed by <arr>
		 */
		template <class Ty, class Generator, size_t HiDim> inline
		static void generate_i(iterator<Ty> arr, const index_type_any<HiDim>& size, Generator gen)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			index_type pos;
			_impl_generate_i<Ty, Generator>(arr, size, gen, pos);
		}

		/*
		 * Assigns the value returned by successive calls to <gen> to the
		 * elements in NEW ARRAY.
		 *
		 * @param <size> - Size of array
		 * @param <gen> - Generator function that is called with a position arguments and
		 *                returns a value of a type convertible to those pointed by <arr>
		 * @return Pointer to NEW ARRAY
		 */
		template <class Ty, class Generator, size_t HiDim> _NODISCARD inline
		static iterator<Ty> generate_i_new(const index_type_any<HiDim>& size, Generator gen)
		{
			static_assert(HiDim >= Dim, "Parameter <size> too small");

			iterator<Ty> newarr = allocate<Ty>(size);
			generate_i<Ty>(newarr, size, gen);
			return newarr;
		}

	}; // class multi_array

	////////////////////////////////                ////////////////////////////////
	//------------------------------                ------------------------------//
	//------------------------------ multi_array<1> ------------------------------//
	//------------------------------                ------------------------------//
	////////////////////////////////                ////////////////////////////////

	template <>
	class multi_array <1U>
	{
	public:
		NW_CLASS_MAKE_STATIC(multi_array, <1U>);

		friend class multi_array;

		template <size_t Dim>
		friend class multi_array;

	protected:

		template <size_t HiDim>
		using index_type_any = std::array<size_t, HiDim>;

	public:

		//Array size / position type
		using index_type = index_type_any<1>;

		//Item type or top-level array for given item type
		template <class Ty>
		using item_type = Ty;
		
		//Pointer type for given item type
		template <class Ty>
		using free_iterator = item_type<Ty>*;

		template <class Ty>
		using iterator = item_type<Ty>*;

		template <class Ty>
		using const_iterator = iterator<Ty> const;

		template <class Ty>
		using iterator_allocatable = iterator<Ty>;

		//-------------------- iterator <=> free_iterator --------------------//

		template <class Ty> inline constexpr
		static free_iterator<Ty> pointer_remove_const_full(iterator<Ty> arr)
		{
			return const_cast<free_iterator<Ty>>(arr);
		}

		template <class Ty> inline constexpr
		static iterator<Ty> pointer_add_const_full(free_iterator<Ty> arr)
		{
			return const_cast<free_iterator<Ty>>(arr);
		}

		//-------------------- iterator <=> iterator_allocatable --------------------//

		template <class Ty> inline constexpr
		static iterator_allocatable<Ty> pointer_make_allocatable(iterator<Ty> arr)
		{
			return const_cast<iterator_allocatable<Ty>>(arr);
		}

		template <class Ty> inline constexpr
		static iterator<Ty> pointer_make_unallocatable(iterator_allocatable<Ty> arr)
		{
			return const_cast<iterator<Ty>>(arr);
		}

		//-------------------- Memory managing operations --------------------//

		/*
		 * Allocates a NEW ARRAY.
		 *
		 * @param <Ty> [template] - Item type of NEW ARRAY
		 * @param <size> - Size of NEW ARRAY
		 * @return Pointer to NEW ARRAY
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static iterator<Ty> allocate(const index_type_any<HiDim>& size)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return new Ty[size[HiDim - 1]];
		}
		
		/*
		 * Deallocates memory of array.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 */
		template <class Ty, size_t HiDim> inline
		static void deallocate(iterator<Ty> arr, const index_type_any<HiDim>& size)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			delete[] arr;
		}

		/*
		 * Return a reference to element on <pos> location.
		 *
		 * @param <arr> - Pointer to array
		 * @param <pos> - Position of item
		 * @return **See above**
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static Ty& get(iterator<Ty> arr, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return arr[pos[HiDim - 1]];
		}

		template <class Ty, class Args> _NODISCARD inline
		static Ty& get_pack(iterator<Ty> arr, Args&& args)
		{
			return get<Ty, 1>(arr, index_type{std::forward<Args>(args)});
		}

		/*
		 * Return a constant reference to element on <pos> location.
		 *
		 * @param <arr> - Pointer to multi_array
		 * @param <pos> - Position of item
		 * @return **See above**
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static const Ty& get_const(iterator<Ty> arr, const index_type_any<HiDim>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return arr[pos[HiDim - 1]];
		}

		//-------------------- Non-modifying sequence operations --------------------//

		/*
		 * Returns true if all the elements are equal to <val>
		 * or <size> has a zero, and false otherwise.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to search for
		 * @return **See above**
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static bool all(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty& val)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (!(arr[idx] == val)) return false;
			}
			return true;
		}

		/*
		 * Returns true if <pred> returns true for all the elements
		 * or <size> is all-zero, and false otherwise.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element
		 *                 and returns a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static bool all_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return std::all_of(arr, arr + size[HiDim - 1], pred);
		}

		/*
		 * Returns true if any of the elements is equal to <val>,
		 * and false otherwise or <size> is empty.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to search for
		 * @return **See above**
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
			static bool any(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty& val)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (arr[idx] == val) return true;
			}
			return false;
		}

		/*
		 * Returns true if <pred> returns true for any of the elements,
		 * and false otherwise or <size> is empty.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element
		 *                 and returns a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static bool any_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return std::any_of(arr, arr + size[HiDim - 1], pred);
		}

		/* Returns true if all the elements are not equal to <val>
		 * or <size> has a zero, and false otherwise.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to search for
		 * @return **See above**
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
			static bool none(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty& val)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (arr[idx] == val) return false;
			}
			return true;
		}

		/* Returns true if <pred> returns false for all the elements.
		 * or <size> is all-zero, and false otherwise.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element
		 *                 and returns a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static bool none_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return std::none_of(arr, arr + size[HiDim - 1], pred);
		}

		/*
		 * Applies function <fn> to each of the elements.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <fn> - Unary function that accepts an element as argument
		 */
		template <class Ty, class Function, size_t HiDim> inline
		static void for_each(iterator<Ty> arr, const index_type_any<HiDim>& size, Function fn)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			std::for_each(arr, arr + size[HiDim - 1], fn);
		}

		/*
		 * Applies function <fn> to each of the elements.
		 *
		 * @param <Layer> - Layer to stop at
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <fn> - Unary function that accepts an element as argument
		 */
		template <size_t Layer, class Ty, class Function, size_t HiDim> inline
		static void for_each_layer(iterator<Ty> arr, const index_type_any<HiDim>& size, Function fn)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");
			static_assert(Layer <= 1, "Template <Layer> too big");

			const auto cut_size = std_array::cut_back<Layer>(size);

			multi_array<1 - Layer>::template for_each<multi_array<Layer>::template const_iterator<Ty>, Function>(arr, cut_size, fn);
		}

	protected:

		template <class Ty, class Function_i, size_t HiDim, size_t HiDim2> inline
		static void _impl_for_each_i(iterator<Ty> arr, const index_type_any<HiDim>& size, Function_i fn, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");
			static_assert(HiDim2 >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				pos[HiDim2 - 1] = idx;
				fn(arr[idx], pos);
			}
		}

	public:

		/*
		 * Applies function <fn> to each of the elements.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <fn> - Unary function that accepts an element and
		 *               its position as arguments
		 */
		template <class Ty, class Function_i, size_t HiDim> inline
		static void for_each_i(iterator<Ty> arr, const index_type_any<HiDim>& size, Function_i fn)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			index_type_any<HiDim> pos;
			_impl_for_each_i(arr, size, fn, pos);
		}

		/*
		 * Applies function <fn> to each of the elements.
		 *
		 * @param <Layer> - Layer to stop at
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <fn> - Unary function that accepts an element and
		 *               its position as arguments
		 */
		template <size_t Layer, class Ty, class Function, size_t HiDim> inline
		static void for_each_i_layer(iterator<Ty> arr, const index_type_any<HiDim>& size, Function fn)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");
			static_assert(Layer <= 1, "Template <Layer> too big");

			const auto cut_size = std_array::cut_back<Layer>(size);
			index_type_any<1 - Layer> pos;

			multi_array<1 - Layer>::template _impl_for_each_i<multi_array<Layer>::template const_iterator<Ty>, Function>(arr, cut_size, fn, pos);
		}

		/*
		 * Returns a pointer to the first element that compares equal to <val>.
		 * If no such element found, the function returns nullptr.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to search for
		 * @param <pos> - Parameter to save found element's position
		 * @return **See above**
		 */
		template <class Ty, class Ty2, size_t HiDim, size_t HiDim2> inline
		static Ty* find(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty2& val, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");
			static_assert(HiDim2 >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (arr[idx] == val)
				{
					pos[HiDim2 - 1] = idx;
					return &arr[idx];
				}
			}
			return nullptr;
		}

		/*
		 * Returns a pointer to the first element that compares equal to <val>.
		 * If no such element found, the function returns nullptr.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to search for
		 * @return **See above**
		 */
		template <class Ty, class Ty2, size_t HiDim> _NODISCARD inline
		static Ty* find(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty2& val)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (arr[idx] == val)
				{
					return &arr[idx];
				}
			}
			return nullptr;
		}

		/*
		 * Returns a pointer to the first element for which <pred> returns true.
		 * If no such element found, the function returns nullptr.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @param <pos> - Parameter to save found element's position
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim, size_t HiDim2> inline
		static Ty* find_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");
			static_assert(HiDim2 >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (pred(arr[idx]))
				{
					pos[HiDim2 - 1] = idx;
					return &arr[idx];
				}
			}

			return nullptr;
		}

		/*
		 * Returns a pointer to the first element for which <pred> returns true.
		 * If no such element found, the function returns nullptr.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static Ty* find_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (pred(arr[idx]))
				{
					return &arr[idx];
				}
			}

			return nullptr;
		}

		/*
		 * Returns a pointer to the first element for which <pred> returns false.
		 * If no such element found, the function returns nullptr.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @param <pos> - Parameter to save found element's position
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim, size_t HiDim2> inline
		static Ty* find_if_not(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");
			static_assert(HiDim2 >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (!pred(arr[idx]))
				{
					pos[HiDim2 - 1] = idx;
					return &arr[idx];
				}
			}

			return nullptr;
		}

		/*
		 * Returns a pointer to the first element for which <pred> returns false.
		 * If no such element found, the function returns nullptr.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static Ty* find_if_not(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (!pred(arr[idx]))
				{
					return &arr[idx];
				}
			}

			return nullptr;
		}

		/*
		 * Returns the number of elements that compare equal to <val>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to match
		 * @return **See above**
		 */
		template <class Ty, class Ty2, size_t HiDim> _NODISCARD inline
		static size_t count(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty2& val)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return std::count(arr, arr + size[HiDim - 1], val);
		}

		/*
		 * Returns the number of elements for which <pred> is true.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @return **See above**
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> _NODISCARD inline
		static size_t count_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return std::count_if(arr, arr + size[HiDim - 1], pred);
		}

		/*
		 * Compares the elements or two arrays and returns the first element of
		 * <arr> that does not match.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @param <pos> - Parameter to save found element's position
		 * @return **See above**
		 */
		template <class Ty, class Ty2, size_t HiDim, size_t HiDim2> inline
		static Ty* mismatch(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");
			static_assert(HiDim2 >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				pos[HiDim2 - 1] = idx;
				if (!(arr[idx] == arr2[idx])) return &arr[idx];
			}

			return nullptr;
		}

		/*
		 * Compares the elements or two arrays and returns the first element of
		 * <arr> that does not match.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @return **See above**
		 */
		template <class Ty, class Ty2, size_t HiDim> _NODISCARD inline
		static Ty* mismatch(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (!(arr[idx] == arr2[idx])) return &arr[idx];
			}

			return nullptr;
		}

		/*
		 * Compares the elements or two arrays and returns true if the elements
		 * of both arrays match.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @return **See above**
		 */
		template <class Ty, class Ty2, size_t HiDim> _NODISCARD inline
		static bool equal(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			return std::equal(arr, arr + size[HiDim - 1], arr2);
		}

		//-------------------- Modifying sequence operations --------------------//

		/*
		 * Copies the elements of <arr> into <arr2>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr_result> - Pointer to result array
		 */
		template <class newTy, class Ty, size_t HiDim> inline
		static void copy(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<newTy> arr_result)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			std::copy(arr, arr + size[HiDim - 1], arr_result);
		}

		/*
		 * Copies the elements of <arr> into NEW ARRAY.
		 *
		 * @param <Ty> [template] - item type of NEW ARRAY. 
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @return Pointer to NEW ARRAY
		 */
		template <class newTy, class Ty, size_t HiDim> _NODISCARD inline
		static iterator<newTy> copy_new(iterator<Ty> arr, const index_type_any<HiDim>& size)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			iterator<newTy> newarr = allocate<newTy>(size);
			copy<newTy, Ty>(arr, size, newarr);
			return newarr;
		}

		/*
		 * Copies the elements of <arr> into <arr2> from which <pred> returns true.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr_result> - Pointer to result array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> inline
		static void copy_if(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty> arr_result, UnaryPredicate pred)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				if (pred(arr[idx])) arr_result[idx] = arr[idx];
			}
		}

		/*
		 * Moves the elements of <arr> into <arr2>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 */
		template <class Ty, class Ty2, size_t HiDim> inline
		static void move(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			std::move(arr, arr + size[HiDim - 1], arr2);
		}

		/*
		 * Moves the elements of <arr> into NEW ARRAY. 
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @return Pointer to NEW ARRAY
		 */
		template <class newTy, class Ty, size_t HiDim> _NODISCARD inline
		static iterator<newTy> move_new(iterator<Ty> arr, const index_type_any<HiDim>& size)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			iterator<newTy> newarr = allocate<newTy>(size);
			move<Ty, newTy>(arr, size, newarr);
			return newarr;
		}

		/*
		 * Applies an operation sequentially to the elements of <arr> and
		 * stores the result into <arr2>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr_result> - Pointer to result array
		 * @param <op> - Unary function that accepts an elements and
		 *               returns value convertible to the type pointed to by <arr_result>
		 */
		template <class newTy, class Ty, class UnaryOperation, size_t HiDim> inline
		static void transform(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<newTy> arr_result, UnaryOperation op)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			std::transform(arr, arr + size[HiDim - 1], arr_result, op);
		}

		/*
		 * Applies an operation sequentially to the elements of <arr> and
		 * stores the result into NEW ARRAY.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <op> - Unary function that accepts an elements and
		 *               returns value convertible to the type pointed to by <arr_result>
		 * @return Pointer to NEW ARRAY
		 */
		template <class newTy, class Ty, class UnaryOperation, size_t HiDim> _NODISCARD inline
		static iterator<newTy> transform_new(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryOperation op)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			iterator<newTy> newarr = allocate<newTy>(size);
			transform<newTy, Ty, UnaryOperation>(arr, size, newarr, op);
			return newarr;
		}

		/*
		 * Applies an operation sequentially to the elements of <arr> and <arr2> and
		 * stores the result into <arr2>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @param <arr_result> - Pointer to result array
		 * @param <binary_op> - Binary function that accepts two elements and
		 *                      returns value convertible to the type pointed to by <arr_result>
		 */
		template <class newTy, class Ty, class Ty2, class BinaryOperation, size_t HiDim> inline
		static void transform(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2, iterator<newTy> arr_result, BinaryOperation binary_op)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			std::transform(arr, arr + size[HiDim - 1], arr2, arr_result, binary_op);
		}

		/*
		 * Applies an operation sequentially to the elements of <arr> and <arr2> and
		 * stores the result into NEW ARRAY.
		 *
		 * @param <newTy> [template] - item type of NEW ARRAY
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr2> - Pointer to array #2
		 * @param <binary_op> - Binary function that accepts two elements and
		 *                      returns value convertible to the type pointed to by <arr_result>
		 * @return Pointer to NEW ARRAY
		 */
		template <class newTy, class Ty, class Ty2, class BinaryOperation, size_t HiDim> _NODISCARD inline
		static iterator<newTy> transform_new(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty2> arr2, BinaryOperation binary_op)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			iterator<newTy> newarr = allocate<newTy>(size);
			transform<newTy, Ty, Ty2, BinaryOperation>(arr, size, arr2, newarr, binary_op);
			return newarr;
		}

		/*
		 * Assigns <new_value> to all the elements that compare equal to <old_value>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <old_value> - Value to be replaced
		 * @param <new_value> - Replacement value
		 */
		template <class Ty, size_t HiDim> inline
		static void replace(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty& old_value, const Ty& new_value)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			std::replace(arr, arr + size[HiDim - 1], old_value, new_value);
		}

		/*
		 * Assigns <new_value> to all the elements for which <pred> returns true.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @param <new_value> - Value to assign to replaced elements
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> inline
		static void replace_if(iterator<Ty> arr, const index_type_any<HiDim>& size, UnaryPredicate pred, const Ty& new_value)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			std::replace_if(arr, arr + size[HiDim - 1], pred, new_value);
		}

		/*
		 * Copies the elements in <arr> to <arr2>, replacing the appearances
		 * of <old_value> by <new_value>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr_result> - Pointer to result array
		 * @param <old_value> - Value to be replaced
		 * @param <new_value> - Replacement value
		 */
		template <class Ty, size_t HiDim> inline
		static void replace_copy(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty> arr_result, const Ty& old_value, const Ty& new_value)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			std::replace_copy(arr, arr + size[HiDim - 1], arr_result, old_value, new_value);
		}

		/*
		 * Copies the elements in <arr> to <arr2>, replacing those for which
		 * <pred> returns true by <new_value>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of arrays
		 * @param <arr_result> - Pointer to result array
		 * @param <pred> - Unary function that accepts an element and returns
		 *                 a val convertible to bool
		 * @param <new_value> - Value to assign to replaced elements
		 */
		template <class Ty, class UnaryPredicate, size_t HiDim> inline
		static void replace_copy_if(iterator<Ty> arr, const index_type_any<HiDim>& size, iterator<Ty> arr_result, UnaryPredicate pred, const Ty& new_value)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			std::replace_copy_if(arr, arr + size[HiDim - 1], arr_result, pred, new_value);
		}

		/*
		 * Assigns <val> to all the elements in <arr>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <val> - Value to assign
		 */
		template <class Ty, size_t HiDim> inline
		static void fill(iterator<Ty> arr, const index_type_any<HiDim>& size, const Ty& val)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			std::fill(arr, arr + size[HiDim - 1], val);
		}

		/*
		 * Assigns <val> to all the elements in NEW ARRAY.
		 *
		 * @param <size> - Size of array
		 * @param <val> - Value to assign
		 * @return Pointer to NEW ARRAY
		 */
		template <class Ty, size_t HiDim> _NODISCARD inline
		static iterator<Ty> fill_new(const index_type_any<HiDim>& size, const Ty& val)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			iterator<Ty> newarr = allocate<Ty>(size);
			fill<Ty>(newarr, size, val);
			return newarr;
		}

		/*
		 * Assigns the value returned by successive calls to <gen> to the
		 * elements in <arr>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <gen> - Generator function that is called with no arguments and
		 *                returns a value of a type convertible to those pointed by <arr>
		 */
		template <class Ty, class Generator, size_t HiDim> inline
		static void generate(iterator<Ty> arr, const index_type_any<HiDim>& size, Generator gen)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				arr[idx] = gen();
			}
		}

		/*
		 * Assigns the value returned by successive calls to <gen> to the
		 * elements in NEW ARRAY.
		 *
		 * @param <size> - Size of array
		 * @param <gen> - Generator function that is called with no arguments and
		 *                returns a value of a type convertible to those pointed by <arr>
		 * @return Pointer to NEW ARRAY
		 */
		template <class Ty, class Generator, size_t HiDim> _NODISCARD inline
		static iterator<Ty> generate_new(const index_type_any<HiDim>& size, Generator gen)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			iterator<Ty> newarr = allocate<Ty>(size);
			generate<Ty>(newarr, size, gen);
			return newarr;
		}

	protected:

		template <class Ty, class Generator, size_t HiDim, size_t HiDim2> inline
		static void _impl_generate_i(iterator<Ty> arr, const index_type_any<HiDim>& size, Generator gen, index_type_any<HiDim2>& pos)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");
			static_assert(HiDim2 >= 1, "Parameter <size> too small");

			for (int idx = 0; idx < size[HiDim - 1]; idx++)
			{
				pos[HiDim2 - 1] = idx;
				arr[idx] = gen(pos);
			}
		}

	public:

		/*
		 * Assigns the value returned by successive calls to <gen> to the
		 * elements in <arr>.
		 *
		 * @param <arr> - Pointer to array
		 * @param <size> - Size of array
		 * @param <gen> - Generator function that is called with a position arguments and
		 *                returns a value of a type convertible to those pointed by <arr>
		 */
		template <class Ty, class Generator, size_t HiDim> inline
		static void generate_i(iterator<Ty> arr, const index_type_any<HiDim>& size, Generator gen)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			index_type pos;
			_impl_generate_i<Ty, Generator>(arr, size, gen, pos);
		}

		/*
		 * Assigns the value returned by successive calls to <gen> to the
		 * elements in NEW ARRAY.
		 *
		 * @param <size> - Size of array
		 * @param <gen> - Generator function that is called with a position arguments and
		 *                returns a value of a type convertible to those pointed by <arr>
		 * @return Pointer to NEW ARRAY
		 */
		template <class Ty, class Generator, size_t HiDim> _NODISCARD inline
		static iterator<Ty> generate_i_new(const index_type_any<HiDim>& size, Generator gen)
		{
			static_assert(HiDim >= 1, "Parameter <size> too small");

			iterator<Ty> newarr = allocate<Ty>(size);
			generate_i<Ty>(newarr, size, gen);
			return newarr;
		}

	}; // class multi_array<1>

	////////////////////////////////                ////////////////////////////////
	//------------------------------                ------------------------------//
	//------------------------------ multi_array<0> ------------------------------//
	//------------------------------                ------------------------------//
	////////////////////////////////                ////////////////////////////////

	template <>
	class multi_array <0U>
	{
	public:
		NW_CLASS_MAKE_STATIC(multi_array, <0U>);

		friend class multi_array;

		template <size_t Dim>
		friend class multi_array;

	protected:

		template <size_t HiDim>
		using index_type_any = std::array<size_t, HiDim>;

		template <class Ty>
		using iterator = Ty;

		template <size_t HiDim>
		using index_type_any = std::array<size_t, HiDim>;

		using index_type = index_type_any<0>;

	public:

		using index_type = index_type_any<0>;

		static inline constexpr size_t depth()
		{
			return 0;
		}

	protected:

		template <class Ty, class Function, size_t HiDim> inline
		static void for_each(iterator<Ty>& arr, const index_type_any<HiDim>& size, Function fn)
		{
			fn(arr);
		}

		template <class Ty, class Function_i, size_t HiDim, size_t HiDim2> inline
		static void _impl_for_each_i(iterator<Ty> arr, const index_type_any<HiDim>& size, Function_i fn, index_type_any<HiDim2>& pos)
		{
			f(arr, pos);
		}

	}; // class multi_array<0>

	//------------------------------                ------------------------------//
	//------------------------------                ------------------------------//
	//------------------------------    ALIASES     ------------------------------//
	//------------------------------                ------------------------------//
	//------------------------------                ------------------------------//


	using multi_array1D = multi_array<1>;
	using multi_array2D = multi_array<2>;
	using multi_array3D = multi_array<3>;
	using multi_array4D = multi_array<4>;
	using multi_array5D = multi_array<5>;
	using multi_array6D = multi_array<6>;
	using multi_array7D = multi_array<7>;
	using multi_array8D = multi_array<8>;

} // namespace nw