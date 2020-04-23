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

FROM envoyproxy/envoy-dev:latest AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
       curl \
       unzip && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN curl -sSL https://github.com/protocolbuffers/protobuf/releases/download/v3.6.1/\
protoc-3.6.1-linux-x86_64.zip -o /tmp/protoc.zip && \
  cd /tmp && \
  unzip -qq protoc.zip && \
  cp /tmp/bin/protoc /usr/local/bin/protoc

COPY . /grpc_with_envoy

RUN mkdir /data && \
    protoc -I/grpc_with_envoy/grpc_with_envoy/proto \
        -I/grpc_with_envoy/third_party/googleapis \
        -I/grpc_with_envoy/third_party/protobuf/src \
        --include_imports \
        --include_source_info \
        --descriptor_set_out=/data/demo_service_definition.pb \
        demo_service.proto

FROM envoyproxy/envoy-dev:latest
COPY --from=build /data/demo_service_definition.pb  /data/demo_service_definition.pb

CMD /usr/local/bin/envoy -c /etc/envoy/envoy.yaml
