#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include "JSON.hpp"
#include "JSONProperty.hpp"
#include <vector>

using namespace std;

namespace picoJSON {

class JSONObject : public JSON {
public:
  JSONObject(JSONType type, vector<JSONProperty *> *value);

  vector<JSONProperty *> *getValue() const;

  string toString() const;

private:
  vector<JSONProperty *> *value_;
};
} // namespace picoJSON

#endif
