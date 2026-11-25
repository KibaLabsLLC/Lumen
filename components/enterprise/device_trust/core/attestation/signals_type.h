// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_ENTERPRISE_DEVICE_TRUST_CORE_ATTESTATION_SIGNALS_TYPE_H_
#define COMPONENTS_ENTERPRISE_DEVICE_TRUST_CORE_ATTESTATION_SIGNALS_TYPE_H_

#include "build/build_config.h"

#if BUILDFLAG(IS_CHROMEOS)

namespace enterprise_connectors {

// Use Chrome OS' signals definition.
using SignalsType = ::attestation::DeviceTrustSignals;

}  // namespace enterprise_connectors

#else

namespace enterprise_connectors {

// Use the browser signals definition.
using SignalsType = DeviceTrustSignals;

}  // namespace enterprise_connectors

#endif  // BUILDFLAG(IS_CHROMEOS)

#endif  // COMPONENTS_ENTERPRISE_DEVICE_TRUST_CORE_ATTESTATION_SIGNALS_TYPE_H_
