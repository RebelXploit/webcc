#pragma once
#include "webcc.h"

namespace webcc::webgl {
    enum OpCode {
        OP_CREATE_CONTEXT = 0x45,
        OP_CLEAR_COLOR = 0x46,
        OP_CLEAR = 0x47,
        OP_CREATE_SHADER = 0x48,
        OP_CREATE_PROGRAM = 0x49,
        OP_ATTACH_SHADER = 0x4a,
        OP_LINK_PROGRAM = 0x4b,
        OP_BIND_ATTRIB_LOCATION = 0x4c,
        OP_USE_PROGRAM = 0x4d,
        OP_CREATE_BUFFER = 0x4e,
        OP_BIND_BUFFER = 0x4f,
        OP_BUFFER_DATA = 0x50,
        OP_ENABLE_VERTEX_ATTRIB_ARRAY = 0x51,
        OP_ENABLE = 0x52,
        OP_UNIFORM_1F = 0x53,
        OP_VERTEX_ATTRIB_POINTER = 0x54,
        OP_DRAW_ARRAYS = 0x55
    };

    inline void create_context(const char* id, const char* canvas_id){
        push_command((uint8_t)OP_CREATE_CONTEXT);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(canvas_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)canvas_id, len); }
    }

    inline void clear_color(const char* id, float r, float g, float b, float a){
        push_command((uint8_t)OP_CLEAR_COLOR);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(r);
        push_data<float>(g);
        push_data<float>(b);
        push_data<float>(a);
    }

    inline void clear(const char* id, uint32_t mask){
        push_command((uint8_t)OP_CLEAR);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<uint32_t>(mask);
    }

    inline void create_shader(const char* ctx_id, const char* shader_id, uint32_t type, const char* source){
        push_command((uint8_t)OP_CREATE_SHADER);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        { uint32_t len = strlen(shader_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)shader_id, len); }
        push_data<uint32_t>(type);
        { uint32_t len = strlen(source); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)source, len); }
    }

    inline void create_program(const char* ctx_id, const char* prog_id){
        push_command((uint8_t)OP_CREATE_PROGRAM);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        { uint32_t len = strlen(prog_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)prog_id, len); }
    }

    inline void attach_shader(const char* ctx_id, const char* prog_id, const char* shader_id){
        push_command((uint8_t)OP_ATTACH_SHADER);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        { uint32_t len = strlen(prog_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)prog_id, len); }
        { uint32_t len = strlen(shader_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)shader_id, len); }
    }

    inline void link_program(const char* ctx_id, const char* prog_id){
        push_command((uint8_t)OP_LINK_PROGRAM);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        { uint32_t len = strlen(prog_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)prog_id, len); }
    }

    inline void bind_attrib_location(const char* ctx_id, const char* prog_id, uint32_t index, const char* name){
        push_command((uint8_t)OP_BIND_ATTRIB_LOCATION);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        { uint32_t len = strlen(prog_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)prog_id, len); }
        push_data<uint32_t>(index);
        { uint32_t len = strlen(name); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)name, len); }
    }

    inline void use_program(const char* ctx_id, const char* prog_id){
        push_command((uint8_t)OP_USE_PROGRAM);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        { uint32_t len = strlen(prog_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)prog_id, len); }
    }

    inline void create_buffer(const char* ctx_id, const char* buf_id){
        push_command((uint8_t)OP_CREATE_BUFFER);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        { uint32_t len = strlen(buf_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)buf_id, len); }
    }

    inline void bind_buffer(const char* ctx_id, uint32_t target, const char* buf_id){
        push_command((uint8_t)OP_BIND_BUFFER);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        push_data<uint32_t>(target);
        { uint32_t len = strlen(buf_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)buf_id, len); }
    }

    inline void buffer_data(const char* ctx_id, uint32_t target, uint32_t data_ptr, uint32_t data_len, uint32_t usage){
        push_command((uint8_t)OP_BUFFER_DATA);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        push_data<uint32_t>(target);
        push_data<uint32_t>(data_ptr);
        push_data<uint32_t>(data_len);
        push_data<uint32_t>(usage);
    }

    inline void enable_vertex_attrib_array(const char* ctx_id, uint32_t index){
        push_command((uint8_t)OP_ENABLE_VERTEX_ATTRIB_ARRAY);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        push_data<uint32_t>(index);
    }

    inline void enable(const char* ctx_id, uint32_t cap){
        push_command((uint8_t)OP_ENABLE);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        push_data<uint32_t>(cap);
    }

    inline void uniform_1f(const char* ctx_id, const char* prog_id, const char* name, float val){
        push_command((uint8_t)OP_UNIFORM_1F);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        { uint32_t len = strlen(prog_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)prog_id, len); }
        { uint32_t len = strlen(name); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)name, len); }
        push_data<float>(val);
    }

    inline void vertex_attrib_pointer(const char* ctx_id, uint32_t index, int32_t size, uint32_t type, uint8_t normalized, int32_t stride, int32_t offset){
        push_command((uint8_t)OP_VERTEX_ATTRIB_POINTER);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        push_data<uint32_t>(index);
        push_data<int32_t>(size);
        push_data<uint32_t>(type);
        push_data<uint8_t>(normalized);
        push_data<int32_t>(stride);
        push_data<int32_t>(offset);
    }

    inline void draw_arrays(const char* ctx_id, uint32_t mode, int32_t first, int32_t count){
        push_command((uint8_t)OP_DRAW_ARRAYS);
        { uint32_t len = strlen(ctx_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)ctx_id, len); }
        push_data<uint32_t>(mode);
        push_data<int32_t>(first);
        push_data<int32_t>(count);
    }

} // namespace webcc::webgl

