#pragma once
#include <stddef.h>

// Placement new operators for nostdlib environments
// 
// These operators don't allocate memory - they just return the pointer you give them.
// The actual object construction is handled by compiler-generated code.
// 
// Usage: ::new (buffer) T(args);
//   - Constructs object T at the address 'buffer' (which you already allocated)
//   - The operator new function below just returns 'buffer' unchanged
//   - The compiler then generates code to call T's constructor at that address
//
// The delete operators are only called if a constructor throws an exception.
// They're empty because placement new doesn't allocate, so there's nothing to free.

// Placement new
inline void* operator new(size_t, void* p) noexcept { return p; }

// Placement delete (called if constructor throws exception)
inline void operator delete(void*, void*) noexcept { }

// Array versions 
inline void* operator new[](size_t, void* p) noexcept { return p; }
inline void operator delete[](void*, void*) noexcept { }