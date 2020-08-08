#pragma once

#include <nowifi/compiler/class.hpp>
#include <deque>
#include <stack>

namespace nw {

	namespace fixed {

		namespace deque {
		
			template <class Ty>
			void fixsize_back(std::deque<Ty>& fixed, size_t size)
			{
				while (fixed.size() > size)
				{
					fixed.pop_back();
				}
			}

			template <class Ty>
			void fixsize_front(std::deque<Ty>& fixed, size_t size)
			{
				while (fixed.size() > size)
				{
					fixed.pop_front();
				}
			}

			template <class Ty>
			void push_back(std::deque<Ty>& fixed, size_t size, const Ty& val)
			{
				fixed.push_back(val);
				fixsize_front(fixed, size);
			}

			template <class Ty>
			void push_back(std::deque<Ty>& fixed, size_t size, Ty&& val)
			{
				fixed.push_back(std::move(val));
				fixsize_front(fixed, size);
			}

			template <class Ty>
			void push_front(std::deque<Ty>& fixed, size_t size, const Ty& val)
			{
				fixed.push_front(val);
				fixsize_back(fixed, size);
			}

			template <class Ty>
			void push_front(std::deque<Ty>& fixed, size_t size, Ty&& val)
			{
				fixed.push_front(std::move(val));
				fixsize_back(fixed, size);
			}
		
		} // namespace deque
	
		namespace stack {
		
			template <class Ty>
			void fixsize(std::stack<Ty>& fixed, size_t size)
			{
				while (fixed.size() > size)
				{
					fixed.pop();
				}
			}

			template <class Ty>
			void push(std::stack<Ty>& fixed, size_t size, const Ty& val)
			{
				fixed.push(val);
				fixsize(fixed, size);
			}

			template <class Ty>
			void push(std::stack<Ty>& fixed, size_t size, Ty&& val)
			{
				fixed.push(std::move(val));
				fixsize(fixed, size);
			}
		
		}
	
	} // namespace fixed

} // namespace nw