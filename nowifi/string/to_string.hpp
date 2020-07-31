#pragma once

#include <nowifi/io/writer.hpp>

namespace nw {

	template <typename charTy>
	class basic_to_string
	{
	public:
		MAKE_STATIC_TEMPLATE_1(basic_to_string, <charTy>);

		using string_type = std::basic_string<charTy>;

		using ostringstream_type = std::basic_ostringstream<charTy>;

		using Writer_type = basic_Writer<charTy>;

		template <class _InIt>
		static inline string_type stl_array(const _InIt _First, const _InIt _Last, const string_type& itemDelimiter)
		{
			ostringstream_type os;
			Writer_type::stl_writeArray(_First, _Last, itemDelimiter, os);
			return os.str();
		}

		template <class Ty>
		static inline string_type array(const Ty* arr, size_t size1, const string_type& itemDelimiter)
		{
			ostringstream_type os;
			Writer_type::writeArray(arr, size1, itemDelimiter, os);
			return os.str();
		}

		template <class Ty>
		static inline string_type array2D(Ty** arr, size_t size1, size_t size2, const string_type& itemDelimiter, const string_type& rowDelimiter)
		{
			ostringstream_type os;
			Writer_type::writeArray2D(arr, size1, size2, itemDelimiter, rowDelimiter, os);
			return os.str();
		}

		template <class Ty>
		static inline string_type pure(const Ty& value)
		{
			ostringstream_type os;
			os << value;
			return os.str();
		}

		template <class... Args>
		static inline string_type pure(const Args&... args)
		{
			return (... + pure(args));
		}

		template <class Ty>
		static inline string_type dec(const Ty& value)
		{
			ostringstream_type os;
			os << std::dec << value;
			return os.str();
		}

		template <class... Args>
		static inline string_type dec(const Args&... args)
		{
			return (... + dec(args));
		}

		template <class Ty>
		static inline string_type hex(const Ty& value)
		{
			ostringstream_type os;
			os << std::hex << value;
			return os.str();
		}


		template <class... Args>
		static inline string_type hex(const Args&... args)
		{
			return (... + hex(args));
		}

		template <class Ty>
		static inline string_type oct(const Ty& value)
		{
			ostringstream_type os;
			os << std::oct << value;
			return os.str();
		}

		template <class... Args>
		static inline string_type oct(const Args&... args)
		{
			return (... + oct(args));
		}

	}; // class basic_to_string

	using to_string = basic_to_string<char>;
	using to_wstring = basic_to_string<wchar_t>;

	template <class Ty>
	static inline std::string to_string_binary(const Ty& value)
	{
		return std::string(reinterpret_cast<const char*>(&value), sizeof(Ty));
	}

	template <class... Args>
	static inline std::string to_string_binary(const Args&... args)
	{
		return (... + to_string_binary(args));
	}

} // namespace nw