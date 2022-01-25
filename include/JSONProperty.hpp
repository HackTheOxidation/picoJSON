#ifndef JSONPROPERTY_HPP
#define JSONPROPERTY_HPP

#include "JSON.hpp"
#include <iostream>

using namespace std;

namespace picoJSON {

  class JSONProperty {
    private:
      string key_;
      JSON* value_;

    public:
      JSONProperty(string key, JSON* value);

      void print() const;

      string toString() const;

      string getKey() const;

      JSON* getValue();

      friend ostream& operator<<(ostream &out, JSONProperty &prop) {
        out << prop.toString();
        return out;
      }
  };
}

#endif
