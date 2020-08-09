#pragma once

#include <nowifi/compiler/class.hpp>
#include <nowifi/util/error.hpp>
#include <nowifi/string/former.hpp>
#include <nowifi/string/from_string.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <limits>

namespace nw {

	template <typename charTy>
	class basic_Scanner {

	public:

		using char_type = charTy;
		using c_string_type = const char_type*;

		using string_type = std::basic_string<charTy>;

		using istream_type = std::basic_istream<charTy>;

		using Error_type = Error<std::string>;

		using from_string_type = basic_from_string<charTy>;

	protected:

		using Scanner_type = basic_Scanner<charTy>;

		istream_type& in;
		Error_type err;

	public:

		//-------------------- GETTER --------------------//

		istream_type& getStream()
		{
			return in;
		}

		//-------------------- CONSTRUCTOR --------------------//

		basic_Scanner(istream_type& in, const Error_type& err) noexcept
			: in(in), err(err) { }

		basic_Scanner(istream_type& in)
			: Scanner_type(in, global::Error_Throw<std::string>) { }

		//-------------------- clear --------------------//

		//STATIC
		static istream_type& _clear(istream_type& in)
		{
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return in;
		}

		Scanner_type& clear()
		{
			Scanner_type::_clear(in);
			return THIS;
		}

		//-------------------- peek --------------------//

		//STATIC
		_NODISCARD static int _peek(istream_type& in)
		{
			return in.peek();
		}

		_NODISCARD int peek()
		{
			return Scanner_type::_peek(in);
		}

		//-------------------- dump --------------------//

		//STATIC
		static string_type _dump(istream_type& in)
		{
			std::basic_ostringstream<charTy> iss;
			iss << in.rdbuf();
			return iss.str();
		}

		string_type dump()
		{
			return Scanner_type::_dump(in);
		}

		//-------------------- isNext char --------------------//

		//STATIC
		_NODISCARD static bool _isNext(char ch, istream_type& in)
		{
			return Scanner_type::_peek(in) == ch;
		}

		_NODISCARD bool isNext(char ch)
		{
			return Scanner_type::_isNext(ch, in);
		}

		//-------------------- ifNextSkip char --------------------//

		//STATIC
		static bool _ifNextSkip(char ch, istream_type& in)
		{
			if (Scanner_type::_isNext(ch, in))
			{
				in.ignore();
				return true;
			}
			return false;
		}

		bool ifNextSkip(char ch)
		{
			return Scanner_type::_ifNextSkip(ch, in);
		}

		//-------------------- nextWord --------------------//

		//STATIC
		static string_type _nextWord(istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			string_type toread;
			if (!(in >> toread)) err.execute("read");
			return toread;
		}

		string_type nextWord()
		{
			return Scanner_type::_nextWord(in, err);
		}

		//-------------------- nextLine --------------------/

		//STATIC
		static string_type _nextLine(istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			string_type toread;
			if (!std::getline<charTy>(in, toread)) err.execute("getline");
			return toread;
		}

		string_type nextLine()
		{
			return Scanner_type::_nextLine(in, err);
		}

		//-------------------- nextSentence --------------------//

		//STATIC
		static string_type _nextSentence(char end, istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			string_type toread;
			if (!std::getline<charTy>(in, toread, end)) err.execute("getline");
			return toread;
		}

		string_type nextSentence(char end)
		{
			return Scanner_type::_nextSentence(end, in, err);
		}

		//-------------------- nextChecked --------------------//

		//STATIC
		template <class Ty>
		static Ty _nextChecked(istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			Ty var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::tryto(str, var)) err.execute(stringMaker("nextChecked:" << typeid(Ty).name()));
			return var;
		}

		template <class Ty>
		Ty nextChecked()
		{
			return Scanner_type::_nextChecked<Ty>(in, err);
		}

		//---------------------------------------------------------------//
		//---------------------------------------------------------------//
		//-------------------- nextChecked PRIMITIVE --------------------//

		//-------------------- short --------------------//

		//STATIC
		static short _nextChecked_short(istream_type& in, int base = 10, const Error_type& err = global::Error_Throw<std::string>)
		{
			short var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoShort(str, var, base)) err.execute("nextChecked:short");
			return var;
		}

		short nextChecked_short(int base = 10)
		{
			return Scanner_type::_nextChecked_short(in, base, err);
		}

		//-------------------- int --------------------//

		//STATIC
		static int _nextChecked_int(istream_type& in, int base = 10, const Error_type& err = global::Error_Throw<std::string>)
		{
			int var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoInt(str, var, base)) err.execute("nextChecked:int");
			return var;
		}

		int nextChecked_int(int base = 10)
		{
			return Scanner_type::_nextChecked_int(in, base, err);
		}

		//-------------------- long --------------------//

		//STATIC
		static long _nextChecked_long(istream_type& in, int base = 10, const Error_type& err = global::Error_Throw<std::string>)
		{
			long var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoLong(str, var, base)) err.execute("nextChecked:int");
			return var;
		}

		long nextChecked_long(int base = 10)
		{
			return Scanner_type::_nextChecked_long(in, base, err);
		}

		//-------------------- long long --------------------//

		//STATIC
		static long long _nextChecked_llong(istream_type& in, int base = 10, const Error_type& err = global::Error_Throw<std::string>)
		{
			long long var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoLLong(str, var, base)) err.execute("nextChecked:int");
			return var;
		}

		long long nextChecked_llong(int base = 10)
		{
			return Scanner_type::_nextChecked_llong(in, base, err);
		}

		//-------------------- unsigned short --------------------//

		//STATIC
		static unsigned short _nextChecked_ushort(istream_type& in, int base = 10, const Error_type& err = global::Error_Throw<std::string>)
		{
			unsigned short var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoUShort(str, var, base)) err.execute("nextChecked:short");
			return var;
		}

		unsigned short nextChecked_ushort(int base = 10)
		{
			return Scanner_type::_nextChecked_ushort(in, base, err);
		}

		//-------------------- unsigned int --------------------//

		//STATIC
		static unsigned int _nextChecked_uint(istream_type& in, int base = 10, const Error_type& err = global::Error_Throw<std::string>)
		{
			unsigned int var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoUInt(str, var, base)) err.execute("nextChecked:int");
			return var;
		}

		unsigned int nextChecked_uint(int base = 10)
		{
			return Scanner_type::_nextChecked_uint(in, base, err);
		}

		//-------------------- unsigned long --------------------//

		//STATIC
		static unsigned long _nextChecked_ulong(istream_type& in, int base = 10, const Error_type& err = global::Error_Throw<std::string>)
		{
			unsigned long var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoULong(str, var, base)) err.execute("nextChecked:int");
			return var;
		}

		unsigned long nextChecked_ulong(int base = 10)
		{
			return Scanner_type::_nextChecked_ulong(in, base, err);
		}

		//-------------------- unsigned long long --------------------//

		//STATIC
		static unsigned long long _nextChecked_ullong(istream_type& in, int base = 10, const Error_type& err = global::Error_Throw<std::string>)
		{
			unsigned long long var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoULLong(str, var, base)) err.execute("nextChecked:int");
			return var;
		}

		unsigned long long nextChecked_ullong(int base = 10)
		{
			return Scanner_type::_nextChecked_ullong(in, base, err);
		}

		//-------------------- float --------------------//

		//STATIC
		static float _nextChecked_float(istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			float var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoFloat(str, var)) err.execute("nextChecked:short");
			return var;
		}

		float nextChecked_float()
		{
			return Scanner_type::_nextChecked_float(in, err);
		}

		//-------------------- double --------------------//

		//STATIC
		static double _nextChecked_double(istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			double var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoDouble(str, var)) err.execute("nextChecked:short");
			return var;
		}

		double nextChecked_double()
		{
			return Scanner_type::_nextChecked_double(in, err);
		}

		//-------------------- long double --------------------//

		//STATIC
		static long double _nextChecked_ldouble(istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			long double var;
			string_type str = Scanner_type::_nextWord(in, err);
			if (!from_string_type::trytoLDouble(str, var)) err.execute("nextChecked:short");
			return var;
		}

		long double nextChecked_ldouble()
		{
			return Scanner_type::_nextChecked_ldouble(in, err);
		}

		//-------------------- nextChecked PRIMITIVE --------------------//
		//---------------------------------------------------------------//
		//---------------------------------------------------------------//

		//-------------------- next --------------------//

		//STATIC
		template <class Ty>
		static Ty _next(istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			Ty toread;
			in >> toread;
			while (in.fail())
			{
				err.execute(stringMaker("type:" << typeid(Ty).name()));
				_clear(in);
				in >> toread;
			}
			return toread;
		}

		template <class Ty>
		Ty next()
		{
			return Scanner_type::_next<Ty>(in, err);
		}

		//-------------------- nextParam --------------------//

		//STATIC
		template <class Ty>
		static istream_type& _nextParam(istream_type& in, const Error_type& err, Ty& first)
		{
			in >> first;
			if (in.fail()) err.execute(stringMaker("type:" << typeid(Ty).name()));
			return in;
		}

		//STATIC
		template <class Ty, class... Args>
		static istream_type& _nextParam(istream_type& in, const Error_type& err, Ty& first, Args&... args)
		{
			Scanner_type::_nextParam(in, err, first);
			return Scanner_type::_nextParam(in, err, args...);
		}

		template <class Ty, class... Args>
		Scanner_type& nextParam(Ty& first, Args&... args)
		{
			Scanner_type::_nextParam(in, err, first, args...);
			return THIS;
		}

		//-------------------- operator>> --------------------//

		template <class Ty>
		friend Scanner_type& operator>>(Scanner_type& scanner, Ty& val)
		{
			scanner.nextParam(val);
			return scanner;
		}

		//-------------------- nextRanged --------------------//

		//STATIC
		template <class Ty>
		static Ty _nextRanged(const Ty min, const Ty max, istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			Ty toread;
			toread = Scanner_type::_next<Ty>(in, err);
			while (toread < min || toread > max)
			{
				err.execute(stringMaker("range:" << toread << ":" << min << ":" << max));
				Scanner_type::_clear(in);
				toread = Scanner_type::_next<Ty>(in, err);
			}
			return toread;
		}

		template <class Ty>
		Ty nextRanged(const Ty min, const Ty max)
		{
			return Scanner_type::_nextRanged<Ty>(min, max, in, err);
		}

		//-------------------- next_separated --------------------//

		//STATIC
		template <class Ty>
		static Ty _next_separated(charTy sep, istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			Ty result = Scanner_type::_next<int>(in, err);
			Scanner_type::_ifNextSkip(sep, in);
			return result;
		}

		template <class Ty>
		Ty next_separated(charTy sep)
		{
			return Scanner_type::_next_separated<Ty>(sep, in, err);
		}

		//-------------------- nextParam_separated --------------------//

		//STATIC
		template <class Ty>
		static istream_type& _nextParam_separated(charTy sep, istream_type& in, const Error_type& err, Ty& first)
		{
			Scanner_type::_nextOaram(in, err, first);
			return Scanner_type::ifNextSkip(sep, in);
		}

		//STATIC
		template <class Ty, class... Args>
		static istream_type& _nextParam_separated(charTy sep, istream_type& in, const Error_type& err, Ty& first, Args&... args)
		{
			Scanner_type::_nextParam_separated(sep, in, err, first);
			return Scanner_type::_nextParam_separated(sep, in, err, args...);
		}

		template <class Ty, class... Args>
		static Scanner_type& nextParam_separated(charTy sep, Ty& first, Args&... args)
		{
			Scanner_type::_nextParam_separated(sep, in, err, first, args...);
			return THIS;
		}

		//-------------------- stl_readArray --------------------//

		//STATIC
		template <class Ty, class _Iter>
		static istream_type& _stl_readArray(_Iter _First, _Iter _Last, istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			std::generate(_First, _Last, [&in, &err]()
			{
				return Scanner_type::_next<Ty>(in, err);
			});
			return in;
		}

		template <class Ty, class _Iter>
		Scanner_type& stl_readArray(_Iter _First, _Iter _Last)
		{
			Scanner_type::_stl_readArray<Ty, _Iter>(_First, _Last, in, err);
			return THIS;
		}

		//-------------------- readArray --------------------//

		//STATIC
		template <class Ty>
		static istream_type& _readArray(Ty* arr, size_t size1, istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			return Scanner_type::_stl_readArray<Ty>(arr, arr + size1, in, err);
		}

		template <class Ty>
		Scanner_type& readArray(Ty* arr, size_t size1)
		{
			Scanner_type::_readArray<Ty>(arr, size1, in, err);
			return THIS;
		}

		//-------------------- readNewVector --------------------//

		//STATIC
		template <class Ty>
		static std::vector<Ty> _readNewVector(size_t size1, istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			std::vector<Ty> arr(size1);
			Scanner_type::_stl_readArray<Ty>(arr.begin(), arr.end(), in, err);
			return arr;
		}

		template <class Ty>
		std::vector<Ty> readNewVector(size_t size1)
		{
			return Scanner_type::_readNewVector<Ty>(size1, in, err);
		}

		//-------------------- stl_readArray_separated --------------------//

		//STATIC
		template <class Ty, class _Iter>
		static istream_type& _stl_readArray_separated(_Iter _First, _Iter _Last, charTy sep, istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			std::generate(_First, _Last, [sep, &in, &err]()
			{
				return Scanner_type::_next_separated<Ty>(sep, in, err);
			});
			return in;
		}

		template <class Ty, class _Iter>
		Scanner_type& stl_readArray_separated(_Iter _First, _Iter _Last, charTy sep)
		{
			Scanner_type::_stl_readArray_separated<Ty>(_First, _Last, sep, in, err);
			return THIS;
		}

		//-------------------- readArray_separated --------------------//

		//STATIC
		template <class Ty>
		static istream_type& _readArray_separated(Ty* arr, size_t size1, charTy sep, istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			return Scanner_type::_stl_readArray_separated<Ty>(arr, arr + size1, sep, in, err);
		}

		template <class Ty>
		Scanner_type& readArray_separated(Ty* arr, size_t size1, charTy sep)
		{
			Scanner_type::_readArray_separated<Ty>(arr, size1, sep, in, err);
			return THIS;
		}

		//-------------------- readNewVector_separated --------------------//

		//STATIC
		template <class Ty>
		static std::vector<Ty> _readNewVector_separated(size_t size1, charTy sep, istream_type& in, const Error_type& err = global::Error_Throw<std::string>)
		{
			std::vector<Ty> arr(size1);
			Scanner_type::_stl_readArray_separated<Ty>(arr.begin(), arr.end(), sep, in, err);
			return arr;
		}

		template <class Ty>
		std::vector<Ty> readNewVector_separated(size_t size1, charTy sep)
		{
			return Scanner_type::_readNewVector_separated<Ty>(size1, sep, in, err);
		}

	}; // class basic_Scanner

	using Scanner = basic_Scanner<char>;
	using WScanner = basic_Scanner<wchar_t>;

	namespace global {

		extern Scanner Scanner_Console = Scanner(std::cin);
		extern WScanner WScanner_Sconsole = WScanner(std::wcin);

	} // namespace global

	//-------------------- readBinary --------------------//

	//STATIC
	template <class Ty>
	static std::istream& Scanner_readBinary(const Ty& val, std::istream& in, const Scanner::Error_type& err = global::Error_Throw<std::string>)
	{
		in.read(reinterpret_cast<const char*>(&val), sizeof(Ty));
		return in;
	}

	//STATIC
	template <class Ty>
	static Ty Scanner_readBinary_new(std::istream& in, const Scanner::Error_type& err = global::Error_Throw<std::string>)
	{
		Ty val;
		Scanner_readBinary(val, in, err);
		return val;
	}

} // namespace nw