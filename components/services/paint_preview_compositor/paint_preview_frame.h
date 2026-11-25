// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SERVICES_PAINT_PREVIEW_COMPOSITOR_PAINT_PREVIEW_FRAME_H_
#define COMPONENTS_SERVICES_PAINT_PREVIEW_COMPOSITOR_PAINT_PREVIEW_FRAME_H_

#include <vector>


namespace paint_preview {

// A deserialized in-memory representation of a PaintPreviewFrame and its
// associated subframe clip rects.
struct PaintPreviewFrame {
 public:
  PaintPreviewFrame();
  ~PaintPreviewFrame();

  PaintPreviewFrame(PaintPreviewFrame&& other);
  PaintPreviewFrame& operator=(PaintPreviewFrame&& other);

  sk_sp<SkPicture> skp;
  std::vector<mojom::SubframeClipRect> subframe_clip_rects;

 private:
  PaintPreviewFrame(const PaintPreviewFrame&) = delete;
  PaintPreviewFrame& operator=(const PaintPreviewFrame&) = delete;
};

}  // namespace paint_preview

#endif  // COMPONENTS_SERVICES_PAINT_PREVIEW_COMPOSITOR_PAINT_PREVIEW_FRAME_H_
