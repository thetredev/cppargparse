FROM debian:11.7-slim

RUN apt-get -y update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        git \
        cmake \
        ninja-build \
        lcov \
        doxygen \
        python3 \
    && apt-get clean \
    && rm -rf /var/cache/apt/lists/*
