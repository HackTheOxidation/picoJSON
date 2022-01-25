#ifndef LEXER_HPP
#define LEXER_HPP

#include "Errors.hpp"
#include "Reader.hpp"
#include "Token.hpp"
#include <iostream>
#include <vector>

using namespace std;

namespace picoJSON {

class Lexer {
public:
  Lexer(string json);

  vector<pair<Token, string> *> *tokenize();

private:
  string json_;
};

} // namespace picoJSON

#endif
