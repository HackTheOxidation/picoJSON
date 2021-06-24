#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include "JSON.hpp"
#include "JSONProperty.hpp"
#include <vector>

using namespace std;

namespace picoJSON {

  class JSONObject : public JSON {
    public:
      JSONObject(JSONType type, vector<JSONProperty*>* value) : JSON(type), value_(value) {
      }
      

      vector<JSONProperty*>* getValue() const {
        return value_;
      }

      string toString() const {
        string out = "{ ";
        for (JSONProperty* prop : *value_) {
          out += prop->toString();
          out += " ";
        }
        out += " }";
        return out;
      }

    private:
    vector<JSONProperty*>* value_;
  };
}

#endif
