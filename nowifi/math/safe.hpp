#pragma omce

#include <stdexcept>
#include <typeinfo>
#include <string>

namespace nw {

	namespace SafeMath {

		template <typename baseTy>
		baseTy _add_impl(baseTy val1, baseTy val2)
		{
			baseTy res = val1 + val2;
			if ( res < val1 )
			{
				throw std::overflow_error((std::string) typeid(baseTy).name() + " type addition overflow");
			}
			return res;
		}

		char add_int8(char val1, char val2)
		{
			return _add_impl<char>(val1, val2);
		}

		unsigned char add_int8(unsigned char val1, unsigned char val2)
		{
			return _add_impl<unsigned char>(val1, val2);
		}

		short add_int16(short val1, short val2)
		{
			return _add_impl<short>(val1, val2);
		}

		unsigned short add_int16(unsigned short val1, unsigned short val2)
		{
			return _add_impl<unsigned short>(val1, val2);
		}

		int add_int32(int val1, int val2)
		{
			return _add_impl<int>(val1, val2);
		}

		unsigned int add_int32(unsigned int val1, unsigned int val2)
		{
			return _add_impl<unsigned int>(val1, val2);
		}

		long long add_int64(long long val1, long long val2)
		{
			return _add_impl<long long>(val1, val2);
		}

		unsigned long long add_int64(unsigned long long val1, unsigned long long val2)
		{
			return _add_impl<unsigned long long>(val1, val2);
		}

		template <typename baseTy>
		baseTy _subtract_impl(baseTy val1, baseTy val2)
		{
			baseTy res = val1 - val2;
			if (res > val1)
			{
				throw std::overflow_error((std::string) typeid(baseTy).name() + " type addition overflow");
			}
			return res;
		}
	
		template <typename baseTy, typename upTy>
		baseTy _multiply_impl(baseTy val1, baseTy val2)
		{
			upTy res = (upTy)val1 * val2;
			if ( (baseTy) (res >> (sizeof(baseTy) * 8) ) )
			{
				throw std::overflow_error((std::string) typeid(baseTy).name() + " type multiplication overflow");
			}
			return res;
		}

		char multiply_int8(char val1, char val2)
		{
			return _multiply_impl<char, short>(val1, val2);
		}

		char multiply_uint8(unsigned char val1, unsigned char val2)
		{
			return _multiply_impl<unsigned char, unsigned short>(val1, val2);
		}

		short multiply_int16(short val1, short val2)
		{
			return _multiply_impl<short, int>(val1, val2);
		}

		short multiply_uint16(unsigned short val1, unsigned short val2)
		{
			return _multiply_impl<unsigned short, unsigned int>(val1, val2);
		}

		int multiply_int32(int val1, int val2)
		{
			return _multiply_impl<int, long long>(val1, val2);
		}

		int multiply_uint32(unsigned int val1, unsigned int val2)
		{
			return _multiply_impl<unsigned int, unsigned long long>(val1, val2);
		}

	} // namespace SafeMath

} // namespace nw