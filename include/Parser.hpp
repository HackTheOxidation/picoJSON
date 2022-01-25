#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include "Reader.hpp"
#include "Lexer.hpp"
#include "JSON.hpp"
#include "JSONBool.hpp"
#include "JSONNull.hpp"
#include "JSONNumber.hpp"
#include "JSONString.hpp"
#include "JSONArray.hpp"
#include "JSONObject.hpp"
#include "JSONProperty.hpp"
#include "Content.hpp"

using namespace std;

namespace picoJSON {

  class Parser {
    public:
      Parser(string fileName);

      Parser(vector<pair<Token, string>*>* tokens);

      Content getContent();

      vector<pair<Token, string>*>* getTokens() const;

      void printTokens() const;

      void print() const;

    private:
      vector<pair<Token, string>*>* tokens_;
      pair<Token, string>* currentTokenPair_;
      int index_;

      JSON* parseJSON() {
        if (!tokens_->empty()) {
          return parse();
        } else {
          return nullptr;
        }
      }

      JSON* parse() {
        advance();
        try {
          return parseValue();
        } catch (exception e) {
          throw exception();
        }
      }

      JSON* parseValue() {
        Token tok = currentTokenPair_->first;

        switch (tok) {
          case LCURLY:
            return parseObject();
          case LBRACE:
            return parseArray();
          case JSONTRUE:
            return new JSONBool(Bool, true);
          case JSONFALSE:
            return new JSONBool(Bool, false);
          case JSONNULL:
            return new JSONNull(Null);
          case STRING:
            return new JSONString(String, currentTokenPair_->second);
          case NUMBER:
            return new JSONNumber(Number, stof(currentTokenPair_->second));
          default:
            break;
        }

        throw exception();
      }

      JSON* parseObject() {
        vector<JSONProperty*>* properties = new vector<JSONProperty*>();
        advance();
        
        do {
          if (currentTokenPair_ == nullptr)
            throw exception();

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

        throw exception();
      }

      JSON* parseArray() {
        vector<JSON*>* array = new vector<JSON*>();
        advance();

        do {
          if (currentTokenPair_ == nullptr)
            throw exception();

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

        throw exception();
      }

      JSONProperty* parseProperty() {
        if (currentTokenPair_ == nullptr) 
          throw exception();

        switch (currentTokenPair_->first) {
          case STRING: {
            string str = currentTokenPair_->second;
            advance();
            if (currentTokenPair_->first == COLON) {
                advance();
                return new JSONProperty(str, parseValue());
            } else
              throw exception();
          }
          default:
            break;
        }

        throw exception();
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

}

#endif
