#include <JSONProperty.hpp>
#include <Parser.hpp>
#include <iterator>

using namespace std;

namespace picoJSON {

Parser::Parser(string fileName) {
  Reader reader(fileName);
  Lexer lexer(reader.getContent());
  tokens_ = lexer.tokenize();
  currentTokenPair_ = nullptr;
  index_ = 0;
}

Parser::Parser(vector<pair<Token, string> *> *tokens)
    : tokens_(tokens), currentTokenPair_(nullptr), index_(0) {}

JSON *Parser::parseJSON() {
  if (!tokens_->empty()) {
    return parse();
  } else {
    return nullptr;
  }
}

JSON *Parser::parse() {
  this->advance();
  try {
    return parseValue();
  } catch (ParserException e) {
    throw ParserException("");
  }
}

JSON *Parser::parseValue() {
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

JSON *Parser::parseObject() {
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

JSON *Parser::parseArray() {
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

JSONProperty *Parser::parseProperty() {
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

void Parser::advance() {
  if (index_ < tokens_->size()) {
    currentTokenPair_ = tokens_->at(index_);
    index_++;
  } else {
    currentTokenPair_ = nullptr;
  }
}

Content Parser::getContent() {
  try {
    JSON *json = parseJSON();
    JSONObject *obj = static_cast<JSONObject *>(json);
    return *(new Content(obj->getValue()));
  } catch (ParserException e) {
    return *(new Content(nullptr));
  }
}

vector<pair<Token, string> *> *Parser::getTokens() const { return tokens_; }

void Parser::printTokens() const {
  for (pair<Token, string> *p : *tokens_) {
    cout << "type: ";
    switch (p->first) {
    case STRING:
      cout << "STRING, ";
      break;
    case NUMBER:
      cout << "NUMBER, ";
      break;
    case WHITESPACE:
      cout << "WHITESPACE, ";
      break;
    case COLON:
      cout << "COLON, ";
      break;
    case COMMA:
      cout << "COMMA, ";
      break;
    case LPAREN:
      cout << "LPAREN, ";
      break;
    case RPAREN:
      cout << "RPAREN, ";
      break;
    case LBRACE:
      cout << "LBRACE, ";
      break;
    case RBRACE:
      cout << "RBRACE, ";
      break;
    case LCURLY:
      cout << "LCURLY, ";
      break;
    case RCURLY:
      cout << "RCURLY, ";
      break;
    case JSONTRUE:
      cout << "JSONTRUE, ";
      break;
    case JSONFALSE:
      cout << "JSONFALSE, ";
      break;
    case JSONNULL:
      cout << "JSONNULL, ";
      break;
    }

    cout << "value: " << p->second << endl;
  }
}

void Parser::print() const {
  for (pair<Token, string> *p : *tokens_) {
    string tok = "";
    switch (p->first) {
    case STRING:
      tok = "STRING ";
      break;
    case NUMBER:
      tok = "NUMBER ";
      break;
    case JSONTRUE:
      tok = "JSONTRUE ";
      break;
    case JSONFALSE:
      tok = "JSONFALSE ";
      break;
    case JSONNULL:
      tok = "JSONNULL ";
      break;
    case WHITESPACE:
      continue;
    default:
      break;
    }

    if (tok != "") {
      cout << tok;
    }
    cout << p->second << " ";
  }
}

} // namespace picoJSON
