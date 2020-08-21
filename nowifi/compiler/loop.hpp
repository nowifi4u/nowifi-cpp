#pragma once

#define LOOP1(CODE) CODE
#define LOOP2(CODE) CODE LOOP1( CODE )
#define LOOP3(CODE) CODE LOOP2( CODE )

#define LOOP(N, CODE) LOOP ## n(a)

namespace nw {

	namespace for_loop {

		////////////////////////////////             ////////////////////////////////
	//------------------------------             ------------------------------//
	//------------------------------  FOR_LOOP   ------------------------------//
	//------------------------------             ------------------------------//
	////////////////////////////////             ////////////////////////////////

		template <size_t N>
		struct raw
		{
			template <class Func>
			static inline void call(Func const& fun)
			{
				raw<N - 1>::call(fun);
				fun();
			}
		};

		template <>
		struct raw <0u>
		{
			template <class Func>
			static inline void call(Func const& fun) { }
		};

		////////////////////////////////             ////////////////////////////////
		//------------------------------             ------------------------------//
		//------------------------------          I  ------------------------------//
		//------------------------------             ------------------------------//
		////////////////////////////////             ////////////////////////////////

		template <size_t N>
		struct raw_i
		{
			template <class Func>
			static inline void call(Func const& fun)
			{
				raw_i<N - 1>::call(fun);
				fun(N - 1);
			}
		};

		template <>
		struct raw_i <0U>
		{
			template <class Func>
			static inline void call(Func const& fun) { }
		};

		////////////////////////////////              ////////////////////////////////
		//------------------------------              ------------------------------//
		//------------------------------          ANY ------------------------------//
		//------------------------------              ------------------------------//
		////////////////////////////////              ////////////////////////////////


		template <size_t N>
		struct any
		{
			template <class Func>
			static inline bool call(Func const& fun)
			{
				if (any<N - 1>::call(fun)) return true;
				return fun();
			}
		};

		template <>
		struct any <0U>
		{
			template <class Func>
			static inline bool call(Func const& fun)
			{
				return false;
			}
		};

		////////////////////////////////                ////////////////////////////////
		//------------------------------                ------------------------------//
		//------------------------------          ANY_I ------------------------------//
		//------------------------------                ------------------------------//
		////////////////////////////////                ////////////////////////////////


		template <size_t N>
		struct any_i
		{
			template <class Func>
			static inline bool call(Func const& fun)
			{
				if (any_i<N - 1>::call(fun)) return true;
				return fun(N - 1);
			}
		};

		template <>
		struct any_i <0U>
		{
			template <class Func>
			static inline bool call(Func const& fun)
			{
				return false;
			}
		};

		////////////////////////////////              ////////////////////////////////
		//------------------------------              ------------------------------//
		//------------------------------          ALL ------------------------------//
		//------------------------------              ------------------------------//
		////////////////////////////////              ////////////////////////////////


		template <size_t N>
		struct all
		{
			template <class Func>
			static inline bool call(Func const& fun)
			{
				if (!all<N - 1>::call(fun)) return false;
				return fun();
			}
		};

		template <>
		struct all <0U>
		{
			template <class Func>
			static inline bool call(Func const& fun)
			{
				return true;
			}
		};

		////////////////////////////////                ////////////////////////////////
		//------------------------------                ------------------------------//
		//------------------------------          ALL_I ------------------------------//
		//------------------------------                ------------------------------//
		////////////////////////////////                ////////////////////////////////


		template <size_t N>
		struct all_i
		{
			template <class Func>
			static inline bool call(Func const& fun)
			{
				if (!all_i<N - 1>::call(fun)) return false;
				return fun(N - 1);
			}
		};

		template <>
		struct all_i <0U>
		{
			template <class Func>
			static inline bool call(Func const& fun)
			{
				return true;
			}
		};

		////////////////////////////////                  ////////////////////////////////
		//------------------------------                  ------------------------------//
		//------------------------------          ANY_PTR ------------------------------//
		//------------------------------                  ------------------------------//
		////////////////////////////////                  ////////////////////////////////


		template <size_t N>
		struct any_ptr
		{
			template <class Ty, class Func>
			static inline bool call(Func const& fun)
			{
				Ty result = any_ptr<N - 1>::template call<Ty>(fun);
				if (result != nullptr) return result;
				return fun();
			}
		};

		template <>
		struct any_ptr <0U>
		{
			template <class Ty, class Func>
			static inline bool call(Func const& fun)
			{
				return nullptr;
			}
		};

		////////////////////////////////                    ////////////////////////////////
		//------------------------------                    ------------------------------//
		//------------------------------          ANY_PTR_I ------------------------------//
		//------------------------------                    ------------------------------//
		////////////////////////////////                    ////////////////////////////////


		template <size_t N>
		struct any_ptr_i
		{
			template <class Ty, class Func>
			static inline bool call(Func const& fun)
			{
				Ty result = any_ptr_i<N - 1>::template call<Ty>(fun);
				if (result != nullptr) return result;
				return fun(N - 1);
			}
		};

		template <>
		struct any_ptr_i <0U>
		{
			template <class Ty, class Func>
			static inline bool call(Func const& fun)
			{
				return nullptr;
			}
		};

		////////////////////////////////                  ////////////////////////////////
		//------------------------------                  ------------------------------//
		//------------------------------          ANY_INT ------------------------------//
		//------------------------------                  ------------------------------//
		////////////////////////////////                  ////////////////////////////////


		template <size_t N>
		struct any_int
		{
			template <class Func>
			static inline int call(Func const& fun)
			{
				int result = any_int<N - 1>::call(fun);
				if (result != 0) return result;
				return fun();
			}
		};

		template <>
		struct any_int <0U>
		{
			template <class Func>
			static inline int call(Func const& fun)
			{
				return 0;
			}
		};

		////////////////////////////////                    ////////////////////////////////
		//------------------------------                    ------------------------------//
		//------------------------------          ANY_INT_I ------------------------------//
		//------------------------------                    ------------------------------//
		////////////////////////////////                    ////////////////////////////////


		template <size_t N>
		struct any_int_i
		{
			template <class Func>
			static inline int call(Func const& fun)
			{
				int result = any_int_i<N - 1>::call(fun);
				if (result != 0) return result;
				return fun(N - 1);
			}
		};

		template <>
		struct any_int_i <0U>
		{
			template <class Func>
			static inline int call(Func const& fun)
			{
				return 0;
			}
		};

		////////////////////////////////                 ////////////////////////////////
		//------------------------------                 ------------------------------//
		//------------------------------          REDUCE ------------------------------//
		//------------------------------                 ------------------------------//
		////////////////////////////////                 ////////////////////////////////

		template <size_t N>
		struct reduce
		{
			template <class Ty, class Func, class Reducer>
			static inline bool call(const Ty& start, Func const& fun, Reducer const& reducer)
			{
				return reducer(reduce<N - 1>::template call<Ty>(start, fun, reducer), fun());
			}
		};

		template <>
		struct reduce <0U>
		{
			template <class Ty, class Func, class Reducer>
			static inline bool call(const Ty& start, Func const& fun, Reducer const& reducer)
			{
				return start;
			}
		};

		////////////////////////////////                   ////////////////////////////////
		//------------------------------                   ------------------------------//
		//------------------------------          REDUCE_I ------------------------------//
		//------------------------------                   ------------------------------//
		////////////////////////////////                   ////////////////////////////////

		template <size_t N>
		struct reduce_i
		{
			template <class Ty, class Func, class Reducer>
			static inline bool call(const Ty& start, Func const& fun, Reducer const& reducer)
			{
				return reducer(reduce_i<N - 1>::template call<Ty>(start, fun, reducer), fun(N - 1));
			}
		};

		template <>
		struct reduce_i <0U>
		{
			template <class Ty, class Func, class Reducer>
			static inline bool call(const Ty& start, Func const& fun, Reducer const& reducer)
			{
				return start;
			}
		};

	} // namespace raw

} // namespace nw