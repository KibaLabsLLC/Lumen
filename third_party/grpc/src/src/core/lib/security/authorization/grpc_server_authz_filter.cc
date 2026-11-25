// Copyright 2021 gRPC authors.
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


#include <grpc/support/port_platform.h>

#include <functional>
#include <memory>
#include <string>
#include <utility>


namespace grpc_core {

GrpcServerAuthzFilter::GrpcServerAuthzFilter(
    RefCountedPtr<grpc_auth_context> auth_context, const ChannelArgs& args,
    RefCountedPtr<grpc_authorization_policy_provider> provider)
    : auth_context_(std::move(auth_context)),
      per_channel_evaluate_args_(auth_context_.get(), args),
      provider_(std::move(provider)) {}

absl::StatusOr<std::unique_ptr<GrpcServerAuthzFilter>>
GrpcServerAuthzFilter::Create(const ChannelArgs& args, ChannelFilter::Args) {
  auto* auth_context = args.GetObject<grpc_auth_context>();
  auto* provider = args.GetObject<grpc_authorization_policy_provider>();
  if (provider == nullptr) {
    return absl::InvalidArgumentError("Failed to get authorization provider.");
  }
  return std::make_unique<GrpcServerAuthzFilter>(
      auth_context != nullptr ? auth_context->Ref() : nullptr, args,
      provider->Ref());
}

bool GrpcServerAuthzFilter::IsAuthorized(ClientMetadata& initial_metadata) {
  EvaluateArgs args(&initial_metadata, &per_channel_evaluate_args_);
  GRPC_TRACE_VLOG(grpc_authz_api, 2)
      << "checking request: url_path=" << args.GetPath()
      << ", transport_security_type=" << args.GetTransportSecurityType()
      << ", uri_sans=[" << absl::StrJoin(args.GetUriSans(), ",")
      << "], dns_sans=[" << absl::StrJoin(args.GetDnsSans(), ",")
      << "], subject=" << args.GetSubject();
  grpc_authorization_policy_provider::AuthorizationEngines engines =
      provider_->engines();
  if (engines.deny_engine != nullptr) {
    AuthorizationEngine::Decision decision =
        engines.deny_engine->Evaluate(args);
    if (decision.type == AuthorizationEngine::Decision::Type::kDeny) {
      GRPC_TRACE_LOG(grpc_authz_api, INFO)
          << "chand=" << this << ": request denied by policy "
          << decision.matching_policy_name;
      return false;
    }
  }
  if (engines.allow_engine != nullptr) {
    AuthorizationEngine::Decision decision =
        engines.allow_engine->Evaluate(args);
    if (decision.type == AuthorizationEngine::Decision::Type::kAllow) {
      GRPC_TRACE_VLOG(grpc_authz_api, 2)
          << "chand=" << this << ": request allowed by policy "
          << decision.matching_policy_name;
      return true;
    }
  }
  GRPC_TRACE_LOG(grpc_authz_api, INFO)
      << "chand=" << this << ": request denied, no matching policy found.";
  return false;
}

absl::Status GrpcServerAuthzFilter::Call::OnClientInitialMetadata(
    ClientMetadata& md, GrpcServerAuthzFilter* filter) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "GrpcServerAuthzFilter::Call::OnClientInitialMetadata");
  if (!filter->IsAuthorized(md)) {
    return absl::PermissionDeniedError("Unauthorized RPC request rejected.");
  }
  return absl::OkStatus();
}

const grpc_channel_filter GrpcServerAuthzFilter::kFilter =
    MakePromiseBasedFilter<GrpcServerAuthzFilter, FilterEndpoint::kServer>();

}  // namespace grpc_core
