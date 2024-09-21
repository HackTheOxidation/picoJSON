#include <JSON.hpp>
#include <Token.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace picoJSON {

JSON::JSON(JSONType type, std::string_view value)
    : type_(type), value_(value) {}

void JSON::print() const { std::cout << "type: " << to_string(); }

std::optional<float> JSON::as_number() const {
  if (type_ == JSONType::Number)
    return std::stof(value_);
}

constexpr std::optional<std::string_view> JSON::as_string() const {
  if (type_ == JSONType::String)
    return value_;
}

constexpr std::string_view JSON::to_string() const noexcept {
  std::string out;

  switch (type_) {
    case JSONType::String:
      out = "String";
      break;
    case JSONType::Number:
      out = "Number";
      break;
    case JSONType::Null:
      out = "Null";
      break;
    case JSONType::Bool:
      out = "Bool";
      break;
    case JSONType::Array:
      out = "Array";
      break;
    case JSONType::Object:
      out = "Object";
      break;
    default:
      break;
  }

  return out + ": " + std::string(get_value());
}
} // namespace picoJSON
