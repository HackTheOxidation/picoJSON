#include <Content.hpp>
#include <exception>
#include <picoJSON/Content.hpp>
#include <picoJSON/JSONProperty.hpp>
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

string Content::extractString(string key) const {
  for (JSONProperty *prop : *properties_) {
    if (prop->getKey().compare(key) == 0 &&
        prop->getValue()->getType() == String) {
      JSONString *jstr = static_cast<JSONString *>(prop->getValue());
      return jstr->getValue();
    }
  }

  return 0;
}

float Content::extractNumber(string key) const {
  for (JSONProperty *prop : *properties_) {
    if (prop->getKey().compare(key) == 0 &&
        prop->getValue()->getType() == Number) {
      JSONNumber *jnum = static_cast<JSONNumber *>(prop->getValue());
      return jnum->getValue();
    }
  }

  return (float)NULL;
}

void *Content::getValue(string key, JSONType type) const {
  if (search(key, type)) {
    JSONProperty *prop = getProperty(key);
    switch (type) {
    case String: {
      JSONString *jstr = static_cast<JSONString *>(prop->getValue());
      string *retVal = new string(jstr->getValue());
      return (void *)retVal;
      break;
    }
    case Number: {
      JSONNumber *jnum = static_cast<JSONNumber *>(prop->getValue());
      float *retVal = new float(jnum->getValue());
      return (void *)retVal;
      break;
    }
    case Null: {
      return nullptr;
      break;
    }
    case Bool: {
      JSONBool *jbool = static_cast<JSONBool *>(prop->getValue());
      bool *retVal = new bool(jbool->getValue());
      return (void *)retVal;
      break;
    }
    case Array: {
      return (void *)static_cast<JSONArray *>(prop->getValue());
      break;
    }
    case Object: {
      return (void *)static_cast<JSONObject *>(prop->getValue());
      break;
    }
    }
  }

  return nullptr;
}

JSON &Content::operator[](std::string key) {
  JSONProperty *prop = getProperty(key);
  if (prop == nullptr)
    throw std::exception();

  return (*prop->getValue());
}

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
} // namespace picoJSON
