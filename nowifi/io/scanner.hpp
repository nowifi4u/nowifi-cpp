#pragma once

#include <nowifi/compiler/class.hpp>
#include <nowifi/util/error.hpp>
#include <nowifi/string/former.hpp>

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

		using string_type = std::basic_string<charTy>;

		using istream_type = std::basic_istream<charTy>;

		using Error_type = Error<std::string>;

		using Scanner_type = basic_Scanner<charTy>;

	private:

		istream_type& in;
		Error_type err;

	public:

		//-------------------- GETTER --------------------//

		istream_type& getStream() {
			return in;
		}

		//-------------------- CONSTRUCTOR --------------------//

		basic_Scanner(istream_type& in, const Error_type& err) noexcept
			: in(in), err(err) {
		}

		basic_Scanner(istream_type& in)
			: Scanner_type(in, global::Error_Throw<std::string>) {
		}

		//-------------------- clear --------------------//

		//STATIC
		static istream_type& clear(istream_type& in) {
			in.clear();
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return in;
		}

		Scanner_type& clear() {
			Scanner_type::clear(in);
			return THIS;
		}

		//-------------------- peek --------------------//

		//STATIC
		static int peek(istream_type& in) {
			return in.peek();
		}

		int peek() {
			return Scanner_type::peek(in);
		}

		//-------------------- dump --------------------//

		//STATIC
		static string_type dump(istream_type& in) {
			std::basic_ostringstream<charTy> iss;
			iss << in.rdbuf();
			return iss.str();
		}

		string_type dump() {
			return Scanner_type::dump(in);
		}

		//-------------------- isNext char --------------------//

		//STATIC
		static bool isNext(char ch, istream_type& in) {
			return Scanner_type::peek(in) == ch;
		}

		bool isNext(char ch) {
			return Scanner_type::isNext(ch, in);
		}

		//-------------------- isNext string --------------------//

		//STATIC
		static bool isNextAny(const string_type& str, istream_type& in) {
			return str.find(Scanner_type::peek(in)) != string_type::npos;
		}

		bool isNextAny(const string_type& str) {
			return Scanner_type::isNextAny(str, in);
		}

		//-------------------- ifNextSkip char --------------------//

		//STATIC
		static bool ifNextSkip(char ch, istream_type& in) {
			if (Scanner_type::isNext(ch, in)) {
				in.ignore();
				return true;
			}
			return false;
		}

		bool ifNextSkip(char ch) {
			return Scanner_type::ifNextSkip(ch, in);
		}

		//-------------------- ifNextSkip string --------------------//

		//STATIC
		static bool ifNextAnySkip(const string_type& str, istream_type& in) {
			if (Scanner_type::isNextAny(str, in)) {
				in.ignore();
				return true;
			}
			return false;
		}

		bool ifNextAnySkip(const string_type& str) {
			return Scanner_type::ifNextAnySkip(str, in);
		}

		//-------------------- nextWord --------------------//

		//STATIC
		static string_type nextWord(istream_type& in, const Error_type& err) {
			string_type toread;
			if (!(in >> toread)) err.execute("read");
			return toread;
		}

		//STATIC
		static string_type nextWord(istream_type& in) {
			return Scanner_type(in).nextWord();
		}

		string_type nextWord() {
			return Scanner_type::nextWord(in, err);
		}

		//-------------------- nextLine --------------------/

		//STATIC
		static string_type nextLine(istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			string_type toread;
			if (!std::getline<charTy>(in, toread)) err.execute("getline");
			return toread;
		}

		string_type nextLine() {
			return Scanner_type::nextLine(in, err);
		}

		//-------------------- nextSentence --------------------//

		//STATIC
		static string_type nextSentence(char end, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			string_type toread;
			if (!std::getline<charTy>(in, toread, end)) err.execute("getline");
			return toread;
		}

		string_type nextSentence(char end) {
			return Scanner_type::nextSentence(end, in, err);
		}

		//-------------------- nextInt --------------------//

		//STATIC
		static int nextInt(istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			while (true) {
				string_type buffer = Scanner_type::nextWord(in, err);
				try {
					return std::stoi(buffer);
				}
				catch (...) {
					err.execute("type:int");
				}
			}
		}

		int nextInt() {
			return Scanner_type::nextInt(in, err);
		}

		//-------------------- nextInt based --------------------//

		//STATIC
		static int nextInt(int base, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			while (true) {
				string_type buffer = Scanner_type::nextWord(in, err);
				try {
					return std::stoi(buffer, 0, base);
				}
				catch (...) {
					err.execute("type:int");
				}
			}
		}

		int nextInt(int base) {
			return Scanner_type::nextInt(base, in, err);
		}

		//-------------------- nextLong --------------------//

		//STATIC
		static int nextLong(istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			while (true) {
				string_type buffer = Scanner_type::nextWord(in, err);
				try {
					return std::stol(buffer);
				}
				catch (...) {
					err.execute("type:int");
				}
			}
		}

		int nextLong() {
			return Scanner_type::nextLong(in, err);
		}

		//-------------------- nextLong based --------------------//

		//STATIC
		static int nextLong(int base, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			while (true) {
				string_type buffer = Scanner_type::nextWord(in, err);
				try {
					return std::stol(buffer, 0, base);
				}
				catch (...) {
					err.execute("type:int");
				}
			}
		}

		int nextLong(int base) {
			return Scanner_type::nextLong(base, in, err);
		}

		//-------------------- nextFloat --------------------//

		//STATIC
		static float nextFloat(istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			while (true) {
				string_type buffer = Scanner_type::nextWord(in, err);
				try {
					return std::stof(buffer);
				}
				catch (...) {
					err.execute("type:int");
				}
			}
		}

		float nextFloat() {
			return Scanner_type::nextFloat(in, err);
		}

		//-------------------- nextDouble --------------------//

		//STATIC
		static double nextDouble(istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			while (true) {
				string_type buffer = Scanner_type::nextWord(in, err);
				try {
					return std::stod(buffer);
				}
				catch (...) {
					err.execute("type:int");
				}
			}
		}

		double nextDouble() {
			return Scanner_type::nextDouble(in, err);
		}

		//-------------------- next --------------------//

		//STATIC
		template <class Ty>
		static Ty next(istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			Ty toread;
			in >> toread;
			while (in.fail()) {
				err.execute(stringMaker("type:" << typeid(Ty).name()));
				clear(in);
				in >> toread;
			}
			return toread;
		}

		template <class Ty>
		Ty next() {
			return Scanner_type::next<Ty>(in, err);
		}

		//-------------------- operator>> --------------------//

		template <class Ty>
		friend Scanner_type& operator>>(Scanner_type& scanner, Ty& value) {
			value = scanner.next<Ty>();
			return scanner;
		}

		//-------------------- nextRanged --------------------//

		//STATIC
		template <class Ty>
		static Ty nextRanged(const Ty min, const Ty max, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			Ty toread;
			toread = Scanner_type::next<Ty>(in, err);
			while (toread < min || toread > max) {
				err.execute(stringMaker("range:" << toread << ":" << min << ":" << max));
				Scanner_type::clear(in);
				toread = Scanner_type::next<Ty>(in, err);
			}
			return toread;
		}

		template <class Ty>
		Ty nextRanged(const Ty min, const Ty max) {
			return Scanner_type::nextRanged<Ty>(min, max, in, err);
		}

		//-------------------- nextSeparated --------------------//

		//STATIC
		template <class Ty>
		static Ty nextSeparated(charTy sep, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			Ty result = Scanner_type::next<int>(in, err);
			Scanner_type::ifNextSkip(sep, in);
			return result;
		}

		template <class Ty>
		Ty nextSeparated(charTy sep) {
			return Scanner_type::nextSeparated<Ty>(sep, in, err);
		}

		//-------------------- stl_readArray --------------------//

		//STATIC
		template <class Ty, class _InIt>
		static istream_type& stl_readArray(_InIt _First, _InIt _Last, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			std::generate(_First, _Last, [&in, &err]() {
				return Scanner_type::next<Ty>(in, err);
			});
			return in;
		}

		template <class Ty, class _InIt>
		Scanner_type& stl_readArray(_InIt _First, _InIt _Last) {
			Scanner_type::stl_readArray<Ty, _InIt>(_First, _Last, in, err);
			return THIS;
		}

		//-------------------- readArray --------------------//

		//STATIC
		template <class Ty>
		static istream_type& readArray(Ty* arr, size_t size1, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			return Scanner_type::stl_readArray<Ty>(arr, arr + size1, in, err);
		}

		template <class Ty>
		Scanner_type& readArray(Ty* arr, size_t size1) {
			Scanner_type::readArray<Ty>(arr, size1, in, err);
			return THIS;
		}

		//-------------------- readNewVector --------------------//

		//STATIC
		template <class Ty>
		static std::vector<Ty> readNewVector(size_t size1, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			std::vector<Ty> arr(size1);
			Scanner_type::stl_readArray<Ty>(arr.begin(), arr.end(), in, err);
			return arr;
		}

		template <class Ty>
		std::vector<Ty> readNewVector(size_t size1) {
			return Scanner_type::readNewVector<Ty>(size1, in, err);
		}

		//-------------------- stl_readArraySeparated --------------------//

		//STATIC
		template <class Ty, class _InIt>
		static istream_type& stl_readArraySeparated(_InIt _First, _InIt _Last, charTy sep, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			std::generate(_First, _Last, [sep, &in, &err]() {
				return Scanner_type::nextSeparated<Ty>(sep, in, err);
			});
			return in;
		}

		template <class Ty, class _InIt>
		Scanner_type& stl_readArraySeparated(_InIt _First, _InIt _Last, charTy sep) {
			Scanner_type::stl_readArraySeparated<Ty>(_First, _Last, sep, in, err);
			return THIS;
		}

		//-------------------- readArraySeparated --------------------//

		//STATIC
		template <class Ty>
		static istream_type& readArraySeparated(Ty* arr, size_t size1, charTy sep, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			return Scanner_type::stl_readArraySeparated<Ty>(arr, arr + size1, sep, in, err);
		}

		template <class Ty>
		Scanner_type& readArraySeparated(Ty* arr, size_t size1, charTy sep) {
			Scanner_type::readArraySeparated<Ty>(arr, size1, sep, in, err);
			return THIS;
		}

		//-------------------- readNewVectorSeparated --------------------//

		//STATIC
		template <class Ty>
		static std::vector<Ty> readNewVectorSeparated(size_t size1, charTy sep, istream_type& in, const Error_type& err = global::Error_Throw<std::string>) {
			std::vector<Ty> arr(size1);
			Scanner_type::stl_readArraySeparated<Ty>(arr.begin(), arr.end(), sep, in, err);
			return arr;
		}

		template <class Ty>
		std::vector<Ty> readNewVectorSeparated(size_t size1, charTy sep) {
			return Scanner_type::readNewVectorSeparated<Ty>(size1, sep, in, err);
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
	static std::istream& Scanner_readBinary(const Ty& value, std::istream& in, const Scanner::Error_type& err = global::Error_Throw<std::string>)
	{
		in.read(reinterpret_cast<const char*>(&value), sizeof(Ty));
		return in;
	}

	//STATIC
	template <class Ty>
	static Ty Scanner_readBinary_new(std::istream& in, const Scanner::Error_type& err = global::Error_Throw<std::string>)
	{
		Ty value;
		Scanner_readBinary(value, in, err);
		return value;
	}

} // namespace nw