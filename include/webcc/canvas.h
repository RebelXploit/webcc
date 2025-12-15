#pragma once
#include "webcc.h"

namespace webcc::canvas {
    enum OpCode {
        OP_CREATE_CANVAS = 0xa,
        OP_SET_SIZE = 0xb,
        OP_SET_FILL_STYLE = 0xc,
        OP_SET_FILL_STYLE_STR = 0xd,
        OP_FILL_RECT = 0xe,
        OP_CLEAR_RECT = 0xf,
        OP_STROKE_RECT = 0x10,
        OP_SET_STROKE_STYLE = 0x11,
        OP_SET_STROKE_STYLE_STR = 0x12,
        OP_SET_LINE_WIDTH = 0x13,
        OP_BEGIN_PATH = 0x14,
        OP_CLOSE_PATH = 0x15,
        OP_MOVE_TO = 0x16,
        OP_LINE_TO = 0x17,
        OP_STROKE = 0x18,
        OP_FILL = 0x19,
        OP_ARC = 0x1a,
        OP_FILL_TEXT = 0x1b,
        OP_FILL_TEXT_F = 0x1c,
        OP_FILL_TEXT_I = 0x1d,
        OP_SET_FONT = 0x1e,
        OP_SET_TEXT_ALIGN = 0x1f,
        OP_DRAW_IMAGE = 0x20,
        OP_TRANSLATE = 0x21,
        OP_ROTATE = 0x22,
        OP_SCALE = 0x23,
        OP_SAVE = 0x24,
        OP_RESTORE = 0x25,
        OP_LOG_CANVAS_INFO = 0x26,
        OP_SET_GLOBAL_ALPHA = 0x27,
        OP_SET_LINE_CAP = 0x28,
        OP_SET_LINE_JOIN = 0x29,
        OP_SET_SHADOW = 0x2a
    };

    inline void create_canvas(const char* id, float width, float height){
        push_command((uint8_t)OP_CREATE_CANVAS);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(width);
        push_data<float>(height);
    }

    inline void set_size(const char* id, float width, float height){
        push_command((uint8_t)OP_SET_SIZE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(width);
        push_data<float>(height);
    }

    inline void set_fill_style(const char* id, uint8_t r, uint8_t g, uint8_t b){
        push_command((uint8_t)OP_SET_FILL_STYLE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<uint8_t>(r);
        push_data<uint8_t>(g);
        push_data<uint8_t>(b);
    }

    inline void set_fill_style_str(const char* id, const char* color){
        push_command((uint8_t)OP_SET_FILL_STYLE_STR);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(color); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)color, len); }
    }

    inline void fill_rect(const char* id, float x, float y, float w, float h){
        push_command((uint8_t)OP_FILL_RECT);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(x);
        push_data<float>(y);
        push_data<float>(w);
        push_data<float>(h);
    }

    inline void clear_rect(const char* id, float x, float y, float w, float h){
        push_command((uint8_t)OP_CLEAR_RECT);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(x);
        push_data<float>(y);
        push_data<float>(w);
        push_data<float>(h);
    }

    inline void stroke_rect(const char* id, float x, float y, float w, float h){
        push_command((uint8_t)OP_STROKE_RECT);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(x);
        push_data<float>(y);
        push_data<float>(w);
        push_data<float>(h);
    }

    inline void set_stroke_style(const char* id, uint8_t r, uint8_t g, uint8_t b){
        push_command((uint8_t)OP_SET_STROKE_STYLE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<uint8_t>(r);
        push_data<uint8_t>(g);
        push_data<uint8_t>(b);
    }

    inline void set_stroke_style_str(const char* id, const char* color){
        push_command((uint8_t)OP_SET_STROKE_STYLE_STR);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(color); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)color, len); }
    }

    inline void set_line_width(const char* id, float width){
        push_command((uint8_t)OP_SET_LINE_WIDTH);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(width);
    }

    inline void begin_path(const char* id){
        push_command((uint8_t)OP_BEGIN_PATH);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void close_path(const char* id){
        push_command((uint8_t)OP_CLOSE_PATH);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void move_to(const char* id, float x, float y){
        push_command((uint8_t)OP_MOVE_TO);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(x);
        push_data<float>(y);
    }

    inline void line_to(const char* id, float x, float y){
        push_command((uint8_t)OP_LINE_TO);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(x);
        push_data<float>(y);
    }

    inline void stroke(const char* id){
        push_command((uint8_t)OP_STROKE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void fill(const char* id){
        push_command((uint8_t)OP_FILL);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void arc(const char* id, float x, float y, float radius, float start_angle, float end_angle){
        push_command((uint8_t)OP_ARC);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(x);
        push_data<float>(y);
        push_data<float>(radius);
        push_data<float>(start_angle);
        push_data<float>(end_angle);
    }

    inline void fill_text(const char* id, const char* text, float x, float y){
        push_command((uint8_t)OP_FILL_TEXT);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(text); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)text, len); }
        push_data<float>(x);
        push_data<float>(y);
    }

    inline void fill_text_f(const char* id, const char* fmt, float val, float x, float y){
        push_command((uint8_t)OP_FILL_TEXT_F);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(fmt); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)fmt, len); }
        push_data<float>(val);
        push_data<float>(x);
        push_data<float>(y);
    }

    inline void fill_text_i(const char* id, const char* fmt, int32_t val, float x, float y){
        push_command((uint8_t)OP_FILL_TEXT_I);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(fmt); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)fmt, len); }
        push_data<int32_t>(val);
        push_data<float>(x);
        push_data<float>(y);
    }

    inline void set_font(const char* id, const char* font){
        push_command((uint8_t)OP_SET_FONT);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(font); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)font, len); }
    }

    inline void set_text_align(const char* id, const char* align){
        push_command((uint8_t)OP_SET_TEXT_ALIGN);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(align); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)align, len); }
    }

    inline void draw_image(const char* id, const char* img_id, float x, float y){
        push_command((uint8_t)OP_DRAW_IMAGE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(img_id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)img_id, len); }
        push_data<float>(x);
        push_data<float>(y);
    }

    inline void translate(const char* id, float x, float y){
        push_command((uint8_t)OP_TRANSLATE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(x);
        push_data<float>(y);
    }

    inline void rotate(const char* id, float angle){
        push_command((uint8_t)OP_ROTATE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(angle);
    }

    inline void scale(const char* id, float x, float y){
        push_command((uint8_t)OP_SCALE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(x);
        push_data<float>(y);
    }

    inline void save(const char* id){
        push_command((uint8_t)OP_SAVE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void restore(const char* id){
        push_command((uint8_t)OP_RESTORE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void log_canvas_info(const char* id){
        push_command((uint8_t)OP_LOG_CANVAS_INFO);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void set_global_alpha(const char* id, float alpha){
        push_command((uint8_t)OP_SET_GLOBAL_ALPHA);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(alpha);
    }

    inline void set_line_cap(const char* id, const char* cap){
        push_command((uint8_t)OP_SET_LINE_CAP);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(cap); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)cap, len); }
    }

    inline void set_line_join(const char* id, const char* join){
        push_command((uint8_t)OP_SET_LINE_JOIN);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(join); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)join, len); }
    }

    inline void set_shadow(const char* id, float blur, float off_x, float off_y, const char* color){
        push_command((uint8_t)OP_SET_SHADOW);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(blur);
        push_data<float>(off_x);
        push_data<float>(off_y);
        { uint32_t len = strlen(color); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)color, len); }
    }

} // namespace webcc::canvas

