#pragma once
#include <stdint.h>
#include <stddef.h>

namespace webcc
{
    // The linker provides this symbol to mark the start of free RAM
    extern "C" uint8_t __heap_base;

    // We use a pointer to keep track of the next free address
    inline uintptr_t heap_ptr = (uintptr_t)&__heap_base;

    // Simple Free List Allocator
    struct BlockHeader {
        size_t size;
        BlockHeader* next;
    };

    inline BlockHeader* free_list = nullptr;

    inline void *malloc(size_t size)
    {
        if (size == 0) return nullptr;

        // Align to 8 bytes
        size = (size + 7) & ~7;
        
        // Total size needed including header
        size_t total_size = size + sizeof(BlockHeader);

        // 1. Check free list for a suitable block
        BlockHeader* prev = nullptr;
        BlockHeader* curr = free_list;
        
        while (curr) {
            if (curr->size >= size) { // Found a block big enough
                // Unlink from list
                if (prev) prev->next = curr->next;
                else free_list = curr->next;
                
                // Return pointer to data (after header)
                return (void*)((uint8_t*)curr + sizeof(BlockHeader));
            }
            prev = curr;
            curr = curr->next;
        }

        // 2. Allocate from heap if no free block found
        uintptr_t current = heap_ptr;
        heap_ptr += total_size;

        // Check current WASM memory limit
        size_t current_pages = __builtin_wasm_memory_size(0);
        uintptr_t max_mem = current_pages * 64 * 1024;

        // If we've exceeded current memory, grow it
        if (heap_ptr > max_mem)
        {
            size_t bytes_needed = heap_ptr - max_mem;
            size_t pages_to_add = (bytes_needed + 65535) / 65536;

            if (__builtin_wasm_memory_grow(0, pages_to_add) == -1)
            {
                heap_ptr = current; // Reset pointer
                return nullptr;
            }
        }

        BlockHeader* header = (BlockHeader*)current;
        header->size = size;
        header->next = nullptr;

        return (void*)((uint8_t*)header + sizeof(BlockHeader));
    }

    inline void free(void *ptr)
    {
        if (!ptr) return;
        
        // Get header
        BlockHeader* header = (BlockHeader*)((uint8_t*)ptr - sizeof(BlockHeader));
        
        // Add to front of free list
        header->next = free_list;
        free_list = header;
    }
} // namespace webcc