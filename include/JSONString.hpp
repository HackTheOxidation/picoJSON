#ifndef JSONSTRING_HPP
#define JSONSTRING_HPP

#include "JSON.hpp"

using namespace std;

namespace picoJSON {

  class JSONString : public JSON {
    public:
      JSONString(JSONType type, string value);

      string getValue() const; 

      string toString() const;

    private:
      string value_;
  };
}

#endif
