#pragma once

#include <string>
#include <functional>

namespace nw {

    unsigned inline constexpr Hash(char const* input) {
        return *input ? /*!= '\0'*/
            static_cast<unsigned int>(*input) + 33 * Hash(input + 1) :
            5381;
    }

    unsigned inline Hash(const std::string& str) {
        return Hash(str.c_str());
    }

} // namespace nw