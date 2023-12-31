#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <exception>
#include <iostream>
#include <string>

using namespace std;

namespace picoJSON {
class SyntaxException {
public:
  SyntaxException(string &msg);
  SyntaxException(string &msg, unsigned int line);
  SyntaxException(string &msg, string suggestion);
  SyntaxException(string &msg, string suggestion, unsigned int line);

  const char *message() const noexcept;

private:
  string msg_;
  string suggestion_;
  unsigned int line_;
};

class ParserException {
public:
  ParserException(string msg);

  const char *message() const noexcept;

private:
  string msg_;
};
} // namespace picoJSON

#endif
