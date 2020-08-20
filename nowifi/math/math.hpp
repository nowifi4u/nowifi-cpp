#pragma once

namespace nw {

    namespace Math {

        template <class Ty1, class Ty2> [[nodiscard]]
        constexpr inline bool willOverflow(const Ty1 val1, const Ty2 val2)
        {
            return (val1 + val2) < val1;
        }

        template <class Ty1, class Ty2> [[nodiscard]]
        constexpr inline bool willUnderflow(const Ty1 val1, const Ty2 val2)
        {
            return (val1 - val2) > val1;
        }

        namespace constref {
        
            template <class Ty1, class Ty2> [[nodiscard]]
            inline bool willOverflow(const Ty1& val1, const Ty2& val2)
            {
                return (val1 + val2) < val1;
            }

            template <class Ty1, class Ty2> [[nodiscard]]
            inline bool willUnderflow(const Ty1& val1, const Ty2& val2)
            {
                return (val1 - val2) > val1;
            }
        
        } // namespace constref

    } // namespace Math

} // namespace nw