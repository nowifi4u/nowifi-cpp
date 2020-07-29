#pragma once

#include <nowifi/compiler/loop.hpp>
#include <iostream>

namespace nw {

	template <size_t N, typename charTy>
	struct basic_Endline {

		using ostream_type = std::basic_ostream<charTy>;

		basic_Endline() noexcept { }

		friend ostream_type& operator<<(ostream_type& os, const basic_Endline<N, charTy>& obj) {
			loop<N>::call([&os]()
			{
				os << std::endl<charTy>; 
			});
			return os;
		}
	};

	template <size_t N>
	using Endline = basic_Endline<N, char>;

	template <size_t N>
	using WEndline = basic_Endline<N, wchar_t>;

} // namespace nw