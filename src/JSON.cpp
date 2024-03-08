#include <JSON.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace picoJSON {

JSON::JSON(JSONType type, std::string_view value = "")
  : type_(type), value_(value) {}

void JSON::print() const { std::cout << "type: " << to_string(); }

std::optional<float> JSON::as_number() const {
  if (type_ == Number)
    return stof(value_);
}

constexpr std::optional<std::string_view>> JSON::as_string() const {
  if (type_ == String)
    return value_;
}

constexpr std::string_view JSON::to_string() const noexcept {
  std::string out;

  switch (type_) {
  case String:
    out = "String";
    break;
  case Number:
    out = "Number";
    break;
  case Null:
    out = "Null";
    break;
  case Bool:
    out = "Bool";
    break;
  case Array:
    out = "Array";
    break;
  case Object:
    out = "Object";
    break;
  default:
    break;
  }

  return out + ": " + get_value();
}
} // namespace picoJSON
