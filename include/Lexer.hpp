#ifndef LEXER_HPP
#define LEXER_HPP

#include "Errors.hpp"
#include "Reader.hpp"
#include "Token.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace picoJSON {
  using TokenPair = std::pair<Token, std::string>;
  using Tokens = std::vector<std::pair<Token, std::string>>;

class Lexer {
public:
  Lexer(const std::string json);
  Tokens tokenize();

private:
  std::string json_;
};

} // namespace picoJSON

#endif
