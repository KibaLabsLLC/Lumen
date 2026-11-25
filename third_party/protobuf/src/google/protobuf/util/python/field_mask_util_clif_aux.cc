
#include <Python.h>

#include <memory>
#include <string>


namespace google {
namespace protobuf {
namespace util {

PyObject* MergeMessageToBytes(const google::protobuf::Message& source,
                              const google::protobuf::FieldMask& mask,
                              const FieldMaskUtil::MergeOptions& options,
                              const google::protobuf::Message& destination) {
  std::unique_ptr<google::protobuf::Message> message(destination.New());
  message->MergeFrom(destination);
  FieldMaskUtil::MergeMessageTo(source, mask, options, message.get());
  std::string wire;
  // TODO: Remove this suppression.
  (void)message->SerializeToString(&wire);
  return PyBytes_FromStringAndSize(wire.data(),
                                   static_cast<Py_ssize_t>(wire.size()));
}

}  // namespace util
}  // namespace protobuf
}  // namespace google
