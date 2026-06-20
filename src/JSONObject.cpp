#include <picoJSON/JSONObject.hpp>

namespace picoJSON {
  JSONObject::JSONObject(const JSONType type, std::unordered_map<std::string, JSON> value)
    : JSON(type), value_(value) {}

  std::unordered_map<std::string, JSON> JSONObject::get_value() const { return value_; }

  std::string JSONObject::to_string() const {
    std::string out = "{ ";
    for (const auto& [k, v] : value_) {
      out += k + ": " + std::string(v.to_string()) + " ";
    }
    return out + " }";
  }
} // namespace picoJSON
