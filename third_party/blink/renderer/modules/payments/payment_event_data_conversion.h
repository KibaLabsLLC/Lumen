// Copyright 2016 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_PAYMENTS_PAYMENT_EVENT_DATA_CONVERSION_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_PAYMENTS_PAYMENT_EVENT_DATA_CONVERSION_H_

#include "third_party/blink/renderer/platform/wtf/allocator/allocator.h"

namespace blink {

class CanMakePaymentEventInit;
class PaymentRequestEventInit;
class ScriptState;

class MODULES_EXPORT PaymentEventDataConversion {
  STATIC_ONLY(PaymentEventDataConversion);

 public:
  static PaymentCurrencyAmount* ToPaymentCurrencyAmount(
      payments::mojom::blink::PaymentCurrencyAmountPtr&);
  static CanMakePaymentEventInit* ToCanMakePaymentEventInit(
      ScriptState*,
      payments::mojom::blink::CanMakePaymentEventDataPtr);
  static PaymentRequestEventInit* ToPaymentRequestEventInit(
      ScriptState*,
      payments::mojom::blink::PaymentRequestEventDataPtr);
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_PAYMENTS_PAYMENT_EVENT_DATA_CONVERSION_H_
