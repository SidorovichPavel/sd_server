#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace sds {

class arg_parse_error;

struct options {
  std::string address;
  std::uint16_t port;
  std::string doc_root;
  std::int32_t threads;
};

auto parse_args(int argc, char* argv[]) -> std::optional<options>;

}  // namespace sds