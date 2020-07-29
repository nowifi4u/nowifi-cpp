#pragma once

#include <nowifi/compiler/class.hpp>
#include <nowifi/util/error.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace nw {

	template <typename charTy>
	class basic_Writer {

	public:

		using string_type = std::basic_string<charTy>;

		using ostream_type = std::basic_ostream<charTy>;

		using stringstream_type = std::basic_stringstream<charTy>;

		using Error_type = Error<std::string>;

		using Writer_type = basic_Writer<charTy>;

	private:

		ostream_type& os;
		Error_type err;

	public:

		//-------------------- CONSTRUCTOR --------------------//

		basic_Writer(ostream_type& os, const Error_type& err)
			: os(os), err(err) { }

		basic_Writer(ostream_type& os)
			: Writer_type(os, global::Error_Throw<std::string>) { }

		//-------------------- write --------------------//

		//STATIC
		template <class Ty>
		static ostream_type& write(const Ty data, ostream_type& os, const Error_type& err = global::Error_Throw<std::string>)
		{
			os << data;
			if (os.bad()) err.execute("write");
			return os;
		}

		template <class Ty>
		Writer_type& write(const Ty data)
		{
			Writer_type::write<Ty>(data, os, err);
			return THIS;
		}

		//-------------------- writeBool --------------------//

		//STATIC
		static ostream_type& writeBool(bool data, ostream_type& os, const Error_type& err)
		{
			return Writer_type::write((data ? "true" : "false"), os, err);
		}

		Writer_type& writeBool(bool data)
		{
			Writer_type::writeBool(data, os, err);
			return THIS;
		}

		//-------------------- writeln empty --------------------//

		//STATIC
		static ostream_type& writeln(ostream_type& os, const Error_type& err)
		{
			return Writer_type::write('\n', os, err);
		}

		Writer_type& writeln()
		{
			Writer_type::writeln(os, err);
			return THIS;
		}

		//-------------------- tabulate --------------------//

		//STATIC
		static ostream_type& tabulate(ostream_type& os, const Error_type& err)
		{
			return Writer_type::write('\t', os, err);
		}

		Writer_type& tabulate()
		{
			Writer_type::tabulate(os, err);
			return THIS;
		}

		//-------------------- endline --------------------//

		//STATIC
		static ostream_type& endline(ostream_type& os, const Error_type& err)
		{
			os << std::endl;
			if (os.bad()) err.execute("write");
			return os;
		}

		Writer_type& endline()
		{
			Writer_type::endline(os, err);
			return THIS;
		}

		//-------------------- writeln --------------------//

		//STATIC
		template <class Ty>
		static ostream_type& writeln(const Ty data, ostream_type& os, const Error_type& err = global::Error_Throw<std::string>)
		{
			Writer_type::write(data, os, err);
			Writer_type::writeln(os, err);
			return os;
		}

		template <class Ty>
		Writer_type& writeln(const Ty data)
		{
			Writer_type::writeln(data, os, err);
			return THIS;
		}

		//-------------------- operator<< --------------------//

		template <class Ty>
		friend static Writer_type& operator<<(Writer_type& writer, Ty& data)
		{
			return writer.write<Ty>(data);
		}

		//-------------------- stl_writeArray --------------------//

		//STATIC
		template <class _InIt>
		static ostream_type& stl_writeArray(const _InIt _First, const _InIt _Last, const string_type& itemDelimiter, ostream_type& os, const Error_type& err = global::Error_Throw<std::string>)
		{
			auto _UFirst = std::_Get_unwrapped(_First);
			const auto _ULast = std::_Get_unwrapped(_Last);
			if (_UFirst != _ULast) {
				for (; _UFirst + 1 != _ULast; ++_UFirst) {
					Writer_type::write(*_UFirst, os, err);
					Writer_type::write<string_type>(itemDelimiter, os, err);
				}
				Writer_type::write(*(_ULast - 1), os, err);
			}
			return os;
		}

		template <class _InIt>
		Writer_type& stl_writeArray(const _InIt _First, const _InIt _Last, const string_type& itemDelimiter)
		{
			Writer_type::stl_writeArray(_First, _Last, itemDelimiter, os, err);
			return THIS;
		}

		//-------------------- writeArray --------------------//

		//STATIC
		template <class Ty>
		static ostream_type& writeArray(const Ty* arr, size_t size1, const string_type& itemDelimiter, ostream_type& os, const Error_type& err = global::Error_Throw<std::string>)
		{
			return Writer_type::stl_writeArray(arr, arr + size1, itemDelimiter, os, err);
		}

		template <class Ty>
		Writer_type& writeArray(const Ty* arr, size_t size1, const string_type& itemDelimiter)
		{
			return this->stl_writeArray(arr, arr + size1, itemDelimiter);
		}

		//-------------------- writeArray2D --------------------//

		//STATIC
		template <class Ty>
		static ostream_type& writeArray2D(Ty** arr, size_t size1, size_t size2, const string_type& itemDelimiter, const string_type& rowDelimiter, ostream_type& os, const Error_type& err = global::Error_Throw<std::string>)
		{
			const size_t lastIdx1 = size1 - 1;
			for (size_t idx1 = 0; idx1 < lastIdx1; idx1++)
			{
				Writer_type::writeArray<Ty>(arr[idx1], size2, itemDelimiter, os, err);
				Writer_type::write(rowDelimiter, os, err);
			}
			Writer_type::writeArray<Ty>(arr[lastIdx1], size2, itemDelimiter, os, err);
			return os;
		}

		template <class Ty>
		Writer_type& writeArray2D(Ty** arr, size_t size1, size_t size2, const string_type& itemDelimiter, const string_type& rowDelimiter)
		{
			Writer_type::writeArray2D<Ty>(arr, size1, size2, itemDelimiter, rowDelimiter, os, err);
			return THIS;
		}

	}; // class basic_Writer

	using Writer = basic_Writer<char>;
	using WWriter = basic_Writer<wchar_t>;

	namespace global {

		extern Writer Writer_Console = Writer(std::cout);
		extern WWriter WWriter_Console = WWriter(std::wcout);

	} // namespace global

	//-------------------- writeBinary --------------------//

	//STATIC
	template <class Ty>
	static std::ostream& Writer_writeBinary(const Ty& value, std::ostream& os, const Writer::Error_type& err = global::Error_Throw<std::string>)
	{
		os.write(reinterpret_cast<const char*>(&value), sizeof(Ty));
		if (os.bad()) err.execute("writeBinary");
		return os;
	}

} // namespace nw