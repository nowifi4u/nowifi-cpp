#pragma once

#include <nowifi/compiler/class.hpp>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace nw {

	template <typename charTy>
	class basic_from_string
	{
	public:
		CLASS_MAKE_STATIC(basic_from_string, <charTy>);

		using string_type = std::basic_string<charTy>;

		using istringstream_type = std::basic_istringstream<charTy>;
		
		template <class Ty>
		static bool _tryto(istringstream_type& iss, const string_type& str, Ty& var)
		{
			iss.str(str);
			iss >> var;
			return (!iss.fail() && iss.eof());
		}

		template <class Ty>
		static bool tryto(const string_type& str, Ty& var)
		{
			istringstream_type iss(str);
			return _to<Ty>(iss, str, var);
		}
		
		template <class Ty>
		static Ty _to(istringstream_type& iss, const string_type& str)
		{
			Ty var;
			if (!_tryto<Ty>(iss, str, var)) throw std::invalid_argument("basic_from_string: string conversion failure");
			return var;
		}

		template <class Ty>
		static Ty to(const string_type& str)
		{
			istringstream_type iss(str);
			return _to<Ty>(iss, str);
		}

		//-------------------- PRIMITIVES --------------------//

		//-------------------- short --------------------//

		static bool trytoShort(const string_type& str, short& val, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _tryto<short>(iss, str, val);
		}

		static short toShort(const string_type& str, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _to<short>(iss, str);
		}

		//-------------------- int --------------------//

		static bool trytoInt(const string_type& str, int& val, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _tryto<int>(iss, str, val);
		}

		static int toInt(const string_type& str, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _to<int>(iss, str);
		}

		//-------------------- long --------------------//

		static bool trytoLong(const string_type& str, long& val, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _tryto<long>(iss, str, val);
		}

		static long toLong(const string_type& str, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _to<long>(iss, str);
		}

		//-------------------- long long --------------------//

		static bool trytoLLong(const string_type& str, long long& val, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _tryto<long long>(iss, str, val);
		}

		static long long toLLong(const string_type& str, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _to<long long>(iss, str);
		}

		//-------------------- unsigned short --------------------//

		static bool trytoUShort(const string_type& str, unsigned short& val, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _tryto<unsigned short>(iss, str, val);
		}

		static unsigned short toUShort(const string_type& str, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _to<unsigned short>(iss, str);
		}

		//-------------------- unsigned int --------------------//

		static bool trytoUInt(const string_type& str, unsigned int& val, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _tryto<unsigned int>(iss, str, val);
		}

		static unsigned int toUInt(const string_type& str, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _to<unsigned int>(iss, str);
		}

		//-------------------- unsigned long --------------------//

		static bool trytoULong(const string_type& str, unsigned long& val, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _tryto<unsigned long>(iss, str, val);
		}

		static unsigned long toULong(const string_type& str, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _to<unsigned long>(iss, str);
		}

		//-------------------- unsigned long long --------------------//

		static bool trytoULLong(const string_type& str, unsigned long long& val, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _tryto<unsigned long long>(iss, str, val);
		}

		static unsigned long long toULLong(const string_type& str, int base = 10)
		{
			istringstream_type iss(str);
			iss >> std::setbase(base);
			return _to<unsigned long long int>(iss, str);
		}

		//-------------------- float --------------------//

		static bool trytoFloat(const string_type& str, float& val)
		{
			return tryto<float>(str, val);
		}

		static float toFloat(const string_type& str)
		{
			return to<float>(str);
		}

		//-------------------- double --------------------//

		static bool trytoDouble(const string_type& str, double& val)
		{
			return tryto<double>(str, val);
		}

		static double toDouble(const string_type& str)
		{
			return to<double>(str);
		}

		//-------------------- long double --------------------//

		static bool trytoLDouble(const string_type& str, long double& val)
		{
			return tryto<long double>(str, val);
		}

		static long double toLDouble(const string_type& str)
		{
			return to<long double>(str);
		}


	}; // class basic_from_string

	using from_string = basic_from_string<char>;
	using from_wstring = basic_from_string<wchar_t>;

} // namespace nw