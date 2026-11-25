// Protocol Buffers - Google's data interchange format
// Copyright 2023 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef UPB_REFLECTION_DESC_STATE_INTERNAL_H_
#define UPB_REFLECTION_DESC_STATE_INTERNAL_H_


// Must be last.

// Manages the storage for mini descriptor strings as they are being encoded.
// TODO: Move some of this state directly into the encoder, maybe.
typedef struct {
  upb_MtDataEncoder e;
  size_t bufsize;
  char* buf;
  char* ptr;
} upb_DescState;

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE void _upb_DescState_Init(upb_DescState* d) {
  d->bufsize = kUpb_MtDataEncoder_MinSize * 2;
  d->buf = NULL;
  d->ptr = NULL;
}

bool _upb_DescState_Grow(upb_DescState* d, upb_Arena* a);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_REFLECTION_DESC_STATE_INTERNAL_H_ */
