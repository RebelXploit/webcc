#!/bin/bash

set -e

# Clean up previous build artifacts to ensure a clean bootstrap
rm -f src/cli/webcc_schema.h

echo "[WebCC] 1/3 Compiling bootstrap compiler..."
# Compile without schema support first
g++ -std=c++20 -O3 -o webcc_bootstrap \
    src/cli/main.cc \
    src/cli/utils.cc \
    src/cli/schema.cc \
    src/cli/generators.cc \
    -I include -I src/cli -I src/core

echo "[WebCC] 2/3 Generating headers..."
# Use bootstrap compiler to generate headers and schema definition
./webcc_bootstrap --headers

echo "[WebCC] 3/3 Compiling final compiler..."
# Compile final version which will now include the generated webcc_schema.h
g++ -std=c++20 -O3 -o webcc \
    src/cli/main.cc \
    src/cli/utils.cc \
    src/cli/schema.cc \
    src/cli/generators.cc \
    -I include -I src/cli -I src/core

# Cleanup
rm webcc_bootstrap

echo "[WebCC] Done."

# Check if webcc is already linked correctly
if command -v webcc >/dev/null 2>&1 && [ "$(command -v webcc)" -ef "$PWD/webcc" ]; then
    echo "webcc is already configured in PATH."
    exit 0
fi

# Only offer install if /usr/local/bin exists (common on Linux/macOS)
if [ -d "/usr/local/bin" ]; then
    echo ""
    echo "To use 'webcc' from anywhere, it needs to be in your PATH."
    read -p "Would you like to create a symlink in /usr/local/bin? [y/N] " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        TARGET="/usr/local/bin/webcc"
        if [ -w /usr/local/bin ]; then
            ln -sf "$PWD/webcc" "$TARGET"
        else
            echo "Need sudo access to write to /usr/local/bin"
            sudo ln -sf "$PWD/webcc" "$TARGET"
        fi
        echo "Symlink created: $TARGET -> $PWD/webcc"
        echo "You can now use 'webcc' command from any directory."
    fi
fi
