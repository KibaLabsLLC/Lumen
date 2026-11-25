// Copyright 2022 The gRPC Authors
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


#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>

#if defined(GPR_WINDOWS)

namespace grpc_event_engine::experimental {

std::unique_ptr<EventEngine> DefaultEventEngineFactory() {
  return std::make_unique<WindowsEventEngine>();
}

}  // namespace grpc_event_engine::experimental
#elif defined(GRPC_CFSTREAM)

namespace grpc_event_engine::experimental {

std::unique_ptr<EventEngine> DefaultEventEngineFactory() {
  return std::make_unique<CFEventEngine>();
}

}  // namespace grpc_event_engine::experimental
#else

namespace grpc_event_engine::experimental {

std::unique_ptr<EventEngine> DefaultEventEngineFactory() {
  return std::make_unique<PosixEventEngine>();
}

}  // namespace grpc_event_engine::experimental

#endif
