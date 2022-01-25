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
      Content(vector<JSONProperty*>* properties);

      vector<JSONProperty*> getProperties() const;

      bool search(string key) const;

      bool search(string key, JSONType& type) const;

      string extractString(string key) const;

      float extractNumber(string key) const;

      void* getValue(string key, JSONType type) const;

      void print() const;
  };
}

#endif
