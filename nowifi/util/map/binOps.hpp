#pragma once

namespace nw {

	namespace BinOps {

		template<typename Ty>
		_CONSTEXPR17 inline bool boolenify(const Ty value) {
			return !!value;
		}

		_CONSTEXPR17 inline bool NOT(bool a) {
			return !a;
		}

		_CONSTEXPR17 inline bool OR(bool a, bool b) {
			return a || b;
		}

		_CONSTEXPR17 inline bool AND(bool a, bool b) {
			return a && b;
		}

		_CONSTEXPR17 inline bool XOR(bool a, bool b) {
			return a != b;
		}

		_CONSTEXPR17 inline bool EQUALS(bool a, bool b) {
			return a == b;
		}

		_CONSTEXPR17 inline bool SUBTRACT(bool a, bool b) {
			return a && (!b);
		}

		_CONSTEXPR17 inline bool TRANS(bool a, bool b) {
			return !SUBTRACT(a, b);
		}

	} // namespace BinOps

} // namespace nw