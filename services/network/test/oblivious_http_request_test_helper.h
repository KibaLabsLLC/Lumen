// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SERVICES_NETWORK_TEST_OBLIVIOUS_HTTP_REQUEST_TEST_HELPER_H_
#define SERVICES_NETWORK_TEST_OBLIVIOUS_HTTP_REQUEST_TEST_HELPER_H_

#include <memory>
#include <string>


namespace network {
namespace test {

// ObliviousHttpRequestTestHelper encapsulates server-side oblivious HTTP key
// management and crypto logic.
//
class ObliviousHttpRequestTestHelper {
 public:
  ObliviousHttpRequestTestHelper();
  ~ObliviousHttpRequestTestHelper();

  std::string GetPublicKeyConfigs();
  std::pair<std::string, quiche::ObliviousHttpRequest::Context> DecryptRequest(
      std::string_view ciphertext_request);
  std::string EncryptResponse(std::string plaintext_response,
                              quiche::ObliviousHttpRequest::Context& context);

 private:
  std::unique_ptr<quiche::ObliviousHttpGateway> ohttp_gateway_;
  quiche::ObliviousHttpHeaderKeyConfig key_config_;
};

}  // namespace test
}  // namespace network

#endif  // SERVICES_NETWORK_TEST_OBLIVIOUS_HTTP_REQUEST_TEST_HELPER_H_
