FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    valgrind \
    clang-format \
    cmake \
    vim \
    git \
    && apt-get clean

# 작업 디렉토리
WORKDIR /workspace
