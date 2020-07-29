#pragma once

#include <nowifi/compiler/class.hpp>
#include <deque>

namespace nw {

	template <class Ty>
	class fixed_deque : public std::deque<Ty>
	{
	public:

		size_t fixed_size;

		using fixed_deque_type = fixed_deque<Ty>;

		using deque_type = std::deque<Ty>;

		fixed_deque(size_t size)
			: deque_type(),
			fixed_size(size) { }

		fixed_deque(size_t size, const deque_type& src)
			: deque_type(src),
			fixed_size(size) { }

		fixed_deque(size_t size, deque_type&& src)
			: deque_type(std::move(src)),
			fixed_size(size) { }



		fixed_deque(const fixed_deque_type& src)
			: deque_type(src),
			fixed_size(src.fixed_size) { }

		fixed_deque_type& operator=(const fixed_deque_type& src)
		{
			super_type::operator=(src);
			this->fixed_size = src.fixed_size;
			return THIS;
		}



		fixed_deque(fixed_deque_type&& src)
			: deque_type(std::move(src)),
			fixed_size(src.fixed_size) { }

		fixed_deque_type& operator=(fixed_deque_type&& src)
		{
			super_type::operator=(std::move(src));
			this->fixed_size = src.fixed_size;
			return THIS;
		}

	protected:

		void fixsize_back()
		{
			while (this->size() > fixed_size)
			{
				super_type::pop_back();
			}
		}

		void fixsize_front()
		{
			while (this->size() > fixed_size)
			{
				super_type::pop_front();
			}
		}

	public:

		void push_back(const Ty& value)
		{
			super_type::push_back(value);

			fixsize_front();
		}

		void push_back(Ty&& value)
		{
			super_type::push_back(std::move(value));

			fixsize_front();
		}

		void push_front(const Ty& value)
		{
			super_type::push_front(value);

			fixsize_back();
		}

		void push_front(Ty&& value)
		{
			super_type::push_front(std::move(value));

			fixsize_back();
		}

	}; // class fixed_deque

} // namespace nw