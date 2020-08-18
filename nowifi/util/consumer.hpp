#pragma once

#include <algorithm>
#include <xutility>

namespace nw {

    template <class Ty>
    class Consumer
    {
    public:
        virtual void consume(const Ty& value) = 0;

        template <class _Iter>
        void stl_consume(const _Iter _First, const _Iter _Last)
        {
            std::for_each(_First, _Last, [this](const auto& elem)
            {
                this->consume(elem);
            });
        }

        void consume(const Ty* arr, size_t size)
        {
            stl_consume(arr, arr + size);
        }
    };

    template <class Ty>
    class Consumer_Reset : virtual public Consumer<Ty>
    {
    public:
        virtual void reset(const Ty& value) = 0;
    };

} // namespace nw