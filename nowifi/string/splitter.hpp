#pragma once

#include <iostream>
#include <vector>

namespace nw {

	template <typename charTy>
	class basic_StringSplitter {
	public:

		using string_type = std::basic_string<charTy>;

		std::basic_istringstream<charTy> stream;
		char sep;

		basic_StringSplitter(const string_type& str, charTy sep)
			: stream(str), sep(sep) {}

		basic_StringSplitter(const basic_StringSplitter& second, charTy sep)
			: basic_StringSplitter(second.stream.str(), sep) {}

		bool cut(string_type& token) {
			return std::getline<charTy>(stream, token, sep) ? true : false;
		}

		string_type cut_force() {
			string_type token;
			this->cut(token);
			return token;
		}

		bool eof() {
			return stream.rdbuf()->in_avail() == 0;
		}

		static std::vector<string_type> split(const string_type& str, charTy sep) {
			std::vector<string_type> tokens;
			basic_StringSplitter splitter(str, sep);
			string_type token;
			while (splitter.cut(token)) {
				tokens.push_back(token);
			}
			return tokens;
		}
	
	}; // class basic_StringSplitter

	using StringSplitter = basic_StringSplitter<char>;
	using WStringSplitter = basic_StringSplitter<wchar_t>;

} // namespace nw