#pragma once
#include "webcc.h"

namespace webcc::webgl {
    enum OpCode {
        OP_CREATE_CONTEXT = 0x46,
        OP_CLEAR_COLOR = 0x47,
        OP_CLEAR = 0x48,
        OP_CREATE_SHADER = 0x49,
        OP_CREATE_PROGRAM = 0x4a,
        OP_ATTACH_SHADER = 0x4b,
        OP_LINK_PROGRAM = 0x4c,
        OP_BIND_ATTRIB_LOCATION = 0x4d,
        OP_USE_PROGRAM = 0x4e,
        OP_CREATE_BUFFER = 0x4f,
        OP_BIND_BUFFER = 0x50,
        OP_BUFFER_DATA = 0x51,
        OP_ENABLE_VERTEX_ATTRIB_ARRAY = 0x52,
        OP_ENABLE = 0x53,
        OP_UNIFORM_1F = 0x54,
        OP_VERTEX_ATTRIB_POINTER = 0x55,
        OP_DRAW_ARRAYS = 0x56
    };

    inline void create_context(const char* id, int32_t canvas_handle){
        push_command((uint8_t)OP_CREATE_CONTEXT);
        webcc::CommandBuffer::push_string(id, strlen(id));
        push_data<int32_t>(canvas_handle);
    }

    inline void clear_color(const char* id, float r, float g, float b, float a){
        push_command((uint8_t)OP_CLEAR_COLOR);
        webcc::CommandBuffer::push_string(id, strlen(id));
        push_data<float>(r);
        push_data<float>(g);
        push_data<float>(b);
        push_data<float>(a);
    }

    inline void clear(const char* id, uint32_t mask){
        push_command((uint8_t)OP_CLEAR);
        webcc::CommandBuffer::push_string(id, strlen(id));
        push_data<uint32_t>(mask);
    }

    inline void create_shader(const char* ctx_id, const char* shader_id, uint32_t type, const char* source){
        push_command((uint8_t)OP_CREATE_SHADER);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        webcc::CommandBuffer::push_string(shader_id, strlen(shader_id));
        push_data<uint32_t>(type);
        webcc::CommandBuffer::push_string(source, strlen(source));
    }

    inline void create_program(const char* ctx_id, const char* prog_id){
        push_command((uint8_t)OP_CREATE_PROGRAM);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        webcc::CommandBuffer::push_string(prog_id, strlen(prog_id));
    }

    inline void attach_shader(const char* ctx_id, const char* prog_id, const char* shader_id){
        push_command((uint8_t)OP_ATTACH_SHADER);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        webcc::CommandBuffer::push_string(prog_id, strlen(prog_id));
        webcc::CommandBuffer::push_string(shader_id, strlen(shader_id));
    }

    inline void link_program(const char* ctx_id, const char* prog_id){
        push_command((uint8_t)OP_LINK_PROGRAM);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        webcc::CommandBuffer::push_string(prog_id, strlen(prog_id));
    }

    inline void bind_attrib_location(const char* ctx_id, const char* prog_id, uint32_t index, const char* name){
        push_command((uint8_t)OP_BIND_ATTRIB_LOCATION);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        webcc::CommandBuffer::push_string(prog_id, strlen(prog_id));
        push_data<uint32_t>(index);
        webcc::CommandBuffer::push_string(name, strlen(name));
    }

    inline void use_program(const char* ctx_id, const char* prog_id){
        push_command((uint8_t)OP_USE_PROGRAM);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        webcc::CommandBuffer::push_string(prog_id, strlen(prog_id));
    }

    inline void create_buffer(const char* ctx_id, const char* buf_id){
        push_command((uint8_t)OP_CREATE_BUFFER);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        webcc::CommandBuffer::push_string(buf_id, strlen(buf_id));
    }

    inline void bind_buffer(const char* ctx_id, uint32_t target, const char* buf_id){
        push_command((uint8_t)OP_BIND_BUFFER);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        push_data<uint32_t>(target);
        webcc::CommandBuffer::push_string(buf_id, strlen(buf_id));
    }

    inline void buffer_data(const char* ctx_id, uint32_t target, uint32_t data_ptr, uint32_t data_len, uint32_t usage){
        push_command((uint8_t)OP_BUFFER_DATA);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        push_data<uint32_t>(target);
        push_data<uint32_t>(data_ptr);
        push_data<uint32_t>(data_len);
        push_data<uint32_t>(usage);
    }

    inline void enable_vertex_attrib_array(const char* ctx_id, uint32_t index){
        push_command((uint8_t)OP_ENABLE_VERTEX_ATTRIB_ARRAY);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        push_data<uint32_t>(index);
    }

    inline void enable(const char* ctx_id, uint32_t cap){
        push_command((uint8_t)OP_ENABLE);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        push_data<uint32_t>(cap);
    }

    inline void uniform_1f(const char* ctx_id, const char* prog_id, const char* name, float val){
        push_command((uint8_t)OP_UNIFORM_1F);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        webcc::CommandBuffer::push_string(prog_id, strlen(prog_id));
        webcc::CommandBuffer::push_string(name, strlen(name));
        push_data<float>(val);
    }

    inline void vertex_attrib_pointer(const char* ctx_id, uint32_t index, int32_t size, uint32_t type, uint8_t normalized, int32_t stride, int32_t offset){
        push_command((uint8_t)OP_VERTEX_ATTRIB_POINTER);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        push_data<uint32_t>(index);
        push_data<int32_t>(size);
        push_data<uint32_t>(type);
        push_data<uint8_t>(normalized);
        push_data<int32_t>(stride);
        push_data<int32_t>(offset);
    }

    inline void draw_arrays(const char* ctx_id, uint32_t mode, int32_t first, int32_t count){
        push_command((uint8_t)OP_DRAW_ARRAYS);
        webcc::CommandBuffer::push_string(ctx_id, strlen(ctx_id));
        push_data<uint32_t>(mode);
        push_data<int32_t>(first);
        push_data<int32_t>(count);
    }

} // namespace webcc::webgl

