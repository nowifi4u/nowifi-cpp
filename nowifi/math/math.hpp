#pragma once

namespace nw {

    namespace Math {

        template <class Ty>
        constexpr inline const Ty min(const Ty val1, const Ty val2)
        {
            return val1 < val2 ? val1 : val2;
        }

        template <class Ty>
        constexpr inline const Ty max(const Ty val1, const Ty val2)
        {
            return val1 < val2 ? val2 : val1;
        }

        template <class Ty1, class Ty2>
        constexpr inline bool willOverflow(const Ty1 val1, const Ty2 val2)
        {
            return (val1 + val2) < val1;
        }

        template <class Ty1, class Ty2>
        constexpr inline bool willUnderflow(const Ty1 val1, const Ty2 val2)
        {
            return (val1 - val2) > val1;
        }

        namespace ref {
        
            template <class Ty>
            constexpr inline const Ty& min(const Ty& val1, const Ty& val2)
            {
                return val1 < val2 ? val1 : val2;
            }

            template <class Ty>
            constexpr inline const Ty& max(const Ty& val1, const Ty& val2)
            {
                return val1 < val2 ? val2 : val1;
            }

            template <class Ty1, class Ty2>
            constexpr inline bool willOverflow(const Ty1& val1, const Ty2& val2)
            {
                return (val1 + val2) < val1;
            }

            template <class Ty1, class Ty2>
            constexpr inline bool willUnderflow(const Ty1& val1, const Ty2& val2)
            {
                return (val1 - val2) > val1;
            }
        
        }

    } // namespace Math

} // namespace nw