#pragma once

#include <nowifi/util/map/charMap.hpp>

namespace nw {

	template <typename charTy, charTy(*Fun)(charTy)>
	struct basic_insensitive_char_traits : public std::char_traits<charTy>
	{
		static inline bool eq(charTy ch1, charTy ch2) { return Fun(ch1) == Fun(ch2); }
		static inline bool lt(charTy ch1, charTy ch2) { return Fun(ch1) < Fun(ch2); }
		static inline bool gt(charTy ch1, charTy ch2) { return Fun(ch1) > Fun(ch2); }

		static int compare(const charTy* str1, const charTy* str2, size_t n)
		{
			while (n-- != 0) {
				if (lt(*str1, *str2)) return -1;
				if (gt(*str1, *str2)) return 1;
				++str1; ++str2;
			}
			return 0;
		}

		static const charTy* find(const charTy* str, int n, charTy ch)
		{
			while (n-- > 0 && !eq(*str, ch)) {
				++str;
			}
			return str;
		}

	}; // struct basic_insensitive_char_traits

	using case_insensivite_char_traits = basic_insensitive_char_traits<char, CharMap::toupper> ;

	using case_insensivite_wchar_traits = basic_insensitive_char_traits<wchar_t, CharMap::towupper> ;

} // namespace nw