#pragma once

namespace nw {

	namespace BinOps {

		template<typename Ty>
		constexpr inline bool boolenify(const Ty value) {
			return !!value;
		}

		constexpr inline bool NOT(bool a) {
			return !a;
		}

		constexpr inline bool OR(bool a, bool b) {
			return a || b;
		}

		constexpr inline bool AND(bool a, bool b) {
			return a && b;
		}

		constexpr inline bool XOR(bool a, bool b) {
			return a != b;
		}

		constexpr inline bool EQUALS(bool a, bool b) {
			return a == b;
		}

		constexpr inline bool SUBTRACT(bool a, bool b) {
			return a && (!b);
		}

		constexpr inline bool TRANS(bool a, bool b) {
			return !SUBTRACT(a, b);
		}

	} // namespace BinOps

} // namespace nw