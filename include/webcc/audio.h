#pragma once
#include "webcc.h"

namespace webcc::audio {
    enum OpCode {
        OP_CREATE_AUDIO = 0x3a,
        OP_PLAY = 0x3b,
        OP_PAUSE = 0x3c,
        OP_SET_VOLUME = 0x3d,
        OP_SET_LOOP = 0x3e,
        OP_GET_CURRENT_TIME = 0x3f,
        OP_GET_DURATION = 0x40
    };

    inline void create_audio(const char* id, const char* src){
        push_command((uint8_t)OP_CREATE_AUDIO);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        { uint32_t len = strlen(src); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)src, len); }
    }

    inline void play(const char* id){
        push_command((uint8_t)OP_PLAY);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void pause(const char* id){
        push_command((uint8_t)OP_PAUSE);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
    }

    inline void set_volume(const char* id, float vol){
        push_command((uint8_t)OP_SET_VOLUME);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<float>(vol);
    }

    inline void set_loop(const char* id, uint8_t loop){
        push_command((uint8_t)OP_SET_LOOP);
        { uint32_t len = strlen(id); push_data<uint32_t>(len); webcc::CommandBuffer::push_bytes((const uint8_t*)id, len); }
        push_data<uint8_t>(loop);
    }

    extern "C" float webcc_audio_get_current_time(const char* id, uint32_t id_len);
    inline float get_current_time(const char* id){
        return webcc_audio_get_current_time(id, strlen(id));
    }

    extern "C" float webcc_audio_get_duration(const char* id, uint32_t id_len);
    inline float get_duration(const char* id){
        return webcc_audio_get_duration(id, strlen(id));
    }

} // namespace webcc::audio

