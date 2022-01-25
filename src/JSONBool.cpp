#include <JSONBool.hpp>

using namespace std;

namespace picoJSON {

JSONBool::JSONBool(JSONType type, bool value) : JSON(type), value_(value) {}

bool JSONBool::getValue() const { return value_; }

string JSONBool::toString() const {
  if (value_)
    return "\"true\"";
  else
    return "\"false\"";
}
} // namespace picoJSON
