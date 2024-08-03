#include "soptions.hpp"

#include <iostream>
#include <string>
#include <string_view>

#include <boost/program_options.hpp>

namespace sds {

namespace {
class arg_parse_error : public std::exception {
  std::string msg_;
  arg_parse_error(std::string_view msg) : msg_(msg) {}
  const char* what() const noexcept override { return msg_.c_str(); }
};

using namespace std::string_view_literals;
constexpr auto kUsageDescription =
    "Usage: sd-server [option...]\n"
    "Example: sd-server -p 8080 -a 0.0.0.0 --threads=4 --root=/home/user";
}  // namespace

auto parse_args(int argc, char* argv[]) -> std::optional<options> {
  options opt;

  namespace po = boost::program_options;
  po::options_description desc("Description");
  desc.add_options()("help", kUsageDescription)(
      "port,p", po::value<std::uint16_t>(&opt.port)->default_value(8080),
      "listen port")(
      "address,a",
      po::value<std::string>(&opt.address)->default_value("0.0.0.0"),
      "binding address")(
      "threads,t", po::value<std::int32_t>(&opt.threads)->default_value(1),
      "number of threads")("root,r", po::value(&opt.doc_root),
                           "root directory");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return std::nullopt;
  }

  if (!vm.count("root")) {
    std::cerr << "root not initialazed\n" << desc;
    return std::nullopt;
  }

  return std::make_optional<options>(opt);
}

}  // namespace sds