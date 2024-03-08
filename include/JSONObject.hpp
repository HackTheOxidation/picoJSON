#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include "JSON.hpp"
#include "JSONProperty.hpp"
#include <vector>

namespace picoJSON {

class JSONObject : public JSON {
public:
  JSONObject(const JSONType type, std::vector<JSONProperty> value);
  std::vector<JSONProperty> get_value() const;
  std::string to_string() const;

private:
  std::vector<JSONProperty> value_;
};
} // namespace picoJSON

#endif
