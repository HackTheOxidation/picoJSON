#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include "JSON.hpp"
#include <string>
#include <unordered_map>

namespace picoJSON {

class JSONObject : public JSON {
public:
  JSONObject(const JSONType type, std::unordered_map<std::string, JSON> value);
  std::unordered_map<std::string, JSON> get_value() const;
  std::string to_string() const;

private:
  std::unordered_map<std::string, JSON> value_;
};
} // namespace picoJSON

#endif
