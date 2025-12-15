#pragma once

#include <stdint.h>
#include <stddef.h>
#include "../../src/command_buffer.h"

namespace webcc{

    // Simple strlen for WASM
    static inline size_t strlen(const char* s) {
        size_t len = 0;
        while (s[len]) ++len;
        return len;
    }

    // The trigger. This calls a JS function (imported)
    void flush();

    // Internal helpers for command serialization
    template<typename T>
    inline void push_data(T value){
#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#error "This code assumes a little-endian host. Add explicit byte-order conversions for big-endian hosts."
#endif
        uint8_t buf[sizeof(T)];
        uint8_t* src = reinterpret_cast<uint8_t*>(&value);
        for(size_t i = 0; i < sizeof(T); ++i) buf[i] = src[i];
        CommandBuffer::push_bytes(buf, sizeof(T));
    }

    inline void push_command(uint8_t opcode){
        CommandBuffer::push_byte(opcode);
    }
}
