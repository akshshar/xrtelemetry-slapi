#pragma once

#include <stdexcept>

#include <folly/Format.h>

namespace iosxr {

class IosxrslException : public std::runtime_error {
 public:
  explicit IosxrslException(const std::string& exception)
      : std::runtime_error(
            folly::sformat("Iosxrsl exception: {} ", exception)) {}
};
} // namespace iosxr 
