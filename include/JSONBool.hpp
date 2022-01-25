#ifndef JSONBOOL_HPP
#define JSONBOOL_HPP

#include "JSON.hpp"

using namespace std;

namespace picoJSON {
class JSONBool : public JSON {
public:
  JSONBool(JSONType type, bool value);

  bool getValue() const;

  string toString() const;

private:
  bool value_;
};
} // namespace picoJSON

#endif
