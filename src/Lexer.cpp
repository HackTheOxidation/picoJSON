#include <Lexer.hpp>
#include <cstddef>
#include <sstream>

namespace picoJSON {

Lexer::Lexer(const std::string json) : json_(json) { tokenize(); }

void tokenize_null(Tokens &tokens, std::size_t &line_no) {
  std::string buffer = "";
  tokens.push_back(std::pair<Token, std::string>(Token::JSONNULL, buffer));
  line_no++;
}

void tokenize_bool(Tokens &tokens, std::size_t &line_no) {
  std::string buffer = "";
  tokens.push_back(std::pair<Token, std::string>(Token::JSONTRUE, buffer));
  line_no++;
}

void tokenize_number(Tokens &tokens, std::size_t &line_no) {
  std::string buffer = "";
  tokens.push_back(std::pair<Token, std::string>(Token::NUMBER, buffer));
  line_no++;
}

void tokenize_string(Tokens &tokens, std::size_t &line_no) {
  std::string buffer = "";
  tokens.push_back(std::pair<Token, std::string>(Token::STRING, buffer));
  line_no++;
}

Tokens Lexer::tokenize() {
  Tokens tokens{};
  std::string buffer;

  std::size_t line_no = 1;
  for (char c : json_) {
    if (c == '{') {
      tokens.push_back(std::pair<Token, std::string>(Token::LCURLY, buffer));
    } else if (c == '[') {
      tokens.push_back(std::pair<Token, std::string>(Token::LBRACE, buffer));
    } else if (c == '(') {
      tokens.push_back(std::pair<Token, std::string>(Token::LPAREN, buffer));
    } else if (c == ',') {
      tokens.push_back(std::pair<Token, std::string>(Token::NUMBER, buffer));
    } else if (c == ':') {
      tokens.push_back(std::pair<Token, std::string>(Token::COLON, buffer));
    } else if (c == '\"') {
      tokenize_string(tokens, line_no);
    } else {
      // Raise exception.
    }
  }

  return tokens;
}
} // namespace picoJSON
