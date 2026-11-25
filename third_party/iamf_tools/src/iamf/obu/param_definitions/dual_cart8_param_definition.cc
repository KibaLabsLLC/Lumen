/*
 * Copyright (c) 2025, Alliance for Open Media. All rights reserved
 *
 * This source code is subject to the terms of the BSD 3-Clause Clear License
 * and the Alliance for Open Media Patent License 1.0. If the BSD 3-Clause Clear
 * License was not distributed with this source code in the LICENSE file, you
 * can obtain it at www.aomedia.org/license/software-license/bsd-3-c-c. If the
 * Alliance for Open Media Patent License 1.0 was not distributed with this
 * source code in the PATENTS file, you can obtain it at
 * www.aomedia.org/license/patent.
 */

#include <memory>
#include <string>
#include <utility>


namespace iamf_tools {

absl::Status DualCart8ParamDefinition::ValidateAndWrite(
    WriteBitBuffer& wb) const {
  // The common part.
  RETURN_IF_NOT_OK(ParamDefinition::ValidateAndWrite(wb));

  // The sub-class specific part.
  RETURN_IF_NOT_OK(wb.WriteSigned8(default_first_x_));
  RETURN_IF_NOT_OK(wb.WriteSigned8(default_first_y_));
  RETURN_IF_NOT_OK(wb.WriteSigned8(default_first_z_));
  RETURN_IF_NOT_OK(wb.WriteSigned8(default_second_x_));
  RETURN_IF_NOT_OK(wb.WriteSigned8(default_second_y_));
  RETURN_IF_NOT_OK(wb.WriteSigned8(default_second_z_));

  return absl::OkStatus();
}

absl::Status DualCart8ParamDefinition::ReadAndValidate(ReadBitBuffer& rb) {
  // The common part.
  RETURN_IF_NOT_OK(ParamDefinition::ReadAndValidate(rb));

  // The sub-class specific part.
  RETURN_IF_NOT_OK(rb.ReadSigned8(default_first_x_));
  RETURN_IF_NOT_OK(rb.ReadSigned8(default_first_y_));
  RETURN_IF_NOT_OK(rb.ReadSigned8(default_first_z_));
  RETURN_IF_NOT_OK(rb.ReadSigned8(default_second_x_));
  RETURN_IF_NOT_OK(rb.ReadSigned8(default_second_y_));
  RETURN_IF_NOT_OK(rb.ReadSigned8(default_second_z_));
  return absl::OkStatus();
}

absl::StatusOr<std::unique_ptr<ParameterData>>
DualCart8ParamDefinition::CreateParameterDataFromBuffer(
    ReadBitBuffer& rb) const {
  auto data = CartesianPositionData::CreateFromBuffer(
      rb, CartesianBitDepth::k8Bit, /*is_dual=*/true);
  if (!data.ok()) {
    return data.status();
  }
  return std::make_unique<CartesianPositionData>(*std::move(data));
}

std::string DualCart8ParamDefinition::ToString() const {
  return absl::StrCat("DualCart8ParamDefinition:\n",
                      ParamDefinition::ToString(),
                      "\n  default_first_x: ", default_first_x_,
                      "\n  default_first_y: ", default_first_y_,
                      "\n  default_first_z: ", default_first_z_,
                      "\n  default_second_x: ", default_second_x_,
                      "\n  default_second_y: ", default_second_y_,
                      "\n  default_second_z: ", default_second_z_);
}

}  // namespace iamf_tools
