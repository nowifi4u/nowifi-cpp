#pragma once

#include <nowifi/io/writer.hpp>
#include <iomanip>

namespace nw {

	template <typename charTy>
	class basic_to_string
	{
	public:
		NW_CLASS_MAKE_STATIC(basic_to_string, <charTy>);

		using char_type = charTy;
		using c_string_type = char_type*;

		using string_type = std::basic_string<charTy>;

		using ostringstream_type = std::basic_ostringstream<charTy>;

		using Writer_type = basic_Writer<charTy>;

		template <class _Iter>
		_NODISCARD static inline string_type stl_array(const _Iter _First, const _Iter _Last, const string_type& itemDelimiter)
		{
			ostringstream_type os;
			Writer_type::_stl_writeArray(_First, _Last, itemDelimiter, os);
			return os.str();
		}

		template <class Ty>
		_NODISCARD static inline string_type array(const Ty* arr, size_t size1, const string_type& itemDelimiter)
		{
			ostringstream_type os;
			Writer_type::_writeArray(arr, size1, itemDelimiter, os);
			return os.str();
		}

		template <class Ty>
		_NODISCARD static inline string_type array2D(Ty** arr, size_t size1, size_t size2, const string_type& itemDelimiter, const string_type& rowDelimiter)
		{
			ostringstream_type os;
			Writer_type::_writeArray2D(arr, size1, size2, itemDelimiter, rowDelimiter, os);
			return os.str();
		}

		template <class Ty, class... Args>
		_NODISCARD static inline string_type raw(ostringstream_type& os, const Ty& value, const Args&... args)
		{
			os << value;
			(os << ... << args);
			return os.str();
		}

		template <class Ty, class... Args>
		_NODISCARD static inline string_type pure(const Ty& value, const Args&... args)
		{
			ostringstream_type os;
			return raw(os, value, args...);
		}

		//-------------------- INTEGER MODIFIERS --------------------//

		template <class Ty, class... Args>
		_NODISCARD static inline string_type dec(const Ty& value, const Args&... args)
		{
			ostringstream_type os;
			os << std::dec;
			return raw(os, value, args...);
		}

		template <class Ty, class... Args>
		_NODISCARD static inline string_type hex(const Ty& value, const Args&... args)
		{
			ostringstream_type os;
			os << std::hex;
			return raw(os, value, args...);
		}

		template <class Ty, class... Args>
		_NODISCARD static inline string_type oct(const Ty& value, const Args&... args)
		{
			ostringstream_type os;
			os << std::oct;
			return raw(os, value, args...);
		}

		template <class Ty, class... Args>
		_NODISCARD static inline string_type setbase(int n, const Ty& value, const Args&... args)
		{
			ostringstream_type os;
			os << std::setbase(n);
			return raw(os, value, args...);
		}

		//-------------------- FLOATING-POINT MODIFIERS --------------------//

		template <class Ty, class... Args>
		_NODISCARD static inline string_type fixed(const Ty& value, const Args&... args)
		{
			ostringstream_type os;
			os << std::fixed;
			return raw(os, value, args...);
		}

		template <class Ty, class... Args>
		_NODISCARD static inline string_type scientific(const Ty& value, const Args&... args)
		{
			ostringstream_type os;
			os << std::scientific;
			return raw(os, value, args...);
		}

		template <class Ty, class... Args>
		_NODISCARD static inline string_type hexfloat(const Ty& value, const Args&... args)
		{
			ostringstream_type os;
			os << std::hexfloat;
			return raw(os, value, args...);
		}

		template <class Ty, class... Args>
		_NODISCARD static inline string_type defaultfloat(const Ty& value, const Args&... args)
		{
			ostringstream_type os;
			os << std::defaultfloat;
			return raw(os, value, args...);
		}

		template <class Ty, class... Args>
		_NODISCARD static inline string_type setprecision(int n, const Ty& value, const Args&... args)
		{
			ostringstream_type os;
			os << std::setprecision(n);
			return raw(os, value, args...);
		}

	}; // class basic_to_string

	using to_string = basic_to_string<char>;
	using to_wstring = basic_to_string<wchar_t>;

	template <class Ty>
	_NODISCARD static inline std::string to_string_binary(const Ty& value)
	{
		return std::string(reinterpret_cast<const char*>(&value), sizeof(Ty));
	}

	template <class... Args>
	_NODISCARD static inline std::string to_string_binary(const Args&... args)
	{
		return (... + to_string_binary(args));
	}

} // namespace nw