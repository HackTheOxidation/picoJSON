#ifndef READER_HPP
#define READER_HPP

#include "Token.hpp"
#include <fstream>
#include <iostream>

using namespace std;

namespace picoJSON {
const string Whitespace = "\r\n\t ";
const string Digits = "1234567890";

class Reader {
public:
  Reader(string fileName);

  string getContent() const;

private:
  string fileName_;
};
} // namespace picoJSON

#endif
