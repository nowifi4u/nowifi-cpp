#pragma once

namespace nw {

	template <typename Ty>
	class Map {

		Ty input_low, input_high, output_low, output_high;

	public:

		Map(const Ty input_low, const Ty input_high, const Ty output_low, const Ty output_high)
			: input_low(input_low), input_high(input_high), output_low(output_low), output_high(output_high) {}

		inline Ty map(const Ty input) {
			return Map::map(input, input_low, input_high, output_low, output_high);
		}

		static constexpr inline Ty map_scale(const Ty input, const Ty input_low, const Ty input_high) {
			const Ty input_size = input_high - input_low;
			const Ty input_delta = input - input_low;

			return input_delta / input_size;
		}

		static constexpr inline Ty map_unscale(const Ty scale, const Ty output_low, const Ty output_high) {
			const Ty output_size = output_high - output_low;
			const Ty output_delta = output_size * scale;

			return output_low + output_delta;
		}

		static constexpr inline Ty map(const Ty input, const Ty input_low, const Ty input_high, const Ty output_low, const Ty output_high) {
			const Ty scale = map_scale(input, input_low, input_high);

			return map_unscale(scale, output_low, output_high);
		}

		static constexpr inline Ty map_reverse(const Ty input, const Ty low, const Ty high) {
			const Ty delta = input - low;

			return high - delta;
		}

	}; // class Map

} // namespace nw