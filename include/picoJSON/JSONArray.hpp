#ifndef JSONARRAY_HPP
#define JSONARRAY_HPP

#include "JSON.hpp"
#include <string>
#include <vector>

namespace picoJSON {

class JSONArray : public JSON {
public:
  JSONArray(const JSONType type, std::vector<JSON> value);
  std::vector<JSON> get_value() const;
  std::string to_string() const;
  void print() const;

private:
  std::vector<JSON> value_;
};
} // namespace picoJSON

#endif
