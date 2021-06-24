#ifndef JSONNULL_HPP
#define JSONNULL_HPP

#include "JSON.hpp"

using namespace std;

namespace picoJSON {
  class JSONNull : public JSON {
    public:
      JSONNull(JSONType type) : JSON(type) {}

      long int* getValue() const {
        return NULL;
      }

      string toString() const {
        return "\"null\"";
      }
  };
}

#endif
