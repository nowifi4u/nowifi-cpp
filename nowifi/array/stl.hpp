#pragma once

namespace nw {

	namespace stl {

		template <class _InIt>
		inline _InIt advance(_InIt _First, int distance)
		{
			std::advance(_First, distance);
			return _First;
		}

		template <class _InIt>
		inline _InIt middle(_InIt _First, _InIt _Last)
		{
			return advance(_First, std::distance(_First, _Last) / 2);
		}

		namespace contiguous {

			template <class _InIt>
			inline _InIt advance(_InIt _First, int distance)
			{
				return _First + distance;
			}

			template <class _InIt>
			inline int distance(_InIt _First, _InIt _Last)
			{
				return static_cast<int>(_Last - _First);
			}

			template <class _InIt>
			inline _InIt middle(_InIt _First, _InIt _Last)
			{
				return advance(_First, distance(_First, _Last) / 2);
			}

		} // namespace contiguous

	} // namespace stl

} // namespace nw