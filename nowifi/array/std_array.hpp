#pragma once

#include <nowifi/compiler/assert.hpp>
#include <nowifi/compiler/loop.hpp>
#include <nowifi/pack/compare.hpp>

#include <array>
#include <tuple>
#include <memory>

namespace nw {

	namespace std_array {

		template <class Ty, size_t size>
		using array_ref = std::array<Ty&, size>;

		template <class Ty, size_t size>
		using array_constref = std::array<const Ty&, size>;

		////////////////////////////////             ////////////////////////////////
		//------------------------------             ------------------------------//
		//------------------------------     STL     ------------------------------//
		//------------------------------             ------------------------------//
		////////////////////////////////             ////////////////////////////////

		//-------------------- Non-modifying sequence operations --------------------//

		template <class Ty, size_t size> inline
		bool all_of(const std::array<Ty, size>& src, const Ty& val)
		{
			return !for_loop::any_i<size>::call(
				[&src, &val](size_t idx)
			{
				return src[idx] != val;
			});
		}

		template <class Ty, size_t size> inline
		bool any_of(const std::array<Ty, size>& src, const Ty& val)
		{
			return for_loop::any_i<size>::call(
				[&src, &val](size_t idx)
			{
				return src[idx] == val;
			});
		}

		template <class Ty, size_t size> inline
		bool none_of(const std::array<Ty, size>& src, const Ty& val)
		{
			return !for_loop::any_i<size>::call(
				[&src, &val](size_t idx)
			{
				return src[idx] == val;
			});
		}

		template <class Ty, size_t size, class Function> inline
		void for_each(std::array<Ty, size>& src, Function fn)
		{
			for_loop::raw_i<size>::call(
				[&src, &fn](size_t idx)
			{
				fn(src[idx]);
			});
		}

		template <class Ty, size_t size, class Function> inline
		void for_each_i(std::array<Ty, size>& src, Function fn)
		{
			for_loop::raw_i<size>::call(
				[&src, &fn](size_t idx)
			{
				fn(src[idx], idx);
			});
		}

		template <class Ty, size_t size> inline
		Ty* find(std::array<Ty, size>& src, const Ty& val)
		{
			return for_loop::any_ptr_i<size>::template call<Ty*>(
				[&src, &val](size_t idx)
			{
				return (src[idx] == val ? &src[idx] : nullptr);
			});
		}

		template <class Ty, size_t size, class UnaryPredicate> inline
		Ty* find_if(std::array<Ty, size>& src, UnaryPredicate pred)
		{
			return for_loop::any_ptr_i<size>::template call<Ty*>(
				[&src, &pred](size_t idx)
			{
				return (pred(src[idx]) ? &src[idx] : nullptr);
			});
		}

		template <class Ty, size_t size, class UnaryPredicate> inline
		Ty* find_if_not(std::array<Ty, size>& src, UnaryPredicate pred)
		{
			return for_loop::any_ptr_i<size>::template call<Ty*>(
				[&src, &pred](size_t idx)
			{
				return (pred(src[idx]) ? nullptr : &src[idx]);
			});
		}

		template <class Ty, size_t size> inline
		size_t count(const std::array<Ty, size>& src, const Ty& val)
		{
			return for_loop::reduce_i<size>::template call<size_t>(0U,
				[&src](size_t idx)
			{
				return src[idx];
			},
				[&val](size_t result, const Ty& v)
			{
				return result + (v == val);
			});
		}

		////////////////////////////////             ////////////////////////////////
		//------------------------------             ------------------------------//
		//------------------------------    CONCAT   ------------------------------//
		//------------------------------             ------------------------------//
		////////////////////////////////             ////////////////////////////////

		//-------------------- concat arrays --------------------//

		template <class Ty, size_t size1, size_t size2> inline
		std::array<Ty, size1 + size2> concat(
			const std::array<Ty, size1>& src1,
			const std::array<Ty, size2>& src2)
		{
			std::array<Ty, size1 + size2> src;
			auto joint = std::copy_n(src1.begin(), size1, src.begin());
			/*         */std::copy_n(src2.begin(), size2, joint);
			return src;
		}

		template <class Ty, size_t size1, size_t size2, size_t size3> inline
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

		template <class Ty, size_t size1, size_t size2, size_t size3, size_t size4> inline
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

		template <class Ty, size_t size1, size_t size2> inline
		std::array<Ty, size1 + size2> concat(
			const std::array<Ty, size1>& src1,
			const array_constref<Ty, size2>& src2)
		{
			std::array<Ty, size1 + size2> src;
			auto joint = std::copy_n(src1.begin(), size1, src.begin());
			/*         */std::copy_n(src2.begin(), size2, joint);
			return src;
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size + 1> concat(
			const std::array<Ty, size>& src,
			const Ty& value1)
		{
			return concat<Ty, size, 1>(src, std::array<const Ty&, 1>{ value1 });
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size + 2> concat(
			const std::array<Ty, size>& src,
			const Ty& value1,
			const Ty& value2)
		{
			return concat<Ty, size, 2>(src, std::array<const Ty&, 2>{ value1, value2 });
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size + 3> concat(
			const std::array<Ty, size>& src,
			const Ty& value1,
			const Ty& value2,
			const Ty& value3)
		{
			return concat<Ty, size, 3>(src, std::array<const Ty&, 3>{ value1, value2, value3 });
		}

		template <class Ty, size_t size> inline
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

		template <class Ty, size_t size1, size_t size2> inline
		std::array<Ty, size1 + size2> concat(
			const array_constref<Ty, size2>& src1,
			const std::array<Ty, size1>& src2)
		{
			std::array<Ty, size1 + size2> src;
			auto joint = std::copy_n(src1.begin(), size1, src.begin());
			/*         */std::copy_n(src2.begin(), size2, joint);
			return src;
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size + 1> concat(
			const Ty& value1,
			const std::array<Ty, size>& src)
		{
			return concat<Ty, size, 1>(std::array<const Ty&, 1>{ value1 }, src);
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size + 2> concat(
			const Ty& value1,
			const Ty& value2,
			const std::array<Ty, size>& src)
		{
			return concat<Ty, size, 2>(std::array<const Ty&, 2>{ value1, value2 }, src);
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size + 3> concat(
			const Ty& value1,
			const Ty& value2,
			const Ty& value3,
			const std::array<Ty, size>& src)
		{
			return concat<Ty, size, 3>(std::array<const Ty&, 3>{ value1, value2, value3 }, src);
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size + 4> concat(
			const Ty& value1,
			const Ty& value2,
			const Ty& value3,
			const Ty& value4,
			const std::array<Ty, size>& src)
		{
			return concat<Ty, size, 4>(std::array<const Ty&, 4>{ value1, value2, value3, value4 }, src);
		}

		////////////////////////////////             ////////////////////////////////
		//------------------------------             ------------------------------//
		//------------------------------      CUT    ------------------------------//
		//------------------------------             ------------------------------//
		////////////////////////////////             ////////////////////////////////

		template <size_t delta, class Ty, size_t size> inline
		void cut_back(
			const std::array<Ty, size>& src,
			std::array<Ty, size - delta>& arr1)
		{
			static_assert(size >= delta, "Template <delta> too big");

			std::copy_n(src.begin(), size - delta, arr1.begin());
		}

		template <size_t delta, class Ty, size_t size> inline
		std::array<Ty, size - delta> cut_back(
			const std::array<Ty, size>& src)
		{
			static_assert(size >= delta, "Template <delta> too big");

			std::array<Ty, size - delta> arr1;

			cut_back<delta, Ty, size>(src, arr1);

			return arr1;
		}

		template <size_t delta, class Ty, size_t size> inline
		void cut_front(
			const std::array<Ty, size>& src,
			std::array<Ty, size - delta>& arr1)
		{
			static_assert(size >= delta, "Template <delta> too big");

			auto begin = src.begin() + delta;
			std::copy_n(begin, size - delta, arr1.begin());
		}

		template <size_t delta, class Ty, size_t size> inline
		std::array<Ty, size - delta> cut_front(
			const std::array<Ty, size>& src)
		{
			std::array<Ty, size - delta> arr;
			cut_front<delta, Ty, size>(src, arr);
			return arr;
		}

		template <size_t delta, class Ty, size_t size> inline
		void cut(
			const std::array<Ty, size>& src,
			std::array<Ty, delta>& arr1,
			std::array<Ty, size - delta>& arr2)
		{
			static_assert(size >= delta, "Template <delta> too big");

			auto joint = std::copy_n(src.begin(), delta, arr1.begin());
			/*         */std::copy_n(joint, size - delta, arr2.begin());
		}

		//-------------------- pop_front --------------------//

		template <size_t delta, class Ty, size_t size> inline
		std::array<Ty, size - delta> cut(
			const std::array<Ty, size>& src,
			array_ref<Ty, delta> output)
		{
			static_assert(size >= delta, "Template <delta> too big");

			std::copy_n(src.begin(), delta, output.begin());

			return cut_front<delta, Ty, size>(src);
		}


		template <class Ty, size_t size> inline
		std::array<Ty, size - 1> cut(
			const std::array<Ty, size>& src,
			Ty& output1)
		{
			return cut<1, Ty, size>(src, array_ref<Ty, 1>{ output1 });
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size - 2> cut(
			const std::array<Ty, size>& src,
			Ty& output1,
			Ty& output2)
		{
			return cut<2, Ty, size>(src, array_ref<Ty, 2>{ output1, output2 });
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size - 3> cut(
			const std::array<Ty, size>& src,
			Ty& output1,
			Ty& output2,
			Ty& output3)
		{
			return cut<3, Ty, size>(src, array_ref<Ty, 3>{ output1, output2, output3 });
		}

		template <class Ty, size_t size> inline
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

		template <size_t delta, class Ty, size_t size> inline
		std::array<Ty, size - delta> cut(
			array_ref<Ty, delta>& output,
			const std::array<Ty, size>& src)
		{
			static_assert(size >= delta, "Template <delta> too big");

			auto pivot = src.begin() + delta;

			std::copy_n(pivot, delta, output.begin());

			return cut_back<delta, Ty, size>(src);
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size - 1> cut(
			Ty& output1,
			const std::array<Ty, size>& src)
		{
			return cut<1, Ty, size>(array_ref<Ty, 1>{ output1 }, src);
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size - 2> cut(
			Ty& output1,
			Ty& output2,
			const std::array<Ty, size>& src)
		{
			return cut<2, Ty, size>(array_ref<Ty, 2>{ output1, output2 }, src);
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size - 3> cut(
			Ty& output1,
			Ty& output2,
			Ty& output3,
			const std::array<Ty, size>& src)
		{
			return cut<3, Ty, size>(array_ref<Ty, 3>{ output1, output2, output3 }, src);
		}

		template <class Ty, size_t size> inline
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

		template <class Ty, size_t size> inline
		Ty* clone_raw(const std::array<Ty, size>& src)
		{
			Ty* arr = new Ty[size];
			std::copy_n(src.begin(), size, arr);
			return arr;
		}

		template <class Ty, size_t size> inline
		std::unique_ptr<Ty> clone_unique(const std::array<Ty, size>& src)
		{
			std::unique_ptr<Ty> arr = std::make_unique<Ty>(size);
			std::copy_n(src.begin(), size, arr.get());
			return arr;
		}

		//-------------------- clone_from --------------------//

		template <class Ty, size_t size> inline
		std::array<Ty, size> clone_from(const Ty* src)
		{
			std::array<Ty, size> result;
			std::copy_n(src, size, src.begin());
			return src;
		}

		template <class Ty, size_t size> inline
		std::array<Ty, size> clone_from(const std::unique_ptr<Ty>& src)
		{
			return clone_from<Ty, size>(src.get());
		}

		//-------------------- comparison --------------------//

		template <class Ty, size_t size1, size_t size2> inline
		int compare_common(const std::array<Ty, size1>& src1, const std::array<Ty, size2>& src2)
		{
			constexpr size_t size_min = Compare::min(size1, size2);
			return for_loop::any_int_i<size_min>::call([&src1, &src2](size_t idx)
			{
				if (src1[idx] < src2[idx]) return -1;
				else if (src1[idx] == src2[idx]) return 0;
				else /* src1[idx] > src2[idx] */ return 1;
			});
		}

		template <class Ty, size_t size1, size_t size2> inline
		int compare_lexicographical(const std::array<Ty, size1>& src1, const std::array<Ty, size2>& src2)
		{
			const int cmp = compare_common(src1, src2);
			if (cmp != 0) return cmp;
			else return (int)size1 - size2;
		}

	} // namespace std_array

} // namespace nw