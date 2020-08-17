#pragma once

#include <nowifi/pack/compare.hpp>
#include <nowifi/util/consumer.hpp>

#include <limits>

namespace nw {

    template <class Ty>
    class SumReducer : public Consumer_Reset<Ty>
    {
    protected:
        Ty _sum;

    public:
        SumReducer(const Ty& value = Ty(0))
        {
            this->reset(value);
        }

        void reset(const Ty& value = Ty(0))
        {
            _sum = value;
        }

        void consume(const Ty& value)
        {
            _sum = _sum + value;
        }
    };

} // namespace nw