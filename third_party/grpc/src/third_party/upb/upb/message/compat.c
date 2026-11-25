// Protocol Buffers - Google's data interchange format
// Copyright 2023 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd


#include <stddef.h>
#include <stdint.h>


// Must be last.

const upb_MiniTableExtension* upb_Message_ExtensionByIndex(
    const upb_Message* msg, size_t index) {
  size_t count;
  const upb_Extension* ext = UPB_PRIVATE(_upb_Message_Getexts)(msg, &count);

  UPB_ASSERT(index < count);
  return ext[index].ext;
}

const upb_MiniTableExtension* upb_Message_FindExtensionByNumber(
    const upb_Message* msg, uint32_t field_number) {
  size_t count;
  const upb_Extension* ext = UPB_PRIVATE(_upb_Message_Getexts)(msg, &count);

  for (; count--; ext++) {
    const upb_MiniTableExtension* e = ext->ext;
    if (upb_MiniTableExtension_Number(e) == field_number) return e;
  }
  return NULL;
}
