#pragma once

namespace nw {

	template <typename Ty>
	struct Map {

		Ty input_low, input_high, output_low, output_high;

		Map(Ty input_low, Ty input_high, Ty output_low, Ty output_high)
			: input_low(input_low), input_high(input_high), output_low(output_low), output_high(output_high) { }

		Map(Ty input_low, Ty input_high)
			: Map(input_low, input_high, 0, 1) { }

		_NODISCARD _CONSTEXPR17 inline Ty map(Ty input) {
			return Map::map(input, input_low, input_high, output_low, output_high);
		}

		static _NODISCARD _CONSTEXPR17 inline Ty map_scale(Ty input, Ty input_low, Ty input_high) {
			const Ty input_size = input_high - input_low;
			const Ty input_delta = input - input_low;

			return input_delta / input_size;
		}

		static _NODISCARD _CONSTEXPR17 inline Ty map_unscale(Ty scale, Ty output_low, Ty output_high) {
			const Ty output_size = output_high - output_low;
			const Ty output_delta = output_size * scale;

			return output_low + output_delta;
		}

		static _NODISCARD _CONSTEXPR17 inline Ty map(Ty input, Ty input_low, Ty input_high, Ty output_low, Ty output_high) {
			const Ty scale = map_scale(input, input_low, input_high);

			return map_unscale(scale, output_low, output_high);
		}

		static _NODISCARD _CONSTEXPR17 inline Ty map_reverse(Ty input, Ty low, Ty high) {
			const Ty delta = input - low;

			return high - delta;
		}

	}; // class Map

} // namespace nw