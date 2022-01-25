#include <JSONArray.hpp>

using namespace std;

namespace picoJSON {
  JSONArray::JSONArray(JSONType type, vector<JSON*>* value) : JSON(type), value_(value) {}

  vector<JSON*>* JSONArray::getValue() const {
        return value_;
  }

  string JSONArray::toString() const {
        string out = "[ ";
        
        for (JSON* json : *value_) {
          out += json->toString();
          out += " ";
        }
        out += "]";
        return out;
  }

  void JSONArray::print() const {
    cout << toString();
  }
}
