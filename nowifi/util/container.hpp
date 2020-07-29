#pragma once

namespace nw {

	//------------------------------         ------------------------------//
	//------------------------------         ------------------------------//
	//------------------------------ Vector2 ------------------------------//
	//------------------------------         ------------------------------//
	//------------------------------         ------------------------------//

	template <class Ty>
	struct Vector2 {
		Ty X;
		Ty Y;

		Vector2(const Ty& X, const Ty& Y) 
			: X(X), Y(Y) {}

		Vector2(const Vector2<Ty>& second)
			: Vector2<Ty>(second.X, second.Y) {}

		Vector2<Ty>& operator=(const Vector2<Ty>& second)
		{
			this->X = second.X;
			this->Y = second.Y;
		}

	}; // struct Vector2

	using Vector2s = Vector2<short int>;
	using Vector2us = Vector2<unsigned short int>;

	using Vector2i = Vector2<int>;
	using Vector2ui = Vector2<unsigned int>;

	using Vector2l = Vector2<long int>;
	using Vector2ul = Vector2<unsigned long int>;

	using Vector2ll = Vector2<long long int>;
	using Vector2ull = Vector2<unsigned long long int>;

	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2ld = Vector2<long double>;

	//------------------------------         ------------------------------//
	//------------------------------         ------------------------------//
	//------------------------------ Vector3 ------------------------------//
	//------------------------------         ------------------------------//
	//------------------------------         ------------------------------//

	template <class Ty>
	struct Vector3 {
		Ty X;
		Ty Y;
		Ty Z;

		Vector3(const Ty& X, const Ty& Y, const Ty& Z)
			: X(X), Y(Y), Z(Z) {}

		Vector3(const Vector3<Ty>& second)
			: Vector2<Ty>(second.X, second.Y, second.Z) {}

		Vector3<Ty>& operator=(const Vector3<Ty>& second)
		{
			this->X = second.X;
			this->Y = second.Y;
			this->Z = second.Z;
		}

	}; // struct Vector3

	using Vector3s = Vector3<short int>;
	using Vector3us = Vector3<unsigned short int>;

	using Vector3i = Vector3<int>;
	using Vector3ui = Vector3<unsigned int>;

	using Vector3l = Vector3<long int>;
	using Vector3ul = Vector3<unsigned long int>;

	using Vector3ll = Vector3<long long int>;
	using Vector3ull = Vector3<unsigned long long int>;

	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3ld = Vector3<long double>;
}