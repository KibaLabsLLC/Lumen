#ifndef MEDIAPIPE_GPU_IMAGE_FRAME_VIEW_H_
#define MEDIAPIPE_GPU_IMAGE_FRAME_VIEW_H_


namespace mediapipe {
namespace internal {

template <>
class ViewProvider<ImageFrame> {
 public:
  virtual ~ViewProvider() = default;
  virtual std::shared_ptr<const ImageFrame> GetReadView(
      types<ImageFrame>) const = 0;
  virtual std::shared_ptr<ImageFrame> GetWriteView(types<ImageFrame>) = 0;
};

}  // namespace internal
}  // namespace mediapipe

#endif  // MEDIAPIPE_GPU_IMAGE_FRAME_VIEW_H_
