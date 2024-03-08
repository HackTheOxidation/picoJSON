#include <Content.hpp>
#include <JSONArray.hpp>
#include <JSONObject.hpp>
#include <JSONProperty.hpp>
#include <exception>
#include <optional>
#include <stdexcept>
#include <string>

namespace picoJSON {

  std::vector<JSONProperty> Content::get_properties() const noexcept {
    return properties_;
  }

  bool Content::search(std::string key) const noexcept {
    for (const JSONProperty prop : properties_) {
      if (prop.get_key() == key) {
        return true;
      }
    }

    return false;
  }

  bool Content::search(std::string key, const JSONType type) const noexcept {
    for (const JSONProperty prop : properties_) {
      if (prop.get_key() == key && prop.get_value().get_type()) {
        return true;
      }
    }
    return false;
  }

  std::optional<JSON> Content::get_value(std::string key) const noexcept {
    for (const JSONProperty prop : properties_) {
      if (prop.get_key() == key) {
        return prop.get_value();
      }
    }

    return std::nullopt;
  }

  std::optional<JSON> Content::operator[](std::string key) {
    return get_value(key);
  }

  void Content::print() const noexcept {
    cout << "{" << endl;
    for (const JSONProperty prop : properties_) {
      cout << "\t";
      prop.print();
      cout << "," << endl;
    }
    cout << "}" << endl;
  }
} // namespace picoJSON
