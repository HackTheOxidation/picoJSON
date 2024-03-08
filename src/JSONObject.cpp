#include <JSONObject.hpp>

namespace picoJSON {
  JSONObject::JSONObject(const JSONType type, std::vector<JSONProperty> value)
    : JSON(type), value_(value) {}

  std::vector<JSONProperty> JSONObject::get_value() const { return value_; }

  std::string JSONObject::to_string() const {
    std::string out = "{ ";
    for (const JSONProperty prop : value_) {
      out += prop->toString() + " ";
    }
    return out + " }";
  }
} // namespace picoJSON
