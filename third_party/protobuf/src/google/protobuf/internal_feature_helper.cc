
#include <string>


namespace google {
namespace protobuf {
namespace internal {
FeatureSet InternalFeatureHelper::ParseAndGetEditionResolvedFeatureSet(
    absl::string_view data, Edition edition) {
  FeatureSetDefaults defaults;
  std::string unescaped_data;
  absl::Base64Unescape(data, &unescaped_data);
  ABSL_CHECK(defaults.ParseFromString(unescaped_data));
  auto edition_feature_set = GetEditionFeatureSetDefaults(edition, defaults);
  ABSL_CHECK_OK(edition_feature_set);
  return *edition_feature_set;
}
}  // namespace internal
}  // namespace protobuf
}  // namespace google
