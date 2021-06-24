#ifndef JSONARRAY_HPP
#define JSONARRAY_HPP

#include "JSON.hpp"
#include <vector>

using namespace std;

namespace picoJSON {

  class JSONArray : public JSON {
    public:
      JSONArray(JSONType type, vector<JSON*>* value) : JSON(type), value_(value) {

      }

      vector<JSON*>* getValue() const {
        return value_;
      }

      string toString() const {
        string out = "[ ";
        
        for (JSON* json : *value_) {
          out += json->toString();
          out += " ";
        }
        out += "]";
        return out;
      }

      void print() const {
        cout << toString();
      }

    private:
      vector<JSON*>* value_;
  };
}

#endif
