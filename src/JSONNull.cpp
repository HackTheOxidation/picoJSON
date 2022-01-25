#include <JSONNull.hpp>

using namespace std;

namespace picoJSON {
  JSONNull::JSONNull(JSONType type) : JSON(type) {}

  long int* JSONNull::getValue() const {
    return NULL;
  }

  string JSONNull::toString() const {
    return "\"null\"";
  }
}
