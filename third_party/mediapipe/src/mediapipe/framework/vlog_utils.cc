

namespace mediapipe {

void VlogLargeMessage(int verbose_level, absl::string_view message) {
#if defined(MEDIAPIPE_MOBILE)
  if (message.size() > 4096) {
    for (const auto& line : absl::StrSplit(message, '\n')) {
      ABSL_VLOG(verbose_level) << line;
    }
    return;
  }
#endif
  ABSL_VLOG(verbose_level) << message;
}

}  // namespace mediapipe
