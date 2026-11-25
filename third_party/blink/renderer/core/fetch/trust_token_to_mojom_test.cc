// Copyright 2023 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/fetch/trust_token_to_mojom.h"

#include <memory>

#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/blink/renderer/platform/bindings/exception_code.h"
#include "third_party/blink/renderer/platform/bindings/exception_state.h"

namespace blink {
namespace {

TEST(TrustTokenToMojomTest, Issuance) {
  PrivateToken* pt = PrivateToken::Create();
  pt->setOperation(V8OperationType::Enum::kTokenRequest);
  pt->setVersion(V8PrivateTokenVersion::Enum::k1);

  network::mojom::blink::TrustTokenParamsPtr params =
      network::mojom::blink::TrustTokenParams::New();
  DummyExceptionStateForTesting e;
  EXPECT_TRUE(ConvertTrustTokenToMojomAndCheckPermissions(
      *pt, {.issuance_enabled = true, .redemption_enabled = true}, &e,
      params.get()));
  EXPECT_EQ(params->operation,
            network::mojom::blink::TrustTokenOperationType::kIssuance);
}

TEST(TrustTokenToMojomTest, IssuanceDenied) {
  PrivateToken* pt = PrivateToken::Create();
  pt->setOperation(V8OperationType::Enum::kTokenRequest);
  pt->setVersion(V8PrivateTokenVersion::Enum::k1);

  auto params = network::mojom::blink::TrustTokenParams::New();
  DummyExceptionStateForTesting e;
  EXPECT_FALSE(ConvertTrustTokenToMojomAndCheckPermissions(
      *pt, {.issuance_enabled = false, .redemption_enabled = true}, &e,
      params.get()));
  EXPECT_TRUE(e.HadException());
  EXPECT_EQ(e.CodeAs<DOMExceptionCode>(), DOMExceptionCode::kNotAllowedError);
}

TEST(TrustTokenToMojomTest, Redemption) {
  PrivateToken* pt = PrivateToken::Create();
  pt->setOperation(V8OperationType::Enum::kTokenRedemption);
  pt->setVersion(V8PrivateTokenVersion::Enum::k1);

  network::mojom::blink::TrustTokenParamsPtr params =
      network::mojom::blink::TrustTokenParams::New();
  DummyExceptionStateForTesting e;
  EXPECT_TRUE(ConvertTrustTokenToMojomAndCheckPermissions(
      *pt, {.issuance_enabled = true, .redemption_enabled = true}, &e,
      params.get()));
  EXPECT_EQ(params->operation,
            network::mojom::blink::TrustTokenOperationType::kRedemption);
}

TEST(TrustTokenToMojomTest, RedemptionDenied) {
  PrivateToken* pt = PrivateToken::Create();
  pt->setOperation(V8OperationType::Enum::kTokenRedemption);
  pt->setVersion(V8PrivateTokenVersion::Enum::k1);

  auto params = network::mojom::blink::TrustTokenParams::New();
  DummyExceptionStateForTesting e;
  EXPECT_FALSE(ConvertTrustTokenToMojomAndCheckPermissions(
      *pt, {.issuance_enabled = true, .redemption_enabled = false}, &e,
      params.get()));
  EXPECT_TRUE(e.HadException());
  EXPECT_EQ(e.CodeAs<DOMExceptionCode>(), DOMExceptionCode::kNotAllowedError);
}

}  // namespace
}  // namespace blink
