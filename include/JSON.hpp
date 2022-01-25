#ifndef JSON_HPP_
#define JSON_HPP_

#include <iostream>

using namespace std;

namespace picoJSON {

  enum JSONType {
    Bool,
    String,
    Number,
    Null,
    Array,
    Object
  };

  class JSON {
    private:
      JSONType type_;

    public:
      JSON(JSONType);
      void print() const;
      virtual ~JSON() {}
      virtual string toString() const;

      JSONType getType() const {
        return type_;
      }

      friend ostream& operator<<(ostream &out, JSON &json) {
        out << json.toString();
        return out;
      }
  };

  string toString(JSON* json);
}
#endif
