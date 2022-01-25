#ifndef JSONARRAY_HPP
#define JSONARRAY_HPP

#include "JSON.hpp"
#include <vector>

using namespace std;

namespace picoJSON {

class JSONArray : public JSON {
public:
  JSONArray(JSONType type, vector<JSON *> *value);

  vector<JSON *> *getValue() const;

  string toString() const;

  void print() const;

private:
  vector<JSON *> *value_;
};
} // namespace picoJSON

#endif
