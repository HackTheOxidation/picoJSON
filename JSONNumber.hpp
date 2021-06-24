#ifndef JSONNUMBER_HPP
#define JSONNUMBER_HPP

#include "JSON.hpp"
#include <sstream>

using namespace std;

namespace picoJSON {

  class JSONNumber : public JSON {
    public:
      JSONNumber(JSONType type, float value) : JSON(type), value_(value) {

      }

      float getValue() const {
        return value_;
      }

      string toString() const {
        ostringstream ss;
        ss << value_;
        return ss.str(); 
      }

    private:
      float value_;
  };
}

#endif
