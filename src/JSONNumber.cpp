#include <JSONNumber.hpp>

using namespace std;

namespace picoJSON {

JSONNumber::JSONNumber(JSONType type, float value)
    : JSON(type), value_(value) {}

float JSONNumber::getValue() const { return value_; }

string JSONNumber::toString() const {
  ostringstream ss;
  ss << value_;
  return ss.str();
}
} // namespace picoJSON
