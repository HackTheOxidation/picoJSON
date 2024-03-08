#ifndef LEXER_HPP
#define LEXER_HPP

#include "Errors.hpp"
#include "Reader.hpp"
#include "Token.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace picoJSON {

class Lexer {
public:
  Lexer(const std::string json);
  std::vector<std::pair<Token, std::string>> tokenize();

private:
  std::string json_;
};

} // namespace picoJSON

#endif
