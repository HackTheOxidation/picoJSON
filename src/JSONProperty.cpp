#include <JSON.hpp>
#include <JSONProperty.hpp>

using namespace std;

namespace picoJSON {
JSONProperty::JSONProperty(string key, JSON *value)
    : key_(key), value_(value) {}

void JSONProperty::print() const {
  cout << key_ << " : " << value_->toString();
}

string JSONProperty::toString() const {
  string out = key_;
  out += " : ";
  out += value_->getValue();
  return out;
}

string JSONProperty::getKey() const { return key_; }

JSON *JSONProperty::getValue() { return value_; }
} // namespace picoJSON
