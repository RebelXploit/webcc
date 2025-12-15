#pragma once
#include "webcc.h"

namespace webcc::image {
    enum OpCode {
        OP_LOAD = 0x45
    };

    extern "C" int32_t webcc_image_load(const char* src, uint32_t src_len);
    inline int32_t load(const char* src){
        return webcc_image_load(src, strlen(src));
    }

} // namespace webcc::image

