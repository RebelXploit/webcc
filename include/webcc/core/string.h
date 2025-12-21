#pragma once
#include "allocator.h"
#include "string_view.h"
#include "format.h"

namespace webcc
{
    class string
    {
    private:
        char *m_data = nullptr;
        uint32_t m_len = 0;

        uint32_t strlen(const char *s)
        {
            uint32_t l = 0;
            while (s[l])
                l++;
            return l;
        }

    public:
        string() : m_data(nullptr), m_len(0) {}

        string(const char *s)
        {
            m_len = strlen(s);
            m_data = (char *)webcc::malloc(m_len + 1);
            for (uint32_t i = 0; i <= m_len; i++)
                m_data[i] = s[i];
        }

        // Move constructor (Zero-cost transfer of ownership)
        string(string &&other)
        {
            m_data = other.m_data;
            m_len = other.m_len;
            other.m_data = nullptr;
            other.m_len = 0;
        }

        ~string() { webcc::free(m_data); }

        template <typename... Args>
        static string concat(Args... args)
        {
            // 1. We use a Formatter on the stack to build the string first
            // This avoids multiple heap allocations
            webcc::Formatter<1024> temp;
            (temp << ... << args); // C++17 Fold Expression

            // 2. Now we allocate the exact size needed once
            return string(temp.c_str());
        }

        const char *c_str() const { return m_data ? m_data : ""; }
        uint32_t length() const { return m_len; }
        operator string_view() const { return string_view(m_data, m_len); }
        char operator[](uint32_t i) { return m_data[i]; }
    };
} // namespace webcc
