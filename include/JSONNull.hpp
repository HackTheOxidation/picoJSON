#ifndef JSONNULL_HPP
#define JSONNULL_HPP

#include "JSON.hpp"

using namespace std;

namespace picoJSON {
class JSONNull : public JSON {
public:
  JSONNull(JSONType type);

  long int *getValue() const;

  string toString() const;
};
} // namespace picoJSON

#endif
