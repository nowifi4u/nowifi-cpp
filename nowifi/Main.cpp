#include <nowifi/array/linear_multi_array.hpp>
#include <nowifi/array/multi_array.hpp>
#include <nowifi/array/std_array.hpp>
#include <nowifi/array/stl.hpp>

#include <nowifi/compiler/assert.hpp>
#include <nowifi/compiler/class.hpp>
#include <nowifi/compiler/loop.hpp>
#include <nowifi/compiler/ternary_exec.hpp>

#include <nowifi/io/inputSeparator.hpp>
#include <nowifi/io/scanner.hpp>
#include <nowifi/io/writer.hpp>

#include <nowifi/math/bitwise.hpp>
#include <nowifi/math/funcIterator.hpp>
#include <nowifi/math/function.hpp>
#include <nowifi/math/map.hpp>
#include <nowifi/math/math.hpp>
#include <nowifi/math/modular.hpp>
#include <nowifi/math/safe.hpp>

#include <nowifi/math/reducer/minmax.hpp>
#include <nowifi/math/reducer/sum.hpp>

#include <nowifi/pack/compare.hpp>

#include <nowifi/string/former.hpp>
#include <nowifi/string/from_string.hpp>
#include <nowifi/string/splitter.hpp>
#include <nowifi/string/to_string.hpp>
#include <nowifi/string/traits.hpp>

#include <nowifi/util/map/binOps.hpp>
#include <nowifi/util/map/charMap.hpp>

#include <nowifi/util/consumer.hpp>
#include <nowifi/util/error.hpp>
#include <nowifi/util/fixed.hpp>
#include <nowifi/util/hash.hpp>
#include <nowifi/util/rawbin.hpp>
#include <nowifi/util/time.hpp>
#include <nowifi/util/unique.hpp>

#include <omp.h>
#include <stdio.h>

using namespace nw;
using namespace nw::global;

void test_multi_array()
{
	omp_set_num_threads(16);

	multi_array8D::index_type arr_size{ 2,3,4,5,6,7,8,9 };

	omp_set_num_threads(1);

	std::cout << "Allocating array..." << std::endl;
	auto arr = multi_array8D::generate_i_new<int>(arr_size, [](const multi_array8D::index_type& pos) {
		return pos[7]
			+ pos[6] * (9)
			+ pos[5] * (9 * 8)
			+ pos[4] * (9 * 8 * 7)
			+ pos[3] * (9 * 8 * 7 * 6)
			+ pos[2] * (9 * 8 * 7 * 6 * 5);
	});

	std::stringstream oss;
	multi_array8D::for_each_layer<2>(arr, arr_size, [&oss](multi_array2D::iterator<int> subarr) {
		Writer::_writeArray2D(subarr, 8, 9, "\t", "\n", oss);
		Writer::_write("\n\n\n", oss);
		//Writer_Console.writeArray2D(subarr, 8, 9, "\t", "\n").write("\n\n\n");
	});

	std::cout << oss.rdbuf();

	omp_set_num_threads(16);

	//std::cout << "Replacing value in array..." << std::endl;
	//multi_array8D::replace(arr, arr_size, 0, 1);

	//std::cout << "Old value present? " << (void*)multi_array8D::find(arr, arr_size, 0) << std::endl;

	std::cout << "Deallocating array..." << std::endl;
	multi_array8D::deallocate(arr, arr_size);

	omp_set_num_threads(1);
}

template <size_t size1, size_t size2>
void test_std_array_comp(const std::array<int, size1>& arr1, const std::array<int, size2>& arr2)
{
	std::cout << to_string::stl_array(arr1.begin(), arr1.end(), ",") << " vs " << to_string::stl_array(arr2.begin(), arr2.end(), ",") << "\n";

	std::cout << "compare: " << std_array::compare_lexicographical(arr1, arr2) << "\n";

	std::cout << "\n";
}

void test_std_array()
{
	std::array<int, 3> arr1{ 3,3,3 };
	std::array<int, 4> arr2{ 3,3,3,3 };
	std::array<int, 3> arr3{ 3,3,2 };
	std::array<int, 3> arr4{ 3,3,4 };

	test_std_array_comp(arr1, arr1);
	test_std_array_comp(arr1, arr2);
	test_std_array_comp(arr1, arr3);
	test_std_array_comp(arr1, arr4);

	test_std_array_comp(arr2, arr1);
	test_std_array_comp(arr2, arr2);
	test_std_array_comp(arr2, arr3);
	test_std_array_comp(arr2, arr4);

	test_std_array_comp(arr3, arr1);
	test_std_array_comp(arr3, arr2);
	test_std_array_comp(arr3, arr3);
	test_std_array_comp(arr3, arr4);

	test_std_array_comp(arr4, arr1);
	test_std_array_comp(arr4, arr2);
	test_std_array_comp(arr4, arr3);
	test_std_array_comp(arr4, arr4);
}

void main() {
	//test_std_array();
	//test_multi_array();

	std::cout << nw::ModularMath_Int<10007>::factorial_fast(100) 
		<< ' ' << nw::ModularMath_Int<10007>::factorial_nomem(100)
		<< ' ' << nw::ModularMath_Int<10007>::multiplicity_factorial(100)
		<< std::endl;
	system("pause");
}