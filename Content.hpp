#ifndef CONTENT_HPP
#define CONTENT_HPP

#include "JSON.hpp"
#include "JSONArray.hpp"
#include "JSONBool.hpp"
#include "JSONNull.hpp"
#include "JSONNumber.hpp"
#include "JSONObject.hpp"
#include "JSONString.hpp"
#include "JSONProperty.hpp"
#include <iostream>
#include <vector>

using namespace std;

namespace picoJSON {

  class Content {
    private:
      vector<JSONProperty*>* properties_;

      JSONProperty* getProperty(string key) const {
        JSONProperty* res;
        for (JSONProperty* prop : *properties_) {
          if (prop->getKey().compare(key) == 0)
            return prop;
        }

        return nullptr;
      }

    public:
      Content(vector<JSONProperty*>* properties) : properties_(properties) {
      }

      vector<JSONProperty*> getProperties() const {
        return *properties_;
      }

      bool search(string key) const {
        for (JSONProperty* prop : *properties_) {
          if (prop->getKey().compare(key) == 0) {
            return true;
          }
        }

        return Null;
      }

      bool search(string key, JSONType& type) const {
        for (JSONProperty* prop : *properties_) {
          if (prop->getKey().compare(key) == 0) {
            type = prop->getValue()->getType();
            return true;
          }
        }
        return Null;
      }

      string extractString(string key) const {
        for (JSONProperty* prop : *properties_) {
          if (prop->getKey().compare(key) == 0 && prop->getValue()->getType() == String) {
            JSONString* jstr = static_cast<JSONString*>(prop->getValue());
            return jstr->getValue();
          }
        }
        
        return 0; 
      }

      float extractNumber(string key) const {
        for (JSONProperty* prop : *properties_) {
          if (prop->getKey().compare(key) == 0 && prop->getValue()->getType() == Number) {
            JSONNumber* jnum = static_cast<JSONNumber*>(prop->getValue());
            return jnum->getValue();
          }
        }

        return (float) NULL;
      }

      void* getValue(string key, JSONType type) const {
        if (search(key, type)) {
          JSONProperty* prop = getProperty(key);
          switch (type) {
            case String: {
                           JSONString* jstr = static_cast<JSONString*>(prop->getValue());
                           string* retVal = new string(jstr->getValue());
                           return (void*) retVal;
                           break;
                         }
            case Number: {
                           JSONNumber* jnum = static_cast<JSONNumber*>(prop->getValue());
                           float* retVal = new float(jnum->getValue());
                           return (void*) retVal;
                           break;
                         }
            case Null: {
                         return nullptr;
                         break;
                       }
            case Bool: {
                         JSONBool* jbool = static_cast<JSONBool*>(prop->getValue());
                         bool* retVal = new bool(jbool->getValue());
                         return (void*) retVal;
                         break;
                       }
            case Array: {
                          return (void*) static_cast<JSONArray*>(prop->getValue());
                          break;
                        }
            case Object: {
                           return (void*) static_cast<JSONObject*>(prop->getValue());
                           break;
                         }
          }
        }
        
        return nullptr;
      }

      void print() const {
        cout << "{" << endl;
        for (JSONProperty* prop : *properties_) {
          cout << "\t";
          prop->print();
          cout << "," << endl;
        }
        cout << "}" << endl;
      }
  };
}

#endif
