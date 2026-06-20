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

  void tokenize_null(Tokens &tokens, std::string::const_iterator& iter, std::size_t &line_no);
  void tokenize_bool(Tokens &tokens, std::string::const_iterator& iter, std::size_t &line_no);
  void tokenize_number(Tokens &tokens, std::string::const_iterator& iter, std::size_t &line_no);
  void tokenize_string(Tokens &tokens, std::string::const_iterator& iter, std::size_t &line_no);
};
} // namespace picoJSON

#endif
