#pragma once

#include <iostream>
#include <functional>

namespace nw {

	template <class Ty>
	class Error {

	protected:

		std::function<void(const Ty&)> fn;

		Error() noexcept
			: Error([](const Ty& msg) {}) {}

	public:

		Error(std::function<void(const Ty&)> fn) noexcept
			: fn(fn) {}

		Error(const Error<Ty>& second) noexcept
			: fn(second.fn) {}

		virtual ~Error() noexcept {}

		virtual void execute(const Ty& msg) const {
			fn(msg);
		}

	}; // class Error

	namespace global {

		template <class Ty>
		extern Error<Ty> Error_Throw = Error<Ty>([](const Ty& msg) {
			throw msg;
		});

		template <class Ty>
		extern Error<Ty> Error_Nothing = Error<Ty>([](const Ty& msg) {

		});

	} // namespace global

} // namespace nw