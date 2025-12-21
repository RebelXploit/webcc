#pragma once

namespace webcc
{

    template <typename... Args>
    class delegate
    {
    private:
        // StubFn now accepts the context AND all the arguments
        using StubFn = void (*)(void *, Args...);

        void *m_ctx;
        StubFn m_stub;

    public:
        delegate() : m_ctx(nullptr), m_stub(nullptr) {}
        delegate(decltype(nullptr)) : m_ctx(nullptr), m_stub(nullptr) {}

        // The Magic "from" method
        template <class T, void (T::*Method)(Args...)>
        static delegate from(T *obj)
        {
            delegate d;
            d.m_ctx = obj;
            d.m_stub = [](void *ctx, Args... args)
            {
                (static_cast<T *>(ctx)->*Method)(args...);
            };
            return d;
        }

        // Support for raw static functions/lambdas without capture
        delegate(void (*fn)(Args...))
        {
            m_ctx = (void *)fn;
            m_stub = [](void *ctx, Args... args)
            {
                auto original_fn = (void (*)(Args...))ctx;
                original_fn(args...);
            };
        }

        operator bool() const { return m_stub != nullptr; }

        // Variadic operator() passes all arguments through
        void operator()(Args... args) const
        {
            if (m_stub)
                m_stub(m_ctx, args...);
        }
    };
} // namespace webcc