#pragma once

#include <stdexcept>
#include <typeinfo>
#include <string>

namespace nw {

	namespace SafeMath {

		//------------------------------     ------------------------------//
		//------------------------------ ADD ------------------------------//
		//------------------------------     ------------------------------//

		template <typename baseTy> [[NODISCARD]]
		constexpr baseTy _add_impl(baseTy val1, baseTy val2)
		{
			baseTy res = val1 + val2;
			if ( res < val1 )
			{
				throw std::overflow_error((std::string) typeid(baseTy).name() + " addition overflow");
			}
			return res;
		}

		[[NODISCARD]]
		constexpr char add_int8(char val1, char val2)
		{
			return _add_impl<char>(val1, val2);
		}

		[[NODISCARD]]
		constexpr unsigned char add_int8(unsigned char val1, unsigned char val2)
		{
			return _add_impl<unsigned char>(val1, val2);
		}

		[[NODISCARD]]
		constexpr short add_int16(short val1, short val2)
		{
			return _add_impl<short>(val1, val2);
		}

		[[NODISCARD]]
		constexpr unsigned short add_int16(unsigned short val1, unsigned short val2)
		{
			return _add_impl<unsigned short>(val1, val2);
		}

		[[NODISCARD]]
		constexpr int add_int32(int val1, int val2)
		{
			return _add_impl<int>(val1, val2);
		}

		[[NODISCARD]]
		constexpr unsigned int add_int32(unsigned int val1, unsigned int val2)
		{
			return _add_impl<unsigned int>(val1, val2);
		}

		[[NODISCARD]]
		constexpr long long add_int64(long long val1, long long val2)
		{
			return _add_impl<long long>(val1, val2);
		}

		[[NODISCARD]]
		constexpr unsigned long long add_int64(unsigned long long val1, unsigned long long val2)
		{
			return _add_impl<unsigned long long>(val1, val2);
		}

		//------------------------------          ------------------------------//
		//------------------------------ SUBTRACT ------------------------------//
		//------------------------------          ------------------------------//

		template <typename baseTy> [[NODISCARD]]
		constexpr baseTy _sub_impl(baseTy val1, baseTy val2)
		{
			baseTy res = val1 - val2;
			if (res > val1)
			{
				throw std::underflow_error((std::string) typeid(baseTy).name() + " subion underflow");
			}
			return res;
		}

		[[NODISCARD]]
		constexpr char sub_int8(char val1, char val2)
		{
			return _sub_impl<char>(val1, val2);
		}

		[[NODISCARD]]
		constexpr unsigned char sub_int8(unsigned char val1, unsigned char val2)
		{
			return _sub_impl<unsigned char>(val1, val2);
		}

		[[NODISCARD]]
		constexpr short sub_int16(short val1, short val2)
		{
			return _sub_impl<short>(val1, val2);
		}

		[[NODISCARD]]
		constexpr unsigned short sub_int16(unsigned short val1, unsigned short val2)
		{
			return _sub_impl<unsigned short>(val1, val2);
		}

		[[NODISCARD]]
		constexpr int sub_int32(int val1, int val2)
		{
			return _sub_impl<int>(val1, val2);
		}

		[[NODISCARD]]
		constexpr unsigned int sub_int32(unsigned int val1, unsigned int val2)
		{
			return _sub_impl<unsigned int>(val1, val2);
		}

		[[NODISCARD]]
		constexpr long long sub_int64(long long val1, long long val2)
		{
			return _sub_impl<long long>(val1, val2);
		}

		[[NODISCARD]]
		constexpr unsigned long long sub_int64(unsigned long long val1, unsigned long long val2)
		{
			return _sub_impl<unsigned long long>(val1, val2);
		}

		//------------------------------          ------------------------------//
		//------------------------------ MULTIPLY ------------------------------//
		//------------------------------          ------------------------------//
	
		template <typename baseTy, typename upTy> [[NODISCARD]]
		constexpr baseTy _mul_impl(baseTy val1, baseTy val2)
		{
			upTy res = (upTy)val1 * val2;
			if ( (baseTy) (res >> (sizeof(baseTy) * 8) ) )
			{
				throw std::overflow_error((std::string) typeid(baseTy).name() + " multiplication overflow");
			}
			return (baseTy)res;
		}

		[[NODISCARD]]
		constexpr char mul_int8(char val1, char val2)
		{
			return _mul_impl<char, short>(val1, val2);
		}

		[[NODISCARD]]
		constexpr char mul_uint8(unsigned char val1, unsigned char val2)
		{
			return _mul_impl<unsigned char, unsigned short>(val1, val2);
		}

		[[NODISCARD]]
		constexpr short mul_int16(short val1, short val2)
		{
			return _mul_impl<short, int>(val1, val2);
		}

		[[NODISCARD]]
		constexpr short mul_uint16(unsigned short val1, unsigned short val2)
		{
			return _mul_impl<unsigned short, unsigned int>(val1, val2);
		}

		[[NODISCARD]]
		constexpr int mul_int32(int val1, int val2)
		{
			return _mul_impl<int, long long>(val1, val2);
		}

		[[NODISCARD]]
		constexpr int mul_uint32(unsigned int val1, unsigned int val2)
		{
			return _mul_impl<unsigned int, unsigned long long>(val1, val2);
		}

	} // namespace SafeMath

} // namespace nw