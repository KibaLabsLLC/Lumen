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

absl::Status Cart16ParamDefinition::ValidateAndWrite(WriteBitBuffer& wb) const {
  // The common part.
  RETURN_IF_NOT_OK(ParamDefinition::ValidateAndWrite(wb));

  // The sub-class specific part.
  RETURN_IF_NOT_OK(wb.WriteSigned16(default_x_));
  RETURN_IF_NOT_OK(wb.WriteSigned16(default_y_));
  RETURN_IF_NOT_OK(wb.WriteSigned16(default_z_));

  return absl::OkStatus();
}

absl::Status Cart16ParamDefinition::ReadAndValidate(ReadBitBuffer& rb) {
  // The common part.
  RETURN_IF_NOT_OK(ParamDefinition::ReadAndValidate(rb));

  // The sub-class specific part.
  RETURN_IF_NOT_OK(rb.ReadSigned16(default_x_));
  RETURN_IF_NOT_OK(rb.ReadSigned16(default_y_));
  RETURN_IF_NOT_OK(rb.ReadSigned16(default_z_));
  return absl::OkStatus();
}

absl::StatusOr<std::unique_ptr<ParameterData>>
Cart16ParamDefinition::CreateParameterDataFromBuffer(ReadBitBuffer& rb) const {
  auto data = CartesianPositionData::CreateFromBuffer(
      rb, CartesianBitDepth::k16Bit, /*is_dual=*/false);
  if (!data.ok()) {
    return data.status();
  }
  return std::make_unique<CartesianPositionData>(*std::move(data));
}

std::string Cart16ParamDefinition::ToString() const {
  return absl::StrCat("Cart16ParamDefinition:\n", ParamDefinition::ToString(),
                      "\n  default_x: ", default_x_,
                      "\n  default_y: ", default_y_,
                      "\n  default_z: ", default_z_);
}

}  // namespace iamf_tools
