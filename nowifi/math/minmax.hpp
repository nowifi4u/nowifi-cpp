#pragma once

#include <nowifi/pack/compare.hpp>
#include <nowifi/util/consumer.hpp>

#include <limits>

namespace nw {

    template <class Ty>
    class _Consumer_Reset : public Consumer<Ty>
    {
    public:
        virtual void reset(const Ty& value) = 0;
    };

    template <class Ty>
    class MinReducer : public _Consumer_Reset<Ty>
    {
    protected:
        Ty _min;

    public:
        MinReducer(const Ty& value = std::numeric_limits<Ty>::max())
        {
            this->reset(value);
        }

        void reset(const Ty& value = std::numeric_limits<Ty>::max())
        {
            _min = value;
        }

        void consume(const Ty& value)
        {
            _min = Compare::constref::min(_min, value);
        }

        Ty min() const
        {
            return _min;
        }
    };

    template <class Ty>
    class MaxReducer : public _Consumer_Reset<Ty>
    {
    protected:
        Ty _max;

    public:
        MaxReducer(const Ty& value = std::numeric_limits<Ty>::min())
        {
            this->reset(value);
        }

        void reset(const Ty& value = std::numeric_limits<Ty>::min())
        {
            _max = value;
        }

        void consume(const Ty& value)
        {
            _max = Compare::constref::max(_max, value);
        }

        Ty max() const
        {
            return _max;
        }
    };

    template <class Ty>
    class MinMaxReducer : public virtual MinReducer<Ty>, public virtual MaxReducer<Ty>
    {
    public:
        MinMaxReducer(const Ty& value)
            : MinReducer<Ty>(value), MaxReducer<Ty>(value) {}

        MinMaxReducer()
            : MinReducer<Ty>(), MaxReducer<Ty>() {}

        void reset(const Ty& value)
        {
            MinReducer<Ty>::reset(value);
            MaxReducer<Ty>::reset(value);
        }

        void reset()
        {
            MinReducer<Ty>::reset();
            MaxReducer<Ty>::reset();
        }

        void consume(const Ty& value)
        {
            MinReducer<Ty>::consume(value);
            MaxReducer<Ty>::consume(value);
        }
    };

    template <class Ty>
    class SumReducer : public _Consumer_Reset<Ty>
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