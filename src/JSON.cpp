#include <picoJSON/JSON.hpp>
#include <picoJSON/Token.hpp>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <system_error>
#include <utility>

namespace picoJSON {

JSON::JSON(JSONType type, std::string_view value)
    : type_(type), value_(value) {}

void JSON::print() const { std::cout << "type: " << to_string(); }

std::optional<float> JSON::as_number() const {
  float value{};
  if (type_ == JSONType::Number &&
      std::from_chars(value_.data(), value_.data() + value_.size(), value).ec == std::errc{}) {
    return value;
  }
  return std::nullopt;
}

constexpr std::optional<std::string_view> JSON::as_string() const {
  if (type_ == JSONType::String)
    return value_;
}

std::ostream &operator<<(std::ostream &out, const JSON &json) {
  out << json.to_string();
  return out;
}

} // namespace picoJSON
