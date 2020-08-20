#pragma once

#include <nowifi/compiler/class.hpp>
#include <functional>


namespace nw {

	template <class TyIn, class TyOut, TyOut(*Fun)(TyIn)>
	class FuncIterator 
	{

	protected:

		TyIn value;
		TyIn dval;
		TyOut result;

		using FuncIterator_type = FuncIterator<TyIn, TyOut, Fun>;

	public:
		
		FuncIterator(TyIn value, TyIn dval = 1) 
		{
			this->update(value, dval);
		}

		FuncIterator(const FuncIterator_type& second)
			: FuncIterator(second.value, second.dval) {}

		TyOut operator()(TyIn value = value) const 
		{
			return Fun(value);
		}

		FuncIterator_type& update(TyIn value) 
		{
			this->value = value;
			this->result = Fun(value);
			return THIS;
		}

		FuncIterator_type& update(TyIn value, TyIn dval) 
		{
			this->dval = dval;
			this->update(value);
		}

		const TyOut& operator*() const 
		{
			return this->result;
		}

		bool lt(const FuncIterator_type& second) const 
		{
			return this->result < second.result;
		}

		bool equal(const FuncIterator_type& second) const 
		{
			return this->result == second.result;
		}

		bool operator==(const FuncIterator_type& second) const {
			return !this->lt(second);
		}

		bool operator!=(const FuncIterator_type& second) const {
			return this->lt(second);
		}

		FuncIterator_type& operator++() 
		{
			return this->update(value + dval);
		}

		FuncIterator_type& operator--() 
		{
			return this->update(value - dval);
		}

		template <class Ty>
		FuncIterator_type operator+(Ty value) const 
		{
			return FuncIterator_type(this->value + value, this->dval);
		}

		template <class Ty>
		FuncIterator_type operator-(Ty value) const 
		{
			return FuncIterator_type(this->value - value, this->dval);
		}

	}; // class FuncIterator

	template <class TyIn, class TyOut, TyOut(*Fun)(TyIn)>
	class FuncIterator_Backward : public FuncIterator<TyIn, TyOut, Fun>
	{
	protected:

		using FuncIterator_type = FuncIterator<TyIn, TyOut, Fun>;

	public:

		bool operator==(const FuncIterator_type& second) const {
			return this->lt(second) || this->equal(second);
		}

		bool operator!=(const FuncIterator_type& second) const {
			return !this->lt(second) && !this->equal(second);
		}

	}; // class FuncIterator_Backward

} // namespace nw