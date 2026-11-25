// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_ASH_SERVICES_NEARBY_PUBLIC_MOJOM_NEARBY_CONNECTIONS_MOJOM_TRAITS_H_
#define CHROMEOS_ASH_SERVICES_NEARBY_PUBLIC_MOJOM_NEARBY_CONNECTIONS_MOJOM_TRAITS_H_


namespace mojo {

template <>
class EnumTraits<nearby::connections::mojom::LogSeverity,
                 nearby::api::LogMessage::Severity> {
 public:
  static nearby::connections::mojom::LogSeverity ToMojom(
      nearby::api::LogMessage::Severity input);
  static nearby::api::LogMessage::Severity FromMojom(
      nearby::connections::mojom::LogSeverity input);
};

}  // namespace mojo

#endif  // CHROMEOS_ASH_SERVICES_NEARBY_PUBLIC_MOJOM_NEARBY_CONNECTIONS_MOJOM_TRAITS_H_
