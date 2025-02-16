#pragma once

#include <stdexcept>

namespace nw {

	//------------------------------                ------------------------------//
	//------------------------------                ------------------------------//
	//------------------------------    UVECTOR     ------------------------------//
	//------------------------------                ------------------------------//
	//------------------------------                ------------------------------//

	template <size_t _size, class _Ty>
	struct uVector
	{
		using value_type = _Ty;
		using size_type = size_t;
		using pointer = _Ty*;
		using const_pointer = const _Ty*;
		using reference = _Ty&;
		using const_reference = const _Ty&;

		using iterator = _Ty*;
		using const_iterator = const _Ty*;

		using below_type = uVector<_size - 1, _Ty>;

		union
		{
			_Ty array[_size];
			
			struct
			{
				_Ty first;
				below_type after_first;
			};

			struct
			{
				below_type before_last;
				_Ty last;
			};
		};

		static constexpr size_t size() noexcept
		{
			return _size;
		}

		_Ty& operator[](size_t idx)
		{
			if (idx >= _size) throw std::invalid_argument("Index too big");
			return array[idx];
		}

		_Ty* begin() noexcept
		{
			return array;
		}

		_Ty* end() noexcept
		{
			return array + _size;
		}
	};

	//------------------------------  UVECTOR <0>   ------------------------------//

	template <class _Ty>
	struct uVector <0, _Ty>
	{
		using value_type = _Ty;
		using size_type = size_t;
		using pointer = _Ty*;
		using const_pointer = const _Ty*;
		using reference = _Ty&;
		using const_reference = const _Ty&;

		using iterator = _Ty*;
		using const_iterator = const _Ty*;

		static constexpr size_t size() noexcept
		{
			return 0;
		}
	};

	//------------------------------    ALIASES     ------------------------------//

	template <class _Ty>
	using uVector1 = uVector<1, _Ty>;

	template <class _Ty>
	using uVector2 = uVector<2, _Ty>;

	template <class _Ty>
	using uVector3 = uVector<3, _Ty>;

	template <class _Ty>
	using uVector4 = uVector<4, _Ty>;

	template <class _Ty>
	using uVector5 = uVector<5, _Ty>;

	template <class _Ty>
	using uVector6 = uVector<6, _Ty>;

	template <class _Ty>
	using uVector7 = uVector<7, _Ty>;

	template <class _Ty>
	using uVector8 = uVector<8, _Ty>;

	template <class _Ty>
	using uVector9 = uVector<9, _Ty>;

	template <class _Ty>
	using uVector10 = uVector<10, _Ty>;

} // namespace nw