#ifndef JSONSTRING_HPP
#define JSONSTRING_HPP

#include "JSON.hpp"

using namespace std;

namespace picoJSON {

  class JSONString : public JSON {
    public:
      JSONString(JSONType type, string value) : JSON(type), value_(value) {
      }

      string getValue() const {
        return value_;
      }

      string toString() const {
        return value_;
      }

    private:
      string value_;
  };
}

#endif
