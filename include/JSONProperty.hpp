#ifndef JSONPROPERTY_HPP
#define JSONPROPERTY_HPP

#include "JSON.hpp"
#include <iostream>
#include <memory>

namespace picoJSON {

class JSONProperty {
private:
  const std::string_view key_;
  std::shared_ptr<JSON> value_;

public:
  JSONProperty(const std::string_view key, JSON value);
  void print() const noexcept;
  std::string_view to_string() const noexcept;
  const std::string_view get_key() const noexcept;
  std::shared_ptr<JSON> get_value();

  friend std::ostream &operator<<(std::ostream &out, JSONProperty &prop) {
    out << prop.to_string();
    return out;
  }
};
} // namespace picoJSON

#endif
