#pragma once
#include "webcc.h"

namespace webcc::image {
    enum OpCode {
        OP_LOAD = 0x44
    };

    inline void load(const char* id, const char* src){
        push_command((uint8_t)OP_LOAD);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(src); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)src, len); }
    }

} // namespace webcc::image

