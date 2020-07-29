#pragma once


namespace nw4u {

    namespace function {

        template <class TyIn, class TyOut, class TyFun>
        TyIn binary_search(const TyIn left, const TyIn right, const TyOut target, size_t maxdepth, TyFun fn)
        {
            TyIn _left = left;
            TyIn _right = right;

            for (size_t depth = 0; depth < maxdepth; depth++)
            {
                TyIn pivot = (_left + _right) / 2;
                TyOut middle = fn(pivot);
                if (target < middle)
                    _right = pivot;
                else if (middle < target)
                    _left = pivot;
                else
                    return pivot;
            }
            return _left;
        }

        template <class Ty, class TyFun>
        Ty binary_search(const Ty left, const Ty right, const Ty target, size_t depth, TyFun fn)
        {
            return binary_search<Ty, Ty>(left, right, target, depth, fn);
        }

        template <class TyIn, class TyOut, class TyFun>
        TyIn binary_search_bound(const TyIn left, const TyIn right, const TyOut precLeft, const TyOut precRight, TyFun fn, size_t maxdepth = 1024)
        {
            TyIn _left = left;
            TyIn _right = right;

            for (size_t depth = 0; depth < maxdepth; depth++)
            {
                TyIn pivot = (_left + _right) / 2;
                TyOut middle = fn(pivot);
                if (precRight < middle)
                    _right = pivot;
                else if (middle < precLeft)
                    _left = pivot;
            }
            return left;
        }

        template <class Ty, class TyFun>
        Ty binary_search_bound(const Ty left, const Ty right, const Ty precLeft, const Ty precRight, TyFun fn, size_t maxdepth = 1024)
        {
            return binary_search_bound<Ty, Ty>(left, right, precLeft, precRight, fn, maxdepth);
        }

        template <class TyIn, class TyOut, class TyFun>
        TyIn binary_search_epsilon(const TyIn left, const TyIn right, const TyOut target, const TyOut eps, TyFun fn, size_t maxdepth = 1024)
        {
            return binary_search_bound<TyIn, TyOut>(left, right, target - eps, target + eps, fn, maxdepth);
        }

        template <class Ty, class TyFun>
        Ty binary_search_epsilon(const Ty left, const Ty right, const Ty target, const Ty eps, TyFun fn, size_t maxdepth = 1024)
        {
            return binary_search_epsilon<Ty, Ty>(left, right, target, eps, fn, maxdepth);
        }

    } // namespace Function

} // namespace nw4u