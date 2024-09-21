#include <Content.hpp>
#include <JSONArray.hpp>
#include <JSONObject.hpp>
#include <exception>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace picoJSON {

  std::unordered_map<std::string, JSON> Content::get_properties() const noexcept {
    return properties_;
  }

  bool Content::search(std::string key) const noexcept {
    for (const auto& [k, _] : properties_) {
      if (k == key) {
        return true;
      }
    }

    return false;
  }

  bool Content::search(std::string key, const JSONType type) const noexcept {
    for (const auto& [k, v] : properties_) {
      if (k == key && v.get_type() == type) {
        return true;
      }
    }
    return false;
  }

  std::optional<JSON> Content::get_value(std::string key) const noexcept {
    for (const auto& [k, v] : properties_) {
      if (k == key) {
        return v;
      }
    }

    return std::nullopt;
  }

  std::optional<JSON> Content::operator[](std::string key) const noexcept {
    return get_value(key);
  }

  void Content::print() const noexcept {
    std::cout << "{" << std::endl;
    for (const auto& [k, v] : properties_) {
      std::cout << "\t" << k << ": " << v.to_string() << "," << std::endl;
    }
    std::cout << "}" << std::endl;
  }
} // namespace picoJSON
