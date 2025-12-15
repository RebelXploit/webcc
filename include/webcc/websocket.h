#pragma once
#include "webcc.h"

namespace webcc::websocket {
    enum OpCode {
        OP_CREATE = 0x42,
        OP_SEND = 0x43,
        OP_CLOSE = 0x44
    };

    inline void create(const char* id, const char* url){
        push_command((uint8_t)OP_CREATE);
        webcc::CommandBuffer::push_string(id, strlen(id));
        webcc::CommandBuffer::push_string(url, strlen(url));
    }

    inline void send(const char* id, const char* msg){
        push_command((uint8_t)OP_SEND);
        webcc::CommandBuffer::push_string(id, strlen(id));
        webcc::CommandBuffer::push_string(msg, strlen(msg));
    }

    inline void close(const char* id){
        push_command((uint8_t)OP_CLOSE);
        webcc::CommandBuffer::push_string(id, strlen(id));
    }

} // namespace webcc::websocket

