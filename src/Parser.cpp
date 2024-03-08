#include <JSONProperty.hpp>
#include <Parser.hpp>
#include <iterator>

using namespace std;

namespace picoJSON {

  Parser::Parser(const std::string file_name) {
    Reader reader(file_name);
    Lexer lexer(reader.get_content());
    tokens_ = lexer.tokenize();
    current_token_pair_ = nullptr;
    index_ = 0;
  }

  Parser::Parser(std::vector<std::pair<Token, string>> tokens)
    : tokens_(tokens), current_token_pair_(nullptr), index_(0) {}

  std::optional<JSON> Parser::parse_JSON() {
    if (!tokens.empty()) {
      return parse();
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

  std::optional<JSON> Parser::parse_value() {
    const auto [tok, value] = *current_token_pair_;

    switch (tok) {
    case LCURLY:
      return parseObject();
    case LBRACE:
      return parseArray();
    case JSONTRUE:
      return JSON(Bool, value);
    case JSONFALSE:
      return JSON(Bool, value);
    case JSONNULL:
      return JSON(Null, value);
    case STRING:
      return JSON(String, value);
    case NUMBER:
      return JSON(Number, value);
    default:
      break;
    }
  }

  std::optional<JSON> Parser::parse_object() {
    std::vector<JSONProperty> properties;
    advance();

    do {
      if (current_token_pair_ == nullptr)
        throw ParserException("");

      switch (currentTokenPair_.first) {
      case RCURLY:
        return JSONObject(Object, properties);
      case COMMA:
        advance();
      default:
        properties.push_back(parse_property());
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
  parse_JSON().and_then
  try {
    JSON *json = parseJSON();
    JSONObject *obj = static_cast<JSONObject *>(json);
    return *(new Content(obj->getValue()));
  } catch (ParserException e) {
    return *(new Content(nullptr));
  }
}

  std::vector<std::pair<Token, string>> Parser::get_tokens() const { return tokens_; }

void Parser::print_tokens() const {
  for (const [token, value] : tokens_) {
    std::cout << "type: ";
    switch (token) {
    case STRING:
      std::cout << "STRING, ";
      break;
    case NUMBER:
      std::cout << "NUMBER, ";
      break;
    case WHITESPACE:
      std::cout << "WHITESPACE, ";
      break;
    case COLON:
      std::cout << "COLON, ";
      break;
    case COMMA:
      std::cout << "COMMA, ";
      break;
    case LPAREN:
      std::cout << "LPAREN, ";
      break;
    case RPAREN:
      std::cout << "RPAREN, ";
      break;
    case LBRACE:
      std::cout << "LBRACE, ";
      break;
    case RBRACE:
      std::cout << "RBRACE, ";
      break;
    case LCURLY:
      std::cout << "LCURLY, ";
      break;
    case RCURLY:
      std::cout << "RCURLY, ";
      break;
    case JSONTRUE:
      std::cout << "JSONTRUE, ";
      break;
    case JSONFALSE:
      std::cout << "JSONFALSE, ";
      break;
    case JSONNULL:
      std::cout << "JSONNULL, ";
      break;
    }

    sdt::cout << "value: " << value << '\n';
  }
}

void Parser::print() const {
  for (const auto [token, value] : tokens_) {
    switch (token) {
    case STRING:
      std::cout << "STRING ";
      break;
    case NUMBER:
      std::cout << "NUMBER ";
      break;
    case JSONTRUE:
      std::cout << "JSONTRUE ";
      break;
    case JSONFALSE:
      std::cout << "JSONFALSE ";
      break;
    case JSONNULL:
      std::cout << "JSONNULL ";
      break;
    case WHITESPACE:
      continue;
    default:
      break;
    }
    std::cout << value << " ";
  }
}

} // namespace picoJSON
