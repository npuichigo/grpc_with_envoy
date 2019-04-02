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

#ifndef GRPC_WITH_ENVOY_SERVING_DEMO_SERVICE_IMPL_H_
#define GRPC_WITH_ENVOY_SERVING_DEMO_SERVICE_IMPL_H_

#include <iostream>
#include <memory>
#include <string>

#include "grpcpp/server_context.h"
#include "grpcpp/support/status.h"
#include "grpc_with_envoy/serving/demo_service.grpc.pb.h"

namespace grpc_with_envoy {
namespace serving {

// Logic and data behind the server's behavior.
class DemoServiceImpl final : public Demo::Service {
 public:
  ::grpc::Status GetSomething(::grpc::ServerContext* context,
                              const GetRequest* request,
                              ::google::api::HttpBody* reply) override;
};

}  // namespace serving
}  // namespace grpc_with_envoy

#endif  // GRPC_WITH_ENVOY_SERVING_DEMO_SERVICE_IMPL_H_
