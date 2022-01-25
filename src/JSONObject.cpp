#include <JSONObject.hpp>

using namespace std;

namespace picoJSON {
  JSONObject::JSONObject(JSONType type, vector<JSONProperty*>* value) : JSON(type), value_(value) {}

  vector<JSONProperty*>* JSONObject::getValue() const {
    return value_;
  }

  string JSONObject::toString() const {
    string out = "{ ";
    for (JSONProperty* prop : *value_) {
      out += prop->toString();
      out += " ";
    }
    out += " }";
    return out;
  }
}
