// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_PAYMENTS_SECURE_PAYMENT_CONFIRMATION_TYPE_CONVERTER_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_PAYMENTS_SECURE_PAYMENT_CONFIRMATION_TYPE_CONVERTER_H_

#include "mojo/public/cpp/bindings/type_converter.h"

namespace mojo {

template <>
struct TypeConverter<
    payments::mojom::blink::SecurePaymentConfirmationRequestPtr,
    blink::SecurePaymentConfirmationRequest*> {
  static payments::mojom::blink::SecurePaymentConfirmationRequestPtr Convert(
      const blink::SecurePaymentConfirmationRequest* input);
};

template <>
struct TypeConverter<payments::mojom::blink::PaymentEntityLogoPtr,
                     blink::PaymentEntityLogo*> {
  static payments::mojom::blink::PaymentEntityLogoPtr Convert(
      const blink::PaymentEntityLogo* input);
};

}  // namespace mojo

#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_PAYMENTS_SECURE_PAYMENT_CONFIRMATION_TYPE_CONVERTER_H_
