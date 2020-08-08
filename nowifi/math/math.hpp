#pragma once

namespace nw {

    namespace Math {

        template <class Ty>
        _CONSTEXPR17 inline const Ty min(const Ty val1, const Ty val2)
        {
            return val1 < val2 ? val1 : val2;
        }

        template <class Ty>
        _CONSTEXPR17 inline const Ty max(const Ty val1, const Ty val2)
        {
            return val1 < val2 ? val2 : val1;
        }

        template <class Ty1, class Ty2>
        _CONSTEXPR17 inline bool willOverflow(const Ty1 val1, const Ty2 val2)
        {
            return (val1 + val2) < val1;
        }

        template <class Ty1, class Ty2>
        _CONSTEXPR17 inline bool willUnderflow(const Ty1 val1, const Ty2 val2)
        {
            return (val1 - val2) > val1;
        }

        namespace constref {
        
            template <class Ty>
            inline const Ty& min(const Ty& val1, const Ty& val2)
            {
                return val1 < val2 ? val1 : val2;
            }

            template <class Ty>
            inline const Ty& max(const Ty& val1, const Ty& val2)
            {
                return val1 < val2 ? val2 : val1;
            }

            template <class Ty1, class Ty2>
            inline bool willOverflow(const Ty1& val1, const Ty2& val2)
            {
                return (val1 + val2) < val1;
            }

            template <class Ty1, class Ty2>
            inline bool willUnderflow(const Ty1& val1, const Ty2& val2)
            {
                return (val1 - val2) > val1;
            }
        
        }

    } // namespace Math

} // namespace nw