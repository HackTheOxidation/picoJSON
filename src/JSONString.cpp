#include <JSONString.hpp>

using namespace std;

namespace picoJSON {
JSONString::JSONString(JSONType type, string value)
    : JSON(type), value_(value) {}

string JSONString::getValue() const { return value_; }

string JSONString::toString() const { return value_; }
} // namespace picoJSON
