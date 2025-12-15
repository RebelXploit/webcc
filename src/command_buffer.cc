#include "command_buffer.h"

namespace webcc {

namespace {
    constexpr size_t MAX_BUFFER_SIZE = 1024 * 1024; // 1MB
    static uint8_t g_buffer[MAX_BUFFER_SIZE];
    static size_t g_offset = 0;
}

void CommandBuffer::push_byte(uint8_t b){
    if (g_offset < MAX_BUFFER_SIZE) {
        g_buffer[g_offset++] = b;
    }
}

void CommandBuffer::push_bytes(const uint8_t* data, size_t len){
    if(!data || len==0) return;
    if (g_offset + len <= MAX_BUFFER_SIZE) {
        for(size_t i=0; i<len; ++i) {
            g_buffer[g_offset++] = data[i];
        }
    }
}

const uint8_t* CommandBuffer::data(){
    return g_buffer;
}

size_t CommandBuffer::size(){
    return g_offset;
}

void CommandBuffer::reset(){
    g_offset = 0;
}

} // namespace webcc

#ifdef __wasm__
// Import for WASM
extern "C" void webcc_js_flush(uintptr_t ptr, size_t size);
#else
// Stub for native build (webcc tool)
extern "C" void webcc_js_flush(uintptr_t ptr, size_t size) {}
#endif

namespace webcc {
    void flush() {
        size_t s = CommandBuffer::size();
        if (s == 0) return;
        webcc_js_flush(reinterpret_cast<uintptr_t>(CommandBuffer::data()), s);
        CommandBuffer::reset();
    }
}


