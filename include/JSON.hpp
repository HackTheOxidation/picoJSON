#ifndef JSON_HPP_
#define JSON_HPP_

#include <iostream>

using namespace std;

namespace picoJSON {

enum JSONType { Bool, String, Number, Null, Array, Object };

class JSON {
private:
  JSONType type_;
  string value_;

public:
  JSON(JSONType);
  JSON(JSONType, string);
  void print() const;
  virtual ~JSON() {}
  virtual string toString() const;

  JSONType getType() const { return type_; }
  string asString() const;
  float asNumber() const;
  bool asBool() const;
  int asNull() const;
  JSON asArray() const;
  JSON asObject() const;
  string getValue() const { return value_; }

  friend ostream &operator<<(ostream &out, JSON &json) {
    out << json.toString();
    return out;
  }
};
} // namespace picoJSON
#endif
