# Copyright 2018 ASLP@NPU.  All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Author: ASLP@NPU

FROM ubuntu:16.04

ARG MAKEFLAGS=-j8

RUN apt-get update && apt-get install -y --no-install-recommends \
        autoconf \
        automake \
        build-essential \
        cmake \
        curl \
        default-jdk \
        default-jre \
        git \
        libpcre3-dev \
        libssl-dev \
        make \
        pkg-config \
        python3 \
        python3-pip \
        vim \
        unzip \
        wget \
        zip && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install grpc with protobuf and gflags
RUN git clone -b v1.17.1 https://github.com/grpc/grpc /github/grpc && \
    cd /github/grpc && \
    git submodule update --init && \
    \
    cd third_party/cares/cares && \
    git fetch origin && \
    git checkout cares-1_13_0 && \
    cmake -H. -Bbuild -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build && \
    cmake --build build --target install && \
    cd ../../../ && \
    rm -rf third_party/cares/cares && \
    \
    cd third_party/zlib && \
    cmake -H. -Bbuild -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build && \
    cmake --build build --target install && \
    cd ../../ && \
    rm -rf third_party/zlib && \
    \
    cd third_party/protobuf && \
    cmake -H./cmake -Bbuild -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -Dprotobuf_BUILD_TESTS=OFF -Dprotobuf_BUILD_SHARED_LIBS=ON && \
    cmake --build build && \
    cmake --build build --target install && \
    ldconfig && \
    cd ../../ && \
    rm -rf third_party/protobuf && \
    \
    cmake -H. -Bbuild -G "Unix Makefiles" -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF \
        -DgRPC_PROTOBUF_PROVIDER=package -DgRPC_ZLIB_PROVIDER=package -DgRPC_CARES_PROVIDER=package \
        -DgRPC_SSL_PROVIDER=package -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build && \
    cmake --build build --target install && \
    \
    rm -rf /github/grpc

RUN pip3 install grpcio==1.17.1 grpcio-tools==1.17.1

# Install glog
RUN git clone -b v0.3.5 https://github.com/google/glog.git /github/glog && \
    cd /github/glog && \
    cmake -H. -Bbuild -G "Unix Makefiles" && \
    cmake --build build && \
    cmake --build build --target install && \
    rm -rf /github/glog

COPY . /grpc_with_envoy

RUN cd /grpc_with_envoy/third_party/googleapis && \
    make && \
    cd /grpc_with_envoy && \
    make

WORKDIR /grpc_with_envoy

EXPOSE 9090
CMD ["/grpc_with_envoy/build/bin/grpc_server"]
