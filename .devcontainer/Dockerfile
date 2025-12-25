FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

# Install additional packages
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    clang \
    lldb \
    llvm \
    python3 \
    && apt-get clean -y && rm -rf /var/lib/apt/lists/*
