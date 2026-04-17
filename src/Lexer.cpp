#include <Lexer.hpp>
#include <cctype>
#include <cstddef>
#include <iterator>
#include <sstream>

namespace picoJSON {

Lexer::Lexer(const std::string json) : json_(json) { tokenize(); }

void Lexer::tokenize_null(Tokens& tokens, std::string::const_iterator& iter, std::size_t& line_no) {
  const auto dist = std::distance(json_.cbegin(), iter) - 1;
  std::string buffer = json_.substr(dist, 4);
  if (buffer == "null") {
    tokens.push_back(std::pair(Token::JSONNULL, buffer));
    std::advance(iter, 4);
  }
}

void Lexer::tokenize_bool(Tokens& tokens, std::string::const_iterator& iter, std::size_t& line_no) {
  const auto dist = std::distance(json_.cbegin(), iter) - 1;
  std::string buffer = json_.substr(dist, 4);

  if (buffer == "true") {
    tokens.push_back(std::pair(Token::JSONTRUE, buffer));
    std::advance(iter, 4);
    return;
  }

  buffer = json_.substr(dist, 5);
  if (buffer == "false") {
    tokens.push_back(std::pair(Token::JSONFALSE, buffer));
    std::advance(iter, 5);
    return;
  }
}

void tokenize_number(Tokens& tokens, std::string::const_iterator& iter, std::size_t& line_no) {
  std::string buffer = "";
  while (std::isdigit(*iter)) {
    buffer += *iter;
    iter++;
  }

  if (*iter == '.') {
    buffer += *(iter++);
    while (std::isdigit(*iter)) {
      buffer += *iter;
      iter++;
    }
  }

  tokens.push_back(std::pair(Token::NUMBER, buffer));
}

void tokenize_string(Tokens& tokens, std::string::const_iterator& iter, std::size_t& line_no) {
  std::string buffer = "";
  while (*iter != '\"') {
    buffer += *iter;
    iter++;
  }
  tokens.push_back(std::pair(Token::STRING, buffer));
}

Tokens Lexer::tokenize() {
  Tokens tokens{};

  std::size_t line_no = 1;
  for (auto iter = json_.cbegin(); iter != json_.cend(); iter++) {
    c = *iter;
    if (c == '{') {
      tokens.push_back(std::pair(Token::LCURLY, "{"));
    } else if (c == '[') {
      tokens.push_back(std::pair(Token::LBRACE, "["));
    } else if (c == '(') {
      tokens.push_back(std::pair(Token::LPAREN, "("));
    } else if (c == ',') {
      tokens.push_back(std::pair(Token::COMMA, ","));
    } else if (c == ':') {
      tokens.push_back(std::pair(Token::COLON, ":"));
    } else if (c == '\"') {
      tokenize_string(tokens, ++iter, line_no);
    } else if (std::isdigit(c)) {
      tokenize_number(tokens, iter, line_no);
    } else {
      // Raise exception.
    }
  }

  return tokens;
}
} // namespace picoJSON
