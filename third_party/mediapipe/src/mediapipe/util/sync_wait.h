#ifndef MEDIAPIPE_UTIL_SYNC_WAIT_H_
#define MEDIAPIPE_UTIL_SYNC_WAIT_H_


namespace mediapipe {

// `fd` - represents a sync
// `timeout` - wait timeout, pass `absl::InfiniteDuration()` to wait until
//             signaled.
absl::Status SyncWait(int fd, absl::Duration timeout);

// `fd` - represents a sync
// `timeout` - wait timeout, pass `absl::InfiniteDuration()` to wait until
//             signaled.
absl::Status SyncWait(const UniqueFd& fd, absl::Duration timeout);

// `fd` - represents a sync
// `timeout` - wait timeout, pass `absl::InfiniteDuration()` to wait until
//             signaled.
absl::Status SyncWait(const SharedFd& fd, absl::Duration timeout);

// Checks if sync represented by `fd` is signaled.
absl::StatusOr<bool> IsSignaled(int fd);

// Checks if sync represented by `fd` is signaled.
absl::StatusOr<bool> IsSignaled(const UniqueFd& fd);

// Checks if sync represented by `fd` is signaled.
absl::StatusOr<bool> IsSignaled(const SharedFd& fd);

}  // namespace mediapipe

#endif  // MEDIAPIPE_UTIL_SYNC_WAIT_H_
