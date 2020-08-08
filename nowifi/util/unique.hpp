#pragma once

#include <nowifi/compiler/class.hpp>
#include <unordered_map>
#include <stdexcept>


namespace nw {

	namespace unique {
	
		template <
			class Ty,
			class _Hasher = std::hash<Ty>,
			class _Keyeq = std::equal_to<Ty>,
			class _Alloc = std::allocator<std::pair<const Ty, int>>
		>
			using map = std::unordered_map<Ty, int, _Hasher, _Keyeq, _Alloc>;


		template <class Ty>
		int get(const map<Ty>& unique, const Ty& val)
		{
			try 
			{
				return unique.at(val);
			}
			catch (const std::out_of_range& err)
			{
				return 0;
			}
		}

		template <class Ty>
		void set(map<Ty>& unique, const Ty& val, int num)
		{
			unique[val] = num;
		}

		template <class Ty>
		void add(map<Ty>& unique, const Ty& val, int num)
		{
			unique[val] = get(unique, val) + num;
		}

		template <class Ty>
		void inc(map<Ty>& unique, const Ty& val)
		{
			set<Ty>(unique, val, 1);
		}

		template <class Ty>
		void dec(map<Ty>& unique, const Ty& val)
		{
			set<Ty>(unique, val, -1);
		}
	
	} // namespace unique

} // namespace nw