# Architecture

WebCC works by serializing API calls into a linear memory buffer (the **Command Buffer**). When you call a function like `webcc::canvas::fill_rect`, it writes a compact binary opcode and its arguments to this buffer.

When `webcc::flush()` is called, the buffer is passed to the JavaScript runtime, which decodes the commands and executes the corresponding Web APIs in a tight loop. This batching approach significantly reduces the overhead of crossing the WebAssembly/JavaScript boundary.

> **Note**: Functions that return a value (e.g., `create_element`) are implemented as **direct WASM imports** (synchronous calls). To ensure correct execution order, they automatically trigger a `flush()` before running, ensuring all pending buffered commands are executed first.

## Event System
WebCC uses a secondary shared memory buffer for sending events (like mouse clicks, key presses, or WebSocket messages) from JavaScript to C++.
- **Zero-Copy**: Events are written directly into WASM memory by the JS runtime.
- **Polling**: The C++ application polls this buffer (e.g., once per frame) to process pending events.

## Schema Generation
The toolchain generates `src/cli/webcc_schema.h` which embeds command definitions directly into the binary. This avoids the need to parse `schema.def` at runtime.

## Compilation & Linking
WebCC acts as a wrapper around `clang++`. It:
1.  **Scans** your code to determine which Web APIs are used.
2.  **Generates** a tree-shaken `app.js` containing only the necessary JS glue code for the features you use.
3.  **Compiles** your C++ code to WebAssembly.
4.  **Caches** compiled object files in a `.webcc_cache` directory (located inside the output directory) to speed up subsequent builds.

## Resource Handles
To maximize performance, WebCC uses **integer handles** to reference resources (like DOM elements, Canvases, Audio objects, and WebGL programs).
- **Creation**: Functions like `create_element` or `create_canvas` return a unique `int` handle.
- **Usage**: Subsequent commands use this integer handle, avoiding expensive string lookups or map queries on the JavaScript side during hot code paths (like rendering loops).

## Easy Extensibility
The entire API surface is defined in a single configuration file: `schema.def`.
- **Format**: `NAMESPACE|TYPE|NAME|FUNC_NAME|ARG_TYPES|JS_ACTION`
- **Generation**: The `webcc` tool parses this file to automatically generate:
  1.  **C++ Headers**: Type-safe function prototypes (e.g., `webcc/canvas.h`).
  2.  **JavaScript Runtime**: The switch-case logic to execute commands in `app.js`.

To add a new Web API feature, simply add a line to `schema.def` and run `./build.sh` to regenerate the toolchain and headers.
