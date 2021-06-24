#ifndef JSONBOOL_HPP
#define JSONBOOL_HPP

#include "JSON.hpp"

using namespace std;

namespace picoJSON {
  class JSONBool : public JSON {
    public:
      JSONBool(JSONType type, bool value) : JSON(type), value_(value) {
      }

      bool getValue() const {
        return value_;
      }

      string toString() const {
        if (value_)
          return "\"true\"";
        else
          return "\"false\"";
      }

    private:
      bool value_;
  };
}

#endif
