#include <JSON.hpp>
#include <JSONProperty.hpp>
#include <string_view>

namespace picoJSON {
  JSONProperty::JSONProperty(const std::string_view key, JSON value)
    : key_(key), value_(value) {}

  void JSONProperty::print() const noexcept {
    std::cout << key_ << " : " << value_.to_string();
  }

  std::string_view JSONProperty::to_string() const noexcept {
    std::string out = key_;
    out += " : ";
    out += value_->getValue();
    return out;
  }

  const std::string_view JSONProperty::get_key() const noexcept { return key_; }

  std::shared_ptr<JSON> JSONProperty::get_value() const { return value_; }
} // namespace picoJSON
