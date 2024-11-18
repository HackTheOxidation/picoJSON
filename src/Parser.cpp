#include <Parser.hpp>
#include <Token.hpp>
#include <iterator>
#include <optional>

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
  if (!tokens_.empty()) {
    return parse();
  }
}

std::optional<JSON> Parser::parse() {
  advance();
  return parse_value();
}

std::optional<JSON> Parser::parse_value() {
  const auto [tok, value] = *current_token_pair_;

  switch (tok) {
  case Token::LCURLY:
    return parse_object();
  case Token::LBRACE:
    return parse_array();
  case Token::JSONTRUE:
    return JSON(Bool, value);
  case Token::JSONFALSE:
    return JSON(Bool, value);
  case Token::JSONNULL:
    return JSON(Null, value);
  case Token::STRING:
    return JSON(String, value);
  case Token::NUMBER:
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
      return std::nullopt;

    switch (current_token_pair_.first) {
    case Token::RCURLY:
      return JSONObject(JSONType::Object, properties);
    case Token::COMMA:
      advance();
    default:
      auto prop = parse_property();
      if (!prop.has_value())
        return std::nullopt;
      properties.push_back(prop.value());
      advance();
    }
  } while (current_token_pair_ != nullptr);

  return std::nullopt;
}

std::optional<JSON> Parser::parse_array() {
  std::vector<std::shared_ptr<JSON>> array;
  advance();

  do {
    if (current_token_pair_ == nullptr)
      return std::nullopt;

    switch (current_token_pair_.first) {
    case Token::RBRACE:
      return JSONArray(JSONType::Array, array);
    case Token::COMMA:
      advance();
    default:
      auto value = parse_value();
      if (!value.has_value())
        return std::nullopt;
      array.push_back(value.value());
      advance();
    }
  } while (current_token_pair_ != nullptr);

  return std::nullopt;
}

std::optional<JSONProperty> Parser::parse_property() {
  if (current_token_pair_ == nullptr)
    return std::nullopt;

  const auto [first, second] = *current_token_pair_;
  switch (first) {
  case Token::STRING: {
    advance();
    if (first == Token::COLON) {
      advance();
      return parse_value().and_then([second](auto value) { return JSONProperty(second, value); });
    }
  }
  default:
    break;
  }
}

void Parser::advance() {
  if (index_ < tokens_.size()) {
    current_token_pair_ = tokens_.at(index_);
    index_++;
  } else {
    current_token_pair_ = nullptr;
  }
}

std::optional<Content> Parser::get_content() {
  parse_JSON().and_then([](auto json) {
    JSONObject obj = JSONObject(json);
    return obj.get_value().and_then([](auto value) { return Content(value); });
  });
}

std::vector<std::pair<Token, string>> Parser::get_tokens() const {
  return tokens_;
}

void Parser::print_tokens() const {
  for (const[token, value] : tokens_) {
    std::cout << "type: ";
    switch (token) {
    case Token::STRING:
      std::cout << "STRING, ";
      break;
    case Token::NUMBER:
      std::cout << "NUMBER, ";
      break;
    case Token::WHITESPACE:
      std::cout << "WHITESPACE, ";
      break;
    case Token::COLON:
      std::cout << "COLON, ";
      break;
    case Token::COMMA:
      std::cout << "COMMA, ";
      break;
    case Token::LPAREN:
      std::cout << "LPAREN, ";
      break;
    case Token::RPAREN:
      std::cout << "RPAREN, ";
      break;
    case Token::LBRACE:
      std::cout << "LBRACE, ";
      break;
    case Token::RBRACE:
      std::cout << "RBRACE, ";
      break;
    case Token::LCURLY:
      std::cout << "LCURLY, ";
      break;
    case Token::RCURLY:
      std::cout << "RCURLY, ";
      break;
    case Token::JSONTRUE:
      std::cout << "JSONTRUE, ";
      break;
    case Token::JSONFALSE:
      std::cout << "JSONFALSE, ";
      break;
    case Token::JSONNULL:
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
