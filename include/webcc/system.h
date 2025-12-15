#pragma once
#include "webcc.h"

namespace webcc::system {
    enum OpCode {
        OP_LOG = 0x2f,
        OP_WARN = 0x30,
        OP_ERROR = 0x31,
        OP_SET_MAIN_LOOP = 0x32,
        OP_SET_TITLE = 0x33,
        OP_RELOAD = 0x34,
        OP_OPEN_URL = 0x35,
        OP_REQUEST_FULLSCREEN = 0x36
    };

    inline void log(const char* msg){
        push_command((uint8_t)OP_LOG);
        { uint32_t len = strlen(msg); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)msg, len); }
    }

    inline void warn(const char* msg){
        push_command((uint8_t)OP_WARN);
        { uint32_t len = strlen(msg); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)msg, len); }
    }

    inline void error(const char* msg){
        push_command((uint8_t)OP_ERROR);
        { uint32_t len = strlen(msg); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)msg, len); }
    }

    inline void set_main_loop(const char* func_name){
        push_command((uint8_t)OP_SET_MAIN_LOOP);
        { uint32_t len = strlen(func_name); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)func_name, len); }
    }

    inline void set_title(const char* title){
        push_command((uint8_t)OP_SET_TITLE);
        { uint32_t len = strlen(title); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)title, len); }
    }

    inline void reload(){
        push_command((uint8_t)OP_RELOAD);
    }

    inline void open_url(const char* url){
        push_command((uint8_t)OP_OPEN_URL);
        { uint32_t len = strlen(url); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)url, len); }
    }

    inline void request_fullscreen(const char* id){
        push_command((uint8_t)OP_REQUEST_FULLSCREEN);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

} // namespace webcc::system

