#include <JSON.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace picoJSON {

JSON::JSON(JSONType type) : type_(type) {}
JSON::JSON(JSONType type, string value) : type_(type), value_(value) {}

void JSON::print() const { cout << "type: " << toString(); }

float JSON::asNumber() const {
  if (type_ != Number)
    throw 1;
  return stof(value_);
}

string JSON::asString() const {
  if (type_ != String)
    throw 1;
  return value_;
}

string JSON::toString() const {
  string out = "";

  switch (type_) {
  case String:
    out = "String";
    break;
  case Number:
    out = "Number";
    break;
  case Null:
    out = "Null";
    break;
  case Bool:
    out = "Bool";
    break;
  case Array:
    out = "Array";
    break;
  case Object:
    out = "Object";
    break;
  default:
    break;
  }

  out += ": " + getValue();

  return out;
}
} // namespace picoJSON
