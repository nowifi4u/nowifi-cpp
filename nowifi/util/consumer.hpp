#pragma once

namespace nw {

    template <class Ty>
    class Consumer
    {
    public:
        virtual void consume(const Ty& value) = 0;
    };

} // namespace nw