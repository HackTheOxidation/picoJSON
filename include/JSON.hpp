#ifndef JSON_HPP_
#define JSON_HPP_

#include <cstddef>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

namespace picoJSON {

enum class JSONType { Bool, String, Number, Null, Array, Object };

class JSONArray;
class JSONObject;

class JSON {
public:
  JSON(JSONType, std::string_view = "");
  void print() const;

  JSONType get_type() const { return type_; }
  constexpr std::optional<std::string_view> as_string() const;
  std::optional<float> as_number() const;
  std::optional<bool> as_bool() const;
  std::optional<std::nullptr_t> as_null() const;
  std::optional<JSONArray> as_array() const;
  std::optional<JSONObject> as_object() const;
  constexpr std::string_view get_value() const { return value_; }

constexpr std::string_view to_string() const noexcept {
  std::stringstream out;

  switch (type_) {
  case JSONType::String:
    out << "String";
    break;
  case JSONType::Number:
    out << "Number";
    break;
  case JSONType::Null:
    out << "Null";
    break;
  case JSONType::Bool:
    out << "Bool";
    break;
  case JSONType::Array:
    out << "Array";
    break;
  case JSONType::Object:
    out << "Object";
    break;
  default:
    break;
  }

  out << ": " << get_value();
  return out.str();
}

private:
  const JSONType type_;
  const std::string_view value_;
};

} // namespace picoJSON
#endif
