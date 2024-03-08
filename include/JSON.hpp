#ifndef JSON_HPP_
#define JSON_HPP_

#include <cstddef>
#include <iostream>
#include <optional>

namespace picoJSON {

enum class JSONType { Bool, String, Number, Null, Array, Object };

class JSONArray;
class JSONObject;

class JSON {
private:
  const JSONType type_;
  const std::string_view value_;

public:
  JSON(JSONType, std::string_view = "");
  void print() const;
  virtual ~JSON() = 0;
  constexpr std::string_view to_string() const noexcept;

  JSONType get_type() const { return type_; }
  constexpr std::optional<std::string_view> as_string() const;
  std::optional<float> as_number() const;
  std::optional<bool> as_bool() const;
  std::optional<std::nullptr_t> as_null() const;
  std::optional<JSONArray> as_array() const;
  std::optional<JSONObject> as_object() const;
  constexpr std::string_view get_value() const { return value_; }

  friend std::ostream &operator<<(std::ostream &out, JSON &json) {
    out << json.to_string();
    return out;
  }
};
} // namespace picoJSON
#endif
