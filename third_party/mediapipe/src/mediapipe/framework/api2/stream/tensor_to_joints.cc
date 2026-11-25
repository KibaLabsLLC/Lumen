

namespace mediapipe::api2::builder {

namespace {}  // namespace

Stream<JointList> ConvertTensorToJointsAtIndex(Stream<Tensor> tensor,
                                               const int num_joints,
                                               const int start_index,
                                               Graph& graph) {
  auto& to_joints = graph.AddNode("TensorToJointsCalculator");
  auto& to_joints_options =
      to_joints.GetOptions<TensorToJointsCalculatorOptions>();
  to_joints_options.set_num_joints(num_joints);
  to_joints_options.set_start_index(start_index);
  tensor.ConnectTo(to_joints[TensorToJointsCalculator::kInTensor]);
  return to_joints[TensorToJointsCalculator::kOutJoints];
}

}  // namespace mediapipe::api2::builder
