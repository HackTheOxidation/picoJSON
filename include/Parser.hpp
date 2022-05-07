#ifndef PARSER_HPP
#define PARSER_HPP

#include "Content.hpp"
#include "JSON.hpp"
#include "JSONArray.hpp"
#include "JSONObject.hpp"
#include "JSONProperty.hpp"
#include "Lexer.hpp"
#include "Reader.hpp"
#include <iostream>
#include <vector>

using namespace std;

namespace picoJSON {

class Parser {
public:
  Parser(string fileName);
  Parser(vector<pair<Token, string> *> *tokens);
  Content getContent();
  vector<pair<Token, string> *> *getTokens() const;
  void printTokens() const;
  void print() const;

private:
  vector<pair<Token, string> *> *tokens_;
  pair<Token, string> *currentTokenPair_;
  long unsigned int index_;

  JSON *parseJSON();
  JSON *parse();
  JSON *parseValue();
  JSON *parseObject();
  JSON *parseArray();
  JSONProperty *parseProperty();
  void advance();
};
} // namespace picoJSON

#endif
