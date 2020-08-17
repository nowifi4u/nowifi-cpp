#pragma once

namespace nw {

    template <class Ty>
    class Consumer
    {
    public:
        virtual void consume(const Ty& value) = 0;
    };

    template <class Ty>
    class Consumer_Reset : public Consumer<Ty>
    {
    public:
        virtual void reset(const Ty& value) = 0;
    };

} // namespace nw