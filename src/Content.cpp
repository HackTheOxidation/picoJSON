#include <Content.hpp>
#include <JSONArray.hpp>
#include <JSONObject.hpp>
#include <JSONProperty.hpp>
#include <exception>
#include <stdexcept>
#include <string>

namespace picoJSON {

vector<JSONProperty *> Content::getProperties() const { return *properties_; }

Content::Content(vector<JSONProperty *> *properties)
    : properties_(properties) {}

bool Content::search(string key) const {
  for (JSONProperty *prop : *properties_) {
    if (prop->getKey().compare(key) == 0) {
      return true;
    }
  }

  return false;
}

bool Content::search(string key, JSONType &type) const {
  for (JSONProperty *prop : *properties_) {
    if (prop->getKey().compare(key) == 0) {
      type = prop->getValue()->getType();
      return true;
    }
  }
  return false;
}

JSON &Content::getValue(string key) const {
  if (!search(key))
    throw 1;
  JSONProperty *prop = getProperty(key);

  switch (prop->getValue()->getType()) {
  case Array:
    return *static_cast<JSONArray *>(prop->getValue());
  case Object:
    return *static_cast<JSONObject *>(prop->getValue());
  }

  return *prop->getValue();
}

JSON &Content::operator[](std::string key) { return getValue(key); }

JSON Content::operator[](std::string key) const {
  JSONProperty *prop = getProperty(key);
  if (prop == nullptr)
    throw out_of_range("");

  return (*prop->getValue());
}

void Content::print() const {
  cout << "{" << endl;
  for (JSONProperty *prop : *properties_) {
    cout << "\t";
    prop->print();
    cout << "," << endl;
  }
  cout << "}" << endl;
}

JSONProperty* Content::getProperty(string key) const {
  for (JSONProperty *prop : *properties_) {
    if (prop->getKey().compare(key) == 0)
      return prop;
    }

    return nullptr;
}
} // namespace picoJSON
