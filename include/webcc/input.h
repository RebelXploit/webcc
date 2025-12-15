#pragma once
#include "webcc.h"

namespace webcc::input {
    enum OpCode {
        OP_INIT_KEYBOARD = 0x2c,
        OP_INIT_MOUSE = 0x2d,
        OP_REQUEST_POINTER_LOCK = 0x2e,
        OP_EXIT_POINTER_LOCK = 0x2f
    };

    inline void init_keyboard(){
        push_command((uint8_t)OP_INIT_KEYBOARD);
    }

    inline void init_mouse(int32_t handle){
        push_command((uint8_t)OP_INIT_MOUSE);
        push_data<int32_t>(handle);
    }

    inline void request_pointer_lock(int32_t handle){
        push_command((uint8_t)OP_REQUEST_POINTER_LOCK);
        push_data<int32_t>(handle);
    }

    inline void exit_pointer_lock(){
        push_command((uint8_t)OP_EXIT_POINTER_LOCK);
    }

} // namespace webcc::input

