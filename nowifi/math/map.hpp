#pragma once

namespace nw {

	template <typename Ty>
	struct Map {

		Ty input_low, input_high, output_low, output_high;

		Map(Ty input_low, Ty input_high, Ty output_low, Ty output_high)
			: input_low(input_low), input_high(input_high), output_low(output_low), output_high(output_high) { }

		Map(Ty input_low, Ty input_high)
			: Map(input_low, input_high, 0, 1) { }

		[[NODISCARD]]
		constexpr Ty map(Ty input) noexcept
		{
			return Map::map(input, input_low, input_high, output_low, output_high);
		}

		[[NODISCARD]]
		static constexpr Ty map_scale(Ty input, Ty input_low, Ty input_high) noexcept
		{
			const Ty input_size = input_high - input_low;
			const Ty input_delta = input - input_low;

			return input_delta / input_size;
		}

		[[NODISCARD]]
		static constexpr Ty map_unscale(Ty scale, Ty output_low, Ty output_high) noexcept
		{
			const Ty output_size = output_high - output_low;
			const Ty output_delta = output_size * scale;

			return output_low + output_delta;
		}

		[[NODISCARD]]
		static constexpr Ty map(Ty input, Ty input_low, Ty input_high, Ty output_low, Ty output_high) noexcept
		{
			const Ty scale = map_scale(input, input_low, input_high);

			return map_unscale(scale, output_low, output_high);
		}

	}; // class Map

} // namespace nw