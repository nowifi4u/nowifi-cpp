#pragma once

#include <sstream>
#include <vector>

namespace nw {

	template <typename charTy>
	class basic_StringSplitter
	{
	protected:

		std::basic_istringstream<charTy> stream;
		const char sep;

	public:

		using string_type = std::basic_string<charTy>;

		basic_StringSplitter(const string_type& str, charTy sep)
			: stream(str), sep(sep) {}

		basic_StringSplitter(const basic_StringSplitter& second, charTy sep)
			: basic_StringSplitter(second.stream.str(), sep) {}

		bool cut(string_type& token)
		{
			return std::getline<charTy>(stream, token, sep) ? true : false;
		}

		string_type cut_return()
		{
			string_type token;
			this->cut(token);
			return token;
		}

		bool eof() const
		{
			return stream.rdbuf()->in_avail() == 0;
		}

		string_type getBuffer() const
		{
			return stream.str();
		}


		static std::vector<string_type> split(const string_type& str, charTy sep)
		{
			std::vector<string_type> tokens;
			basic_StringSplitter splitter(str, sep);
			string_type token;
			while (splitter.cut(token))
			{
				tokens.push_back(token);
			}
			return tokens;
		}
	
	}; // class basic_StringSplitter

	using StringSplitter = basic_StringSplitter<char>;
	using WStringSplitter = basic_StringSplitter<wchar_t>;

} // namespace nw