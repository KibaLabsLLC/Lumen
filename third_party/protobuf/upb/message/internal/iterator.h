// Protocol Buffers - Google's data interchange format
// Copyright 2024 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef GOOGLE_UPB_UPB_MESSAGE_INTERNAL_ITERATOR_H__
#define GOOGLE_UPB_UPB_MESSAGE_INTERNAL_ITERATOR_H__

#include <stddef.h>
#include <stdint.h>


// Must be last.

#define kUpb_BaseField_Begin ((size_t)-1)
bool UPB_PRIVATE(_upb_Message_NextBaseField)(const upb_Message* msg,
                                             const upb_MiniTable* m,
                                             const upb_MiniTableField** out_f,
                                             upb_MessageValue* out_v,
                                             uintptr_t* iter);

#endif  // GOOGLE_UPB_UPB_MESSAGE_INTERNAL_ITERATOR_H__
