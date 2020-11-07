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

	public:
		
		FuncIterator(TyIn value, TyIn dval = 1) 
		{
			this->update(value, dval);
		}

		FuncIterator(const FuncIterator& second)
			: FuncIterator(second.value, second.dval) {}

		TyOut operator()(TyIn value = value) const 
		{
			return Fun(value);
		}

		FuncIterator& update(TyIn value) 
		{
			this->value = value;
			this->result = Fun(value);
			return THIS;
		}

		FuncIterator& update(TyIn value, TyIn dval) 
		{
			this->dval = dval;
			this->update(value);
		}

		const TyOut& operator*() const 
		{
			return this->result;
		}

		bool lt(const FuncIterator& second) const 
		{
			return this->result < second.result;
		}

		bool equal(const FuncIterator& second) const 
		{
			return this->result == second.result;
		}

		bool operator==(const FuncIterator& second) const {
			return !this->lt(second);
		}

		bool operator!=(const FuncIterator& second) const {
			return this->lt(second);
		}

		FuncIterator& operator++() 
		{
			return this->update(value + dval);
		}

		FuncIterator& operator--() 
		{
			return this->update(value - dval);
		}

		template <class Ty>
		FuncIterator operator+(Ty value) const 
		{
			return FuncIterator(this->value + value, this->dval);
		}

		template <class Ty>
		FuncIterator operator-(Ty value) const 
		{
			return FuncIterator(this->value - value, this->dval);
		}

	}; // class FuncIterator

	template <class TyIn, class TyOut, TyOut(*Fun)(TyIn)>
	class FuncIterator_Backward : public FuncIterator<TyIn, TyOut, Fun>
	{
	public:

		bool operator==(const FuncIterator_Backward& second) const {
			return this->lt(second) || this->equal(second);
		}

		bool operator!=(const FuncIterator_Backward& second) const {
			return !this->lt(second) && !this->equal(second);
		}

	}; // class FuncIterator_Backward

} // namespace nw