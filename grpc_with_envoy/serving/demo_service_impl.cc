// Copyright 2018 ASLP@NPU.  All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: ASLP@NPU

#include "grpc_with_envoy/serving/demo_service_impl.h"

#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

#include "glog/logging.h"

namespace grpc_with_envoy {
namespace serving {

using Callback = std::function<bool(const void* value, size_t size)>;

static const int kBufferSize = 64 * 1024;

static bool ReadFile(const std::string& filename, Callback callback) {
  std::ifstream input(filename, std::ifstream::binary);
  if (!input)
    return false;
  int byte_read = 0;
  char buffer[kBufferSize];
  while (!input.eof()) {
    input.read(buffer, kBufferSize);
    byte_read = input.gcount();
    if (!callback(buffer, byte_read)) {
      LOG(INFO) << "Callback failed";
      return false;
    }
    LOG(INFO) << "Send " << byte_read << " bytes";
    usleep(100 * 1000);
  }
  input.close();
  return true;
}

::grpc::Status DemoServiceImpl::GetSomething(
    ::grpc::ServerContext* context,
    const GetRequest* request,
    ::grpc::ServerWriter<::google::api::HttpBody>* writer) {
  auto filename = request->filename();
  LOG(INFO) << "Get audio from grpc server: " << filename;

  std::string extension = filename.substr(filename.find_last_of(".") + 1);
  std::string content_type;
  if (extension == "mp3")
    content_type = "audio/mp3";
  else if (extension == "wav")
    content_type = "audio/wav";
  else
    content_type = "application/json";
  LOG(INFO) << content_type;

  bool ok = ReadFile(filename, [&](const void* value, size_t size) -> bool {
    ::google::api::HttpBody reply;
    reply.set_content_type(content_type);
    reply.set_data(value, size);
    return writer->Write(reply);
  });

  if (!ok)
    return ::grpc::Status::CANCELLED;
  else
    return ::grpc::Status::OK;
}

}  // namespace serving
}  // namespace grpc_with_envoy
