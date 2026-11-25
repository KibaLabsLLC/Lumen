// Copyright 2024 gRPC authors.
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

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_CLIENT_CHAOTIC_GOOD_CONNECTOR_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_CLIENT_CHAOTIC_GOOD_CONNECTOR_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <cstddef>
#include <cstdint>
#include <memory>


namespace grpc_core {
namespace chaotic_good {
class ChaoticGoodConnector final : public SubchannelConnector {
 public:
  void Connect(const Args& args, Result* result, grpc_closure* notify) override;
  void Shutdown(grpc_error_handle) override {
    ActivityPtr connect_activity;
    MutexLock lock(&mu_);
    is_shutdown_ = true;
    connect_activity = std::move(connect_activity_);
  };

 private:
  class ConnectionCreator final : public ClientConnectionFactory {
   public:
    ConnectionCreator(
        grpc_event_engine::experimental::EventEngine::ResolvedAddress address,
        const ChannelArgs& args)
        : address_(address), args_(args) {}
    PendingConnection Connect(absl::string_view id) override;
    void Orphaned() override {};

   private:
    grpc_event_engine::experimental::EventEngine::ResolvedAddress address_;
    ChannelArgs args_;
  };

  struct ResultNotifier {
    ResultNotifier(const Args& args, Result* result, grpc_closure* notify)
        : args(args),
          config(args.channel_args),
          result(result),
          notify(notify) {}

    Args args;
    Config config;
    Result* result;
    grpc_closure* notify;

    void Run(absl::Status status, DebugLocation location = {}) {
      ExecCtx::Run(location, std::exchange(notify, nullptr), status);
    }
  };

  Mutex mu_;
  bool is_shutdown_ ABSL_GUARDED_BY(mu_) = false;
  ActivityPtr connect_activity_ ABSL_GUARDED_BY(mu_);
};
}  // namespace chaotic_good
}  // namespace grpc_core

grpc_channel* grpc_chaotic_good_channel_create(const char* target,
                                               const grpc_channel_args* args);

#endif  // GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_CLIENT_CHAOTIC_GOOD_CONNECTOR_H
