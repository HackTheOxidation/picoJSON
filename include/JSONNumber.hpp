#ifndef JSONNUMBER_HPP
#define JSONNUMBER_HPP

#include "JSON.hpp"
#include <sstream>

using namespace std;

namespace picoJSON {

class JSONNumber : public JSON {
public:
  JSONNumber(JSONType type, float value);

  float getValue() const;

  string toString() const;

private:
  float value_;
};
} // namespace picoJSON

#endif
