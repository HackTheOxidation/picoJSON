#ifndef CONTENT_HPP
#define CONTENT_HPP

#include "JSON.hpp"
#include "JSONArray.hpp"
#include "JSONObject.hpp"
#include <exception>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>


namespace picoJSON {

class Content {
public:
  Content(const std::unordered_map<std::string, JSON>& properties)
    : properties_(properties) {}
  std::unordered_map<std::string, JSON> get_properties() const noexcept;
  bool search(std::string key) const noexcept;
  bool search(std::string key, const JSONType type) const noexcept;
  std::optional<JSON> get_value(std::string key) const noexcept;
  std::optional<JSON> operator[](std::string key) const noexcept;
  void print() const noexcept;
  
private:
  std::unordered_map<std::string, JSON> properties_;
};
} // namespace picoJSON

#endif
