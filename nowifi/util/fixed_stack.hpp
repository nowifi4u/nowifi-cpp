#pragma once

#include <nowifi/compiler/class.hpp>
#include <stack>

namespace nw {

	template <class Ty>
	class fixed_stack : public std::stack<Ty>
	{
	public:

		size_t fixed_size;

		using fixed_stack_type = fixed_stack<Ty>;

		using stack_type = std::stack<Ty>;

		fixed_stack(size_t size)
			: stack_type(),
			fixed_size(size) { }

		fixed_stack(size_t size, const stack_type& src)
			: stack_type(src),
			fixed_size(size) { }

		fixed_stack(size_t size, stack_type&& src)
			: stack_type(std::move(src)),
			fixed_size(size) { }



		fixed_stack(const fixed_stack_type& src)
			: stack_type(src),
			fixed_size(src.fixed_size) { }

		fixed_stack_type& operator=(const fixed_stack_type& src)
		{
			super_type::operator=(src);
			this->fixed_size = src.fixed_size;
			return THIS;
		}



		fixed_stack(fixed_stack_type&& src)
			: stack_type(std::move(src)),
			fixed_size(src.size) { }

		fixed_stack_type& operator=(fixed_stack_type&& src)
		{
			super_type::operator=(std::move(src));
			this->fixed_size = src.fixed_size;
			return THIS;
		}

	protected:

		void fixsize()
		{
			while (this->size() > fixed_size)
			{
				super_type::pop();
			}
		}

	public:

		void push(const Ty& value)
		{
			super_type::push(value);

			fixsize();
		}

		void push(Ty&& value)
		{
			super_type::push(std::move(value));

			fixsize();
		}

	}; // class fixed_stack

} // namespace nw