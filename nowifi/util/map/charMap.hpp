#pragma once

#include <string>
#include <codecvt>
#include <cwctype>

namespace nw {

	namespace CharMap {

		//-------------------- CHAR --------------------//

		bool isalpha(char ch) {
			return std::isalpha(ch) != 0;
		}

		bool isupper(char ch) {
			return std::isupper(ch) != 0;
		}

		bool islower(char ch) {
			return std::islower(ch) != 0;
		}

		bool isdigit(char ch) {
			return std::isdigit(ch) != 0;
		}

		bool isxdigit(char ch) {
			return std::isxdigit(ch) != 0;
		}

		bool isspace(char ch) {
			return std::isspace(ch) != 0;
		}
		
		bool ispunct(char ch) {
			return std::ispunct(ch) != 0;
		}

		bool isblank(char ch) {
			return std::isblank(ch) != 0;
		}

		bool isalnum(char ch) {
			return std::isalnum(ch) != 0;
		}

		bool isprint(char ch) {
			return std::isprint(ch) != 0;
		}

		bool isgraph(char ch) {
			return std::isgraph(ch) != 0;
		}

		bool iscntrl(char ch) {
			return std::iscntrl(ch) != 0;
		}

		char toupper(char ch) {
			return std::toupper(ch);
		}

		char tolower(char ch) {
			return std::tolower(ch);
		}

		//-------------------- WCHAR_T --------------------//

		bool iswalnum(wchar_t ch) {
			return std::iswalnum(ch) != 0;
		}

		bool iswalpha(wchar_t ch) {
			return std::iswalpha(ch) != 0;
		}

		bool iswblank(wchar_t ch) {
			return std::iswblank(ch) != 0;
		}

		bool iswcntrl(wchar_t ch) {
			return std::iswcntrl(ch) != 0;
		}

		bool iswdigit(wchar_t ch) {
			return std::iswdigit(ch) != 0;
		}

		bool iswgraph(wchar_t ch) {
			return std::iswgraph(ch) != 0;
		}

		bool iswlower(wchar_t ch) {
			return std::iswlower(ch) != 0;
		}

		bool iswprint(wchar_t ch) {
			return std::iswprint(ch) != 0;
		}

		bool iswpunct(wchar_t ch) {
			return std::iswpunct(ch) != 0;
		}

		bool iswspace(wchar_t ch) {
			return std::iswspace(ch) != 0;
		}

		bool iswupper(wchar_t ch) {
			return std::iswupper(ch) != 0;
		}

		wchar_t towupper(wchar_t ch) {
			return std::towupper(ch);
		}

		wchar_t towlower(wchar_t ch) {
			return std::towlower(ch);
		}

	} // namespace CharMap

} // namespace nw