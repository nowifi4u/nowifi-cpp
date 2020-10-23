#pragma once

#include <stdexcept>

namespace nw {

	template <size_t _size, class _Ty>
	struct uVector
	{
		using below_type = uVector<_size - 1, _Ty>;

		union
		{
			_Ty arr[_size];

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

		static constexpr size_t size()
		{
			return _size;
		}

		_Ty& operator[](size_t idx)
		{
			if (idx >= _size) throw std::invalid_argument("Index too big");
			return arr[idx];
		}

		const _Ty& operator[](size_t idx) const
		{
			if (idx >= _size) throw std::invalid_argument("Index too big");
			return arr[idx];
		}
	};

	template <class _Ty>
	struct uVector <0, _Ty>
	{
		static constexpr size_t size()
		{
			return 0;
		}
	};

	//------------------------------                ------------------------------//
	//------------------------------                ------------------------------//
	//------------------------------    ALIASES     ------------------------------//
	//------------------------------                ------------------------------//
	//------------------------------                ------------------------------//

	template <class _Ty>
	using uVector1 = uVector<1, _Ty>;

	template <class _Ty>
	using uVector2 = uVector<2, _Ty>;

	template <class _Ty>
	using uVector3 = uVector<3, _Ty>;

	template <class _Ty>
	using uVector4 = uVector<4, _Ty>;

} // namespace nw