#pragma once
#include "webcc.h"

namespace webcc::storage {
    enum OpCode {
        OP_SET_ITEM = 0x37,
        OP_REMOVE_ITEM = 0x38,
        OP_CLEAR = 0x39
    };

    inline void set_item(const char* key, const char* value){
        push_command((uint8_t)OP_SET_ITEM);
        { uint32_t len = strlen(key); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)key, len); }
        { uint32_t len = strlen(value); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)value, len); }
    }

    inline void remove_item(const char* key){
        push_command((uint8_t)OP_REMOVE_ITEM);
        { uint32_t len = strlen(key); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)key, len); }
    }

    inline void clear(){
        push_command((uint8_t)OP_CLEAR);
    }

} // namespace webcc::storage

