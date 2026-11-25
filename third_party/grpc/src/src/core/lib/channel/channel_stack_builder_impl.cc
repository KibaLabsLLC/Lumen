//
//
// Copyright 2016 gRPC authors.
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
//


#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>


namespace grpc_core {

absl::StatusOr<RefCountedPtr<grpc_channel_stack>>
ChannelStackBuilderImpl::Build() {
  std::vector<const grpc_channel_filter*> stack;

  for (const auto* filter : this->stack()) {
    stack.push_back(filter);
  }

  // calculate the size of the channel stack
  size_t channel_stack_size =
      grpc_channel_stack_size(stack.data(), stack.size());

  // allocate memory
  auto* channel_stack =
      static_cast<grpc_channel_stack*>(gpr_zalloc(channel_stack_size));

  // and initialize it
  grpc_error_handle error = grpc_channel_stack_init(
      1,
      [](void* p, grpc_error_handle) {
        auto* stk = static_cast<grpc_channel_stack*>(p);
        grpc_channel_stack_destroy(stk);
        gpr_free(stk);
      },
      channel_stack, stack.data(), stack.size(), channel_args(), name(),
      channel_stack, old_blackboard_, new_blackboard_);

  if (!error.ok()) {
    grpc_channel_stack_destroy(channel_stack);
    gpr_free(channel_stack);
    auto status = grpc_error_to_absl_status(error);
    return status;
  }

  // run post-initialization functions
  for (size_t i = 0; i < stack.size(); i++) {
    auto* elem = grpc_channel_stack_element(channel_stack, i);
    elem->filter->post_init_channel_elem(channel_stack, elem);
  }

  return RefCountedPtr<grpc_channel_stack>(channel_stack);
}

}  // namespace grpc_core
