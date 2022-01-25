#ifndef CONTENT_HPP
#define CONTENT_HPP

#include "JSON.hpp"
#include "JSONArray.hpp"
#include "JSONBool.hpp"
#include "JSONNull.hpp"
#include "JSONNumber.hpp"
#include "JSONObject.hpp"
#include "JSONProperty.hpp"
#include "JSONString.hpp"
#include <iostream>
#include <vector>

using namespace std;

namespace picoJSON {

class Content {
private:
  vector<JSONProperty *> *properties_;

  JSONProperty *getProperty(string key) const {
    for (JSONProperty *prop : *properties_) {
      if (prop->getKey().compare(key) == 0)
        return prop;
    }

    return nullptr;
  }

public:
  Content(vector<JSONProperty *> *properties);

  vector<JSONProperty *> getProperties() const;

  bool search(string key) const;

  bool search(string key, JSONType &type) const;

  string extractString(string key) const;

  float extractNumber(string key) const;

  void *getValue(string key, JSONType type) const;

  JSON &operator[](string key);

  JSON operator[](string key) const;

  void print() const;
};
} // namespace picoJSON

#endif
