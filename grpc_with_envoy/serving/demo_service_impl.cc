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

::grpc::Status DemoServiceImpl::GetSomething(
    ::grpc::ServerContext* context,
    const GetRequest* request,
    ::google::api::HttpBody* reply) {
  auto wav_filename = request->filename();
  LOG(INFO) << "Get audio from grpc server: " << wav_filename;

  std::ifstream input_file(wav_filename, std::ifstream::binary);
  std::ostringstream oss;
  oss << input_file.rdbuf();
  std::string data(oss.str());
  input_file.close();

  reply->set_content_type("audio/wav");
  reply->set_data(data.c_str(), data.size());
  return ::grpc::Status::OK;
}

}  // namespace serving
}  // namespace grpc_with_envoy
