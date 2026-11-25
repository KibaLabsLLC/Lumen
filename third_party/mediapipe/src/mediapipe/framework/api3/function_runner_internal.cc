
#include <utility>


namespace mediapipe::api3 {

absl::StatusOr<mediapipe::Packet> GetOutputPacket(OutputStreamPoller& poller,
                                                  CalculatorGraph& graph) {
  mediapipe::Packet packet;
  if (!poller.Next(&packet)) {
    if (graph.HasError()) {
      absl::Status status;
      (void)graph.GetCombinedErrors("Failed to poll the output", &status);
      return status;
    } else {
      return absl::InternalError("Failled to poll the output.");
    }
  }

  // NOTE: currently supporting timestamp-less execution only.
  return std::move(packet).At(Timestamp::Unset());
}

}  // namespace mediapipe::api3
