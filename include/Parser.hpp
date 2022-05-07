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

  JSON *parseJSON() {
    if (!tokens_->empty()) {
      return parse();
    } else {
      return nullptr;
    }
  }

  JSON *parse() {
    advance();
    try {
      return parseValue();
    } catch (ParserException e) {
      throw ParserException("");
    }
  }

  JSON *parseValue() {
    Token tok = currentTokenPair_->first;

    switch (tok) {
    case LCURLY:
      return parseObject();
    case LBRACE:
      return parseArray();
    case JSONTRUE:
      return new JSON(Bool, currentTokenPair_->second);
    case JSONFALSE:
      return new JSON(Bool, currentTokenPair_->second);
    case JSONNULL:
      return new JSON(Null, currentTokenPair_->second);
    case STRING:
      return new JSON(String, currentTokenPair_->second);
    case NUMBER:
      return new JSON(Number, currentTokenPair_->second);
    default:
      break;
    }

    throw ParserException("");
  }

  JSON *parseObject() {
    vector<JSONProperty *> *properties = new vector<JSONProperty *>();
    advance();

    do {
      if (currentTokenPair_ == nullptr)
        throw ParserException("");

      switch (currentTokenPair_->first) {
      case RCURLY:
        return new JSONObject(Object, properties);
      case COMMA:
        advance();
      default:
        properties->push_back(parseProperty());
        advance();
      }
    } while (currentTokenPair_ != nullptr);

    throw ParserException("");
  }

  JSON *parseArray() {
    vector<JSON *> *array = new vector<JSON *>();
    advance();

    do {
      if (currentTokenPair_ == nullptr)
        throw ParserException("");

      switch (currentTokenPair_->first) {
      case RBRACE:
        return new JSONArray(Array, array);
      case COMMA:
        advance();
      default:
        array->push_back(parseValue());
        advance();
      }
    } while (currentTokenPair_ != nullptr);

    throw ParserException("");
  }

  JSONProperty *parseProperty() {
    if (currentTokenPair_ == nullptr)
      throw ParserException("");

    switch (currentTokenPair_->first) {
    case STRING: {
      string str = currentTokenPair_->second;
      advance();
      if (currentTokenPair_->first == COLON) {
        advance();
        return new JSONProperty(str, parseValue());
      } else
        throw ParserException("");
    }
    default:
      break;
    }

    throw ParserException("");
  }

  void advance() {
    if (index_ < tokens_->size()) {
      currentTokenPair_ = tokens_->at(index_);
      index_++;
    } else {
      currentTokenPair_ = nullptr;
    }
  }
};
} // namespace picoJSON

#endif
