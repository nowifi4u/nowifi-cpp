#pragma once

#define LOOP1(CODE) CODE
#define LOOP2(CODE) CODE LOOP1( CODE )
#define LOOP3(CODE) CODE LOOP2( CODE )

#define LOOP(N, CODE) LOOP ## n(a)

namespace nw {

	////////////////////////////////             ////////////////////////////////
	//------------------------------             ------------------------------//
	//------------------------------  FOR_LOOP   ------------------------------//
	//------------------------------             ------------------------------//
	////////////////////////////////             ////////////////////////////////

	template <size_t N>
	struct for_loop
	{
		template <class Func>
		static inline void call(Func const& fun)
		{
			for_loop<N - 1>::call(fun);
			fun();
		}
	};

	template <>
	struct for_loop <0u>
	{
		template <class Func>
		static inline void call(Func const& fun) { }
	};

	////////////////////////////////             ////////////////////////////////
	//------------------------------             ------------------------------//
	//------------------------------ FOR_LOOP_I  ------------------------------//
	//------------------------------             ------------------------------//
	////////////////////////////////             ////////////////////////////////

	template <size_t N>
	struct for_loop_i
	{
		template <class Func>
		static inline void call(Func const& fun)
		{
			for_loop_i<N - 1>::call(fun);
			fun(N - 1);
		}
	};

	template <>
	struct for_loop_i <0U>
	{
		template <class Func>
		static inline void call(Func const& fun) { }
	};

	////////////////////////////////              ////////////////////////////////
	//------------------------------              ------------------------------//
	//------------------------------ FOR_LOOP_ANY ------------------------------//
	//------------------------------              ------------------------------//
	////////////////////////////////              ////////////////////////////////


	template <size_t N>
	struct for_loop_any
	{
		template <class Func>
		static inline bool call(Func const& fun)
		{
			if (for_loop_any<N - 1>::call(fun)) return true;
			return fun();
		}
	};

	template <>
	struct for_loop_any <0U>
	{
		template <class Func>
		static inline bool call(Func const& fun)
		{
			return false;
		}
	};

	////////////////////////////////                ////////////////////////////////
	//------------------------------                ------------------------------//
	//------------------------------ FOR_LOOP_ANY_I ------------------------------//
	//------------------------------                ------------------------------//
	////////////////////////////////                ////////////////////////////////


	template <size_t N>
	struct for_loop_any_i
	{
		template <class Func>
		static inline bool call(Func const& fun)
		{
			if (for_loop_any_i<N - 1>::call(fun)) return true;
			return fun(N - 1);
		}
	};

	template <>
	struct for_loop_any_i <0U>
	{
		template <class Func>
		static inline bool call(Func const& fun)
		{
			return false;
		}
	};

	////////////////////////////////                  ////////////////////////////////
	//------------------------------                  ------------------------------//
	//------------------------------ FOR_LOOP_ANY_PTR ------------------------------//
	//------------------------------                  ------------------------------//
	////////////////////////////////                  ////////////////////////////////


	template <size_t N>
	struct for_loop_any_ptr
	{
		template <class Ty, class Func>
		static inline bool call(Func const& fun)
		{
			Ty result = for_loop_any_ptr<N - 1>::template call<Ty>(fun);
			if (result != nullptr) return result;
			return fun();
		}
	};

	template <>
	struct for_loop_any_ptr <0U>
	{
		template <class Ty, class Func>
		static inline bool call(Func const& fun)
		{
			return nullptr;
		}
	};

	////////////////////////////////                    ////////////////////////////////
	//------------------------------                    ------------------------------//
	//------------------------------ FOR_LOOP_ANY_PTR_I ------------------------------//
	//------------------------------                    ------------------------------//
	////////////////////////////////                    ////////////////////////////////


	template <size_t N>
	struct for_loop_any_ptr_i
	{
		template <class Ty, class Func>
		static inline bool call(Func const& fun)
		{
			Ty result = for_loop_any_ptr_i<N - 1>::template call<Ty>(fun);
			if (result != nullptr) return result;
			return fun(N - 1);
		}
	};

	template <>
	struct for_loop_any_ptr_i <0U>
	{
		template <class Ty, class Func>
		static inline bool call(Func const& fun)
		{
			return nullptr;
		}
	};

	////////////////////////////////                 ////////////////////////////////
	//------------------------------                 ------------------------------//
	//------------------------------ FOR_LOOP_REDUCE ------------------------------//
	//------------------------------                 ------------------------------//
	////////////////////////////////                 ////////////////////////////////

	template <size_t N>
	struct for_loop_reduce
	{
		template <class Ty, class Func, class Reducer>
		static inline bool call(const Ty& start, Func const& fun, Reducer const& reducer)
		{
			return reducer(for_loop_reduce<N - 1>::template call<Ty>(start, fun, reducer), fun());
		}
	};

	template <>
	struct for_loop_reduce <0U>
	{
		template <class Ty, class Func, class Reducer>
		static inline bool call(const Ty& start, Func const& fun, Reducer const& reducer)
		{
			return start;
		}
	};

	////////////////////////////////                   ////////////////////////////////
	//------------------------------                   ------------------------------//
	//------------------------------ FOR_LOOP_REDUCE_I ------------------------------//
	//------------------------------                   ------------------------------//
	////////////////////////////////                   ////////////////////////////////

	template <size_t N>
	struct for_loop_reduce_i
	{
		template <class Ty, class Func, class Reducer>
		static inline bool call(const Ty& start, Func const& fun, Reducer const& reducer)
		{
			return reducer(for_loop_reduce_i<N - 1>::template call<Ty>(start, fun, reducer), fun(N - 1));
		}
	};

	template <>
	struct for_loop_reduce_i <0U>
	{
		template <class Ty, class Func, class Reducer>
		static inline bool call(const Ty& start, Func const& fun, Reducer const& reducer)
		{
			return start;
		}
	};

} // namespace nw