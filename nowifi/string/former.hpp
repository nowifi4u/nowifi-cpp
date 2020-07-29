#pragma once

#include <iostream>

namespace nw {

	template <typename charTy>
	class basic_stringstream : public std::basic_stringstream<charTy> {
	public:
		basic_stringstream() {}

		operator const std::basic_string<charTy>() const {
			return std::basic_stringstream<charTy>::str();
		}

		template <typename Ty>
		basic_stringstream<charTy>& operator<< (Ty _val) {
			std::basic_stringstream<charTy>::operator<< (_val);
			return *this;
		}

		basic_stringstream<charTy>& operator<< (std::streambuf* _val) {
			std::basic_stringstream<charTy>::operator<< (_val);
			return *this;
		}

		basic_stringstream<charTy>& operator<< (std::ostream& (*_val)(std::ostream&)) {
			std::basic_stringstream<charTy>::operator<< (_val);
			return *this;
		}

		basic_stringstream<charTy>& operator<< (std::ios& (*_val)(std::ios&)) {
			std::basic_stringstream<charTy>::operator<< (_val);
			return *this;
		}

		basic_stringstream<charTy>& operator<< (std::ios_base& (*_val)(std::ios_base&)) {
			std::basic_stringstream<charTy>::operator<< (_val);
			return *this;
		}

		basic_stringstream<charTy>& operator<< (const charTy* _val) {
			return static_cast<basic_stringstream<charTy>&>(std::operator<< (*this, _val));
		}

		basic_stringstream<charTy>& operator<< (const std::basic_string<charTy>& _val) {
			return static_cast<basic_stringstream<charTy>&>(std::operator<< (*this, _val.c_str()));
		}
	};

	typedef basic_stringstream<char> stringstream;
	typedef basic_stringstream<wchar_t> wstringstream;
}

#define stringMaker(params) std::string(nw::stringstream() << params )
#define wstringMaker(params) std::wstring(nw::wstringstream() << params )