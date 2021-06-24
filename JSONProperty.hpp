#ifndef JSONPROPERTY_HPP
#define JSONPROPERTY_HPP

#include "JSON.hpp"
#include <iostream>
#include <any>

using namespace std;

namespace picoJSON {

  class JSONProperty {
    private:
      string key_;
      JSON* value_;

    public:
      JSONProperty(string key, JSON* value) : key_(key), value_(value) {}

      void print() const {
        cout << key_ << " : " << value_->toString();
      }

      string toString() const {
        string out = key_;
        out += " : ";
        out += picoJSON::toString(value_);
        return out;
      }

      string getKey() const {
        return key_;
      }

      JSON* getValue() {
        return value_;
      }

      friend ostream& operator<<(ostream &out, JSONProperty &prop) {
        out << prop.toString();
        return out;
      }
  };
}

#endif
