#pragma once
#include "webcc.h"

namespace webcc::dom {
    enum OpCode {
        OP_CREATE_ELEMENT = 0x1,
        OP_SET_ATTRIBUTE = 0x2,
        OP_GET_ATTRIBUTE = 0x3,
        OP_APPEND_CHILD = 0x4,
        OP_REMOVE_ELEMENT = 0x5,
        OP_SET_INNER_HTML = 0x6,
        OP_SET_INNER_TEXT = 0x7,
        OP_ADD_CLASS = 0x8,
        OP_REMOVE_CLASS = 0x9
    };

    inline void create_element(const char* id, const char* tag){
        push_command((uint8_t)OP_CREATE_ELEMENT);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(tag); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)tag, len); }
    }

    inline void set_attribute(const char* id, const char* name, const char* value){
        push_command((uint8_t)OP_SET_ATTRIBUTE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(name); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)name, len); }
        { uint32_t len = strlen(value); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)value, len); }
    }

    inline void get_attribute(const char* id, const char* name){
        push_command((uint8_t)OP_GET_ATTRIBUTE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(name); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)name, len); }
    }

    inline void append_child(const char* parent_id, const char* child_id){
        push_command((uint8_t)OP_APPEND_CHILD);
        { uint32_t len = strlen(parent_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)parent_id, len); }
        { uint32_t len = strlen(child_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)child_id, len); }
    }

    inline void remove_element(const char* id){
        push_command((uint8_t)OP_REMOVE_ELEMENT);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void set_inner_html(const char* id, const char* html){
        push_command((uint8_t)OP_SET_INNER_HTML);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(html); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)html, len); }
    }

    inline void set_inner_text(const char* id, const char* text){
        push_command((uint8_t)OP_SET_INNER_TEXT);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(text); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)text, len); }
    }

    inline void add_class(const char* id, const char* cls){
        push_command((uint8_t)OP_ADD_CLASS);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(cls); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)cls, len); }
    }

    inline void remove_class(const char* id, const char* cls){
        push_command((uint8_t)OP_REMOVE_CLASS);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(cls); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)cls, len); }
    }

} // namespace webcc::dom

