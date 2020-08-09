#pragma once

#include <array>
#include <tuple>
#include <memory>

#include <nowifi/compiler/assert.hpp>

namespace nw {

	namespace std_array {

		template <class Ty, size_t size>
		using array_ref = std::array<Ty&, size>;

		template <class Ty, size_t size>
		using array_constref = std::array<const Ty&, size>;

		//-------------------- concat arrays --------------------//

		template <class Ty, size_t size1, size_t size2>
		std::array<Ty, size1 + size2> concat(
			const std::array<Ty, size1>& src1,
			const std::array<Ty, size2>& src2)
		{
			std::array<Ty, size1 + size2> src;
			auto joint = std::copy_n(src1.begin(), size1, src.begin());
			/*         */std::copy_n(src2.begin(), size2, joint);
			return src;
		}

		template <class Ty, size_t size1, size_t size2, size_t size3>
		std::array<Ty, size1 + size2 + size3> concat(
			const std::array<Ty, size1>& src1,
			const std::array<Ty, size2>& src2,
			const std::array<Ty, size3>& src3)
		{
			std::array<Ty, size1 + size2 + size3> src;
			auto joint = std::copy_n(src1.begin(), size1, src.begin());
			/* */joint = std::copy_n(src2.begin(), size2, joint);
			/*         */std::copy_n(src3.begin(), size3, joint);
			return src;
		}

		template <class Ty, size_t size1, size_t size2, size_t size3, size_t size4>
		std::array<Ty, size1 + size2 + size3 + size4> concat(
			const std::array<Ty, size1>& src1,
			const std::array<Ty, size2>& src2,
			const std::array<Ty, size3>& src3,
			const std::array<Ty, size4>& src4)
		{
			std::array<Ty, size1 + size2 + size3 + size4> src;
			auto joint = std::copy_n(src1.begin(), size1, src.begin());
			/* */joint = std::copy_n(src2.begin(), size2, joint);
			/* */joint = std::copy_n(src3.begin(), size3, joint);
			/*         */std::copy_n(src4.begin(), size4, joint);
			return src;
		}

		//-------------------- concat array + values --------------------//

		template <class Ty, size_t size1, size_t size2>
		std::array<Ty, size1 + size2> concat(
			const std::array<Ty, size1>& src1,
			const array_constref<Ty, size2>& src2)
		{
			std::array<Ty, size1 + size2> src;
			auto joint = std::copy_n(src1.begin(), size1, src.begin());
			/*         */std::copy_n(src2.begin(), size2, joint);
			return src;
		}

		template <class Ty, size_t size>
		std::array<Ty, size + 1> concat(
			const std::array<Ty, size>& src,
			const Ty& value1)
		{
			return concat<Ty, size, 1>(src, std::array<const Ty&, 1>{ value1 });
		}

		template <class Ty, size_t size>
		std::array<Ty, size + 2> concat(
			const std::array<Ty, size>& src,
			const Ty& value1,
			const Ty& value2)
		{
			return concat<Ty, size, 2>(src, std::array<const Ty&, 2>{ value1, value2 });
		}

		template <class Ty, size_t size>
		std::array<Ty, size + 3> concat(
			const std::array<Ty, size>& src,
			const Ty& value1,
			const Ty& value2,
			const Ty& value3)
		{
			return concat<Ty, size, 3>(src, std::array<const Ty&, 3>{ value1, value2, value3 });
		}

		template <class Ty, size_t size>
		std::array<Ty, size + 4> concat(
			const std::array<Ty, size>& src,
			const Ty& value1,
			const Ty& value2,
			const Ty& value3,
			const Ty& value4)
		{
			return concat<Ty, size, 4>(src, std::array<const Ty&, 4>{ value1, value2, value3, value4 });
		}

		//-------------------- concat values + array --------------------//

		template <class Ty, size_t size1, size_t size2>
		std::array<Ty, size1 + size2> concat(
			const array_constref<Ty, size2>& src1,
			const std::array<Ty, size1>& src2)
		{
			std::array<Ty, size1 + size2> src;
			auto joint = std::copy_n(src1.begin(), size1, src.begin());
			/*         */std::copy_n(src2.begin(), size2, joint);
			return src;
		}

		template <class Ty, size_t size>
		std::array<Ty, size + 1> concat(
			const Ty& value1,
			const std::array<Ty, size>& src)
		{
			return concat<Ty, size, 1>(std::array<const Ty&, 1>{ value1 }, src);
		}

		template <class Ty, size_t size>
		std::array<Ty, size + 2> concat(
			const Ty& value1,
			const Ty& value2,
			const std::array<Ty, size>& src)
		{
			return concat<Ty, size, 2>(std::array<const Ty&, 2>{ value1, value2 }, src);
		}

		template <class Ty, size_t size>
		std::array<Ty, size + 3> concat(
			const Ty& value1,
			const Ty& value2,
			const Ty& value3,
			const std::array<Ty, size>& src)
		{
			return concat<Ty, size, 3>(std::array<const Ty&, 3>{ value1, value2, value3 }, src);
		}

		template <class Ty, size_t size>
		std::array<Ty, size + 4> concat(
			const Ty& value1,
			const Ty& value2,
			const Ty& value3,
			const Ty& value4,
			const std::array<Ty, size>& src)
		{
			return concat<Ty, size, 4>(std::array<const Ty&, 4>{ value1, value2, value3, value4 }, src);
		}

		//-------------------- concat values --------------------//

		template <class Ty, size_t size>
		std::array<Ty, size> concat(const array_constref<Ty, size>& src)
		{
			std::array<Ty, size> arr;
			std::copy_n(src.begin(), size, arr.begin());
			return arr;
		}

		template <class Ty>
		std::array<Ty, 1> concat(
			const Ty& value1)
		{
			return concat<Ty, 1>(array_constref<Ty, 1>{ value1 });
		}

		template <class Ty>
		std::array<Ty, 2> concat(
			const Ty& value1,
			const Ty& value2)
		{
			return concat<Ty, 2>(array_constref<Ty, 2>{ value1, value2 });
		}

		template <class Ty>
		std::array<Ty, 3> concat(
			const Ty& value1,
			const Ty& value2,
			const Ty& value3)
		{
			return concat<Ty, 3>(array_constref<Ty, 3>{ value1, value2, value3 });
		}

		template <class Ty>
		std::array<Ty, 4> concat(
			const Ty& value1,
			const Ty& value2,
			const Ty& value3,
			const Ty& value4)
		{
			return concat<Ty, 4>(array_constref<Ty, 4>{ value1, value2, value3, value4 });
		}

		template <class Ty>
		std::array<Ty, 5> concat(
			const Ty& value1,
			const Ty& value2,
			const Ty& value3,
			const Ty& value4,
			const Ty& value5)
		{
			return concat<Ty, 5>(array_constref<Ty, 5>{ value1, value2, value3, value4, value5 });
		}

		template <class Ty>
		std::array<Ty, 6> concat(
			const Ty& value1,
			const Ty& value2,
			const Ty& value3,
			const Ty& value4,
			const Ty& value5,
			const Ty& value6)
		{
			return concat<Ty, 6>(array_constref<Ty, 6>{ value1, value2, value3, value4, value5, value6 });
		}

		template <class Ty>
		std::array<Ty, 7> concat(
			const Ty& value1,
			const Ty& value2,
			const Ty& value3,
			const Ty& value4,
			const Ty& value5,
			const Ty& value6,
			const Ty& value7)
		{
			return concat<Ty, 7>(array_constref<Ty, 7>{ value1, value2, value3, value4, value5, value6, value7 });
		}

		template <class Ty>
		std::array<Ty, 8> concat(
			const Ty& value1,
			const Ty& value2,
			const Ty& value3,
			const Ty& value4,
			const Ty& value5,
			const Ty& value6,
			const Ty& value7,
			const Ty& value8)
		{
			return concat<Ty, 8>(array_constref<Ty, 8>{ value1, value2, value3, value4, value5, value6, value7, value8 });
		}

		//-------------------- cut --------------------//

		template <size_t delta, class Ty, size_t size>
		void cut_back(
			const std::array<Ty, size>& src,
			std::array<Ty, delta>& arr1)
		{
			compile_assert<(size >= delta)>::assert(); // delta argument too big

			std::copy_n(src.begin(), delta, arr1.begin());
		}

		template <size_t delta, class Ty, size_t size>
		std::array<Ty, delta> cut_back(
			const std::array<Ty, size>& src)
		{
			compile_assert<(size >= delta)>::assert(); // delta argument too big

			std::array<Ty, delta> arr1;

			cut_back<delta, Ty, size>(src, arr1);

			return arr1;
		}

		template <size_t delta, class Ty, size_t size>
		void cut_front(
			const std::array<Ty, size>& src,
			std::array<Ty, delta>& arr1)
		{
			compile_assert<(size >= delta)>::assert(); // delta argument too big

			auto begin = src.begin() + delta;
			std::copy_n(begin, size - delta, arr1.begin());
		}

		template <size_t delta, class Ty, size_t size>
		std::array<Ty, delta> cut_front(
			const std::array<Ty, size>& src)
		{
			std::array<Ty, delta> arr;
			cut_front<delta, Ty, size>(src, arr);
			return arr;
		}

		template <size_t delta, class Ty, size_t size>
		void cut(
			const std::array<Ty, size>& src,
			std::array<Ty, delta>& arr1,
			std::array<Ty, size - delta>& arr2)
		{
			compile_assert<(size >= delta)>::assert(); // delta argument too big

			auto joint = std::copy_n(src.begin(), delta, arr1.begin());
			/*         */std::copy_n(joint, size - delta, arr2.begin());
		}

		//-------------------- pop_front --------------------//

		template <size_t delta, class Ty, size_t size>
		std::array<Ty, size - delta> cut(
			const std::array<Ty, size>& src,
			array_ref<Ty, delta> output)
		{
			compile_assert<(size >= delta)>::assert(); // delta argument too big

			std::copy_n(src.begin(), delta, output.begin());

			return cut_front<delta, Ty, size>(src);
		}


		template <class Ty, size_t size>
		std::array<Ty, size - 1> cut(
			const std::array<Ty, size>& src,
			Ty& output1)
		{
			return cut<1, Ty, size>(src, array_ref<Ty, 1>{ output1 });
		}

		template <class Ty, size_t size>
		std::array<Ty, size - 2> cut(
			const std::array<Ty, size>& src,
			Ty& output1,
			Ty& output2)
		{
			return cut<2, Ty, size>(src, array_ref<Ty, 2>{ output1, output2 });
		}

		template <class Ty, size_t size>
		std::array<Ty, size - 3> cut(
			const std::array<Ty, size>& src,
			Ty& output1,
			Ty& output2,
			Ty& output3)
		{
			return cut<3, Ty, size>(src, array_ref<Ty, 3>{ output1, output2, output3 });
		}

		template <class Ty, size_t size>
		std::array<Ty, size - 4> cut(
			const std::array<Ty, size>& src,
			Ty& output1,
			Ty& output2,
			Ty& output3,
			Ty& output4)
		{
			return cut<4, Ty, size>(src, array_ref<Ty, 4>{ output1, output2, output3, output4 });
		}

		//-------------------- pop_back --------------------//

		template <size_t delta, class Ty, size_t size>
		std::array<Ty, size - delta> cut(
			array_ref<Ty, delta>& output,
			const std::array<Ty, size>& src)
		{
			compile_assert<(size >= delta)>::assert(); // delta argument too big

			auto pivot = src.begin() + delta;

			std::copy_n(pivot, delta, output.begin());

			return cut_back<delta, Ty, size>(src);
		}

		template <class Ty, size_t size>
		std::array<Ty, size - 1> cut(
			Ty& output1,
			const std::array<Ty, size>& src)
		{
			return cut<1, Ty, size>(array_ref<Ty, 1>{ output1 }, src);
		}

		template <class Ty, size_t size>
		std::array<Ty, size - 2> cut(
			Ty& output1,
			Ty& output2,
			const std::array<Ty, size>& src)
		{
			return cut<2, Ty, size>(array_ref<Ty, 2>{ output1, output2 }, src);
		}

		template <class Ty, size_t size>
		std::array<Ty, size - 3> cut(
			Ty& output1,
			Ty& output2,
			Ty& output3,
			const std::array<Ty, size>& src)
		{
			return cut<3, Ty, size>(array_ref<Ty, 3>{ output1, output2, output3 }, src);
		}

		template <class Ty, size_t size>
		std::array<Ty, size - 4> cut(
			Ty& output1,
			Ty& output2,
			Ty& output3,
			Ty& output4,
			const std::array<Ty, size>& src)
		{
			return cut<4, Ty, size>(array_ref<Ty, 4>{ output1, output2, output3, output4 }, src);
		}

		//-------------------- clone_raw --------------------//

		template <class Ty, size_t size>
		Ty* clone_raw(const std::array<Ty, size>& src)
		{
			Ty* arr = new Ty[size];
			std::copy_n(src.begin(), size, arr);
			return arr;
		}

		template <class Ty, size_t size>
		std::unique_ptr<Ty> clone_unique(const std::array<Ty, size>& src)
		{
			std::unique_ptr<Ty> arr = std::make_unique<Ty>(size);
			std::copy_n(src.begin(), size, arr.get());
			return arr;
		}

		//-------------------- clone_from --------------------//

		template <class Ty, size_t size>
		std::array<Ty, size> clone_from(const Ty* src)
		{
			std::array<Ty, size> src;
			std::copy_n(src, size, src.begin());
			return src;
		}

		template <class Ty, size_t size>
		std::array<Ty, size> clone_from(const std::unique_ptr<Ty>& src)
		{
			return clone_from<Ty, size>(src.get());
		}

		//-------------------- create --------------------//

		template <class Ty, size_t size>
		void _impl_create(std::array<Ty, size>& arr, const Ty& arg1)
		{
			arr[size - 1] = arg1;
		}

		template <class Ty, size_t size, class... Args>
		void _impl_create(std::array<Ty, size>& arr, const Ty& arg1, const Args&... args)
		{
			arr[size - 1 - sizeof...(args)] = arg1;
			return _impl_create(arr, args...);
		}

		template <class Ty, size_t size, class... Args>
		std::array<Ty, size> create(const Args&... args)
		{
			std::array<Ty, size> arr;
			_impl_create(arr, args...);
			return arr;
		}

	} // namespace std_array

} // namespace nw