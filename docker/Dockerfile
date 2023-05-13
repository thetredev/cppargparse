FROM debian:11.7-slim

RUN apt-get -y update \
    && apt-get install -y --no-install-recommends \
        ca-certificates \
        build-essential \
        git \
        cmake \
        ninja-build \
        doxygen \
        python3 \
        python3-pip \
    && apt-get clean \
    && rm -rf /var/cache/apt/lists/* \
    && pip3 install gcovr==6.0
