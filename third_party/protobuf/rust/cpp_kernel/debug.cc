
#include <string>


extern "C" {

google::protobuf::rust::RustStringRawParts proto2_rust_utf8_debug_string(
    const google::protobuf::MessageLite* msg) {
  std::string text = google::protobuf::Utf8Format(*msg);
  return google::protobuf::rust::RustStringRawParts(text);
}

}  // extern "C"
