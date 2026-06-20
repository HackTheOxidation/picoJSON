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
  std::vector<std::pair<Token, std::string>> tokens_;
  std::optional<std::pair<Token, std::string>> current_token_pair_;
  long unsigned int index_;

  std::optional<JSONObject> parse_JSON();
  std::optional<JSON> parse();
  std::optional<JSON> parse_value();
  std::optional<JSONObject> parse_object();
  std::optional<JSONArray> parse_array();
  std::optional<std::pair<std::string, JSON>> parse_property();
  void advance();
};
} // namespace picoJSON

#endif
