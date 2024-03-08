#include <JSONArray.hpp>

namespace picoJSON {
  JSONArray::JSONArray(const JSONType type, std::vector<JSON> value)
    : JSON(type), value_(value) {}

  std::vector<JSON> JSONArray::get_value() const { return value_; }

  std::string JSONArray::to_string() const {
    string out = "[ ";

    for (const JSON json : value_) {
      out += json->to_string() + " ";
    }
    return out + "]";
  }

  void JSONArray::print() const { std::cout << to_string(); }
} // namespace picoJSON
