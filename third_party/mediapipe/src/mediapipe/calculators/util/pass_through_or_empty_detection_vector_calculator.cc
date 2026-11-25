
#include <vector>


namespace mediapipe {

class PassThroughOrEmptyDetectionVectorCalculatorImpl
    : public mediapipe::api2::NodeImpl<
          PassThroughOrEmptyDetectionVectorCalculator> {
 public:
  absl::Status Process(CalculatorContext* cc) override {
    if (kInputVector(cc).IsEmpty()) {
      kOutputVector(cc).Send(std::vector<mediapipe::Detection>{});
      return absl::OkStatus();
    }
    kOutputVector(cc).Send(kInputVector(cc));
    return absl::OkStatus();
  }
};
MEDIAPIPE_NODE_IMPLEMENTATION(PassThroughOrEmptyDetectionVectorCalculatorImpl);

}  // namespace mediapipe
