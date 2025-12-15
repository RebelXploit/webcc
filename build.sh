#!/bin/bash

set -e

echo "[WebCC] Building webcc tool..."
g++ -std=c++17 -O2 -o webcc/webcc \
    webcc/cli/webcc.cc \
    webcc/src/webcc.cc \
    webcc/src/command_buffer.cc \
    -I webcc/include

echo "[WebCC] Build complete: webcc/webcc"
