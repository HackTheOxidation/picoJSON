#include <JSON.hpp>
#include <JSONArray.hpp>
#include <JSONBool.hpp>
#include <JSONNull.hpp>
#include <JSONNumber.hpp>
#include <JSONObject.hpp>
#include <JSONString.hpp>
#include <JSONProperty.hpp>
#include <iostream>
#include <sstream>

using namespace std;

namespace picoJSON {

  JSON::JSON(JSONType type) 
          : type_(type) {}

  string toString(JSON* json) {
    string out = "";

    switch (json->getType()) {
      case String: {
        JSONString* res = static_cast<JSONString*>(json);
        out = res->toString();
        break;
      }
      case Number: {
        JSONNumber* res = static_cast<JSONNumber*>(json);
        out = res->toString();
        break;
      }
      case Null: {
        out = "\"null\"";
        break;
      }
      case Bool: {
        JSONBool* res = static_cast<JSONBool*>(json);
        out = res->toString();
        break;
      }
      case Array: {
        JSONArray* res = static_cast<JSONArray*>(json);
        out = res->toString();
        break;
      }
      case Object: {
        JSONObject* res = static_cast<JSONObject*>(json);
        out = res->toString();
        break;
      }
      default:
        out = "Unknown";
        break;
    }

    return out;
  }

  void JSON::print() const {
    cout << "type: " << toString();
  }

  string JSON::toString() const {
    string out = "";

    switch (type_) {
      case String:
        out = "String";
        break;
      case Number:
        out = "Number";
        break;
      case Null:
        out = "Null";
        break;
      case Bool:
        out = "Bool";
        break;
      case Array:
        out = "Array";
        break;
      case Object:
        out = "Object";
        break;
      default:
        out = "Unknown";
        break;
    }

    return out;
  }
}
