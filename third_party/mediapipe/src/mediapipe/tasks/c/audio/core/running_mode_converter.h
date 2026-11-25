#ifndef MEDIAPIPE_TASKS_C_AUDIO_CORE_RUNNING_MODE_CONVERTER_H_
#define MEDIAPIPE_TASKS_C_AUDIO_CORE_RUNNING_MODE_CONVERTER_H_


namespace mediapipe::tasks::c::audio::core {

// Converts a C RunningMode to its C++ equivalent.
absl::StatusOr<mediapipe::tasks::audio::core::RunningMode>
CppConvertToRunningMode(MpAudioRunningMode running_mode);

}  // namespace mediapipe::tasks::c::audio::core

#endif  // MEDIAPIPE_TASKS_C_AUDIO_CORE_RUNNING_MODE_CONVERTER_H_
