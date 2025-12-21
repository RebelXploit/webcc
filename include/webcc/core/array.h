#pragma once
#include <stdint.h>
#include <stddef.h>

namespace webcc
{
    template <typename T, size_t N>
    class array
    {
    private:
        T m_data[N];

    public:
        // Accessors
        constexpr T *data() { return m_data; }
        constexpr const T *data() const { return m_data; }
        constexpr size_t size() const { return N; }

        // Bounds checking (Crucial for WASM debugging)
        T &operator[](size_t i)
        {
            return m_data[i];
        }

        // Iterator support for: for(auto& x : my_array)
        T *begin() { return &m_data[0]; }
        T *end() { return &m_data[N]; }
    };
} // namespace webcc