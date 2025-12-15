#pragma once
#include "webcc.h"

namespace webcc::input {
    enum OpCode {
        OP_INIT_KEYBOARD = 0x2b,
        OP_INIT_MOUSE = 0x2c,
        OP_REQUEST_POINTER_LOCK = 0x2d,
        OP_EXIT_POINTER_LOCK = 0x2e
    };

    inline void init_keyboard(){
        push_command((uint8_t)OP_INIT_KEYBOARD);
    }

    inline void init_mouse(const char* element_id){
        push_command((uint8_t)OP_INIT_MOUSE);
        { uint32_t len = strlen(element_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)element_id, len); }
    }

    inline void request_pointer_lock(const char* id){
        push_command((uint8_t)OP_REQUEST_POINTER_LOCK);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void exit_pointer_lock(){
        push_command((uint8_t)OP_EXIT_POINTER_LOCK);
    }

} // namespace webcc::input

