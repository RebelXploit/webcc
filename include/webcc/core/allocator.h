#pragma once
#include <stdint.h>
#include <stddef.h>

namespace webcc
{
    // The linker provides this symbol to mark the start of free RAM
    extern "C" uint8_t __heap_base;

    // We use a pointer to keep track of the next free address
    static uintptr_t heap_ptr = (uintptr_t)&__heap_base;

    inline void *malloc(size_t size)
    {
        if (size == 0)
            return nullptr;

        // 1. Align to 8 bytes
        size = (size + 7) & ~7;

        uintptr_t current = heap_ptr;
        heap_ptr += size;

        // 2. Check current WASM memory limit
        // __builtin_wasm_memory_size returns size in 64KB Pages
        size_t current_pages = __builtin_wasm_memory_size(0);
        uintptr_t max_mem = current_pages * 64 * 1024;

        // 3. If we've exceeded current memory, grow it
        if (heap_ptr > max_mem)
        {
            size_t bytes_needed = heap_ptr - max_mem;
            // WASM pages are 64KiB.
            size_t pages_to_add = (bytes_needed + 65535) / 65536;

            if (__builtin_wasm_memory_grow(0, pages_to_add) == -1)
            {
                // Memory growth failed
                heap_ptr = current; // Reset pointer
                return nullptr;
            }
        }
        return (void *)current;
    }

    inline void free(void *ptr)
    {
        // In a "Bump allocator", we dont free indivitual items.
        // This is extremly common in WASM games/apps for speed.
    }
} // namespace webcc