#ifndef PARSER_HPP
#define PARSER_HPP

#include "Content.hpp"
#include "JSON.hpp"
#include "JSONArray.hpp"
#include "JSONObject.hpp"
#include "Lexer.hpp"
#include "Reader.hpp"
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace picoJSON {

class Parser {
public:
  Parser(const std::string file_name);
  Parser(std::vector<std::pair<Token, std::string>> tokens);
  std::optional<Content> get_content();
  std::vector<std::pair<Token, std::string>> get_tokens() const;
  void print_tokens() const;
  void print() const;

private:
  std::vector<std::shared_ptr<std::pair<Token, std::string>>> tokens_;
  std::shared_ptr<std::pair<Token, std::string>> current_token_pair_;
  long unsigned int index_;

  std::optional<JSON> parse_JSON();
  std::optional<JSON> parse();
  std::optional<JSON> parse_value();
  std::optional<JSON> parse_object();
  std::optional<JSON> parse_array();
  void advance();
};
} // namespace picoJSON

#endif
