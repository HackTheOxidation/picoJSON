#include <JSONArray.hpp>

namespace picoJSON {
  JSONArray::JSONArray(const JSONType type, std::vector<JSON> value)
    : JSON(type), value_(value) {}

  std::vector<JSON> JSONArray::get_value() const { return value_; }

  std::string JSONArray::to_string() const {
    std::string out = "[ ";

    for (const JSON json : value_) {
      out += std::string(json.to_string()) + " ";
    }
    return out + "]";
  }

  void JSONArray::print() const { std::cout << to_string(); }
} // namespace picoJSON
