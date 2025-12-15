#pragma once
#include "webcc.h"

namespace webcc::websocket {
    enum OpCode {
        OP_CREATE = 0x41,
        OP_SEND = 0x42,
        OP_CLOSE = 0x43
    };

    inline void create(const char* id, const char* url){
        push_command((uint8_t)OP_CREATE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(url); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)url, len); }
    }

    inline void send(const char* id, const char* msg){
        push_command((uint8_t)OP_SEND);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(msg); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)msg, len); }
    }

    inline void close(const char* id){
        push_command((uint8_t)OP_CLOSE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

} // namespace webcc::websocket

