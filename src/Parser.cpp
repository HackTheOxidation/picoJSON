#include <picoJSON/Parser.hpp>
#include <picoJSON/Token.hpp>
#include <iterator>
#include <optional>

using namespace std;

namespace picoJSON {

Parser::Parser(const std::string file_name) {
  Reader reader(file_name);
  Lexer lexer(reader.get_content().str());
  tokens_ = lexer.tokenize();
  current_token_pair_ = std::nullopt;
  index_ = 0;
}

Parser::Parser(std::vector<std::pair<Token, string>> tokens)
  : tokens_(tokens), current_token_pair_{}, index_(0) {}

std::optional<JSONObject> Parser::parse_JSON() {
  if (tokens_.empty())
    return std::nullopt;
  return parse_object();
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
    return JSON(JSONType::Bool, value);
  case Token::JSONFALSE:
    return JSON(JSONType::Bool, value);
  case Token::JSONNULL:
    return JSON(JSONType::Null, value);
  case Token::STRING:
    return JSON(JSONType::String, value);
  case Token::NUMBER:
    return JSON(JSONType::Number, value);
  default:
    break;
  }

  return std::nullopt;
}

std::optional<JSONObject> Parser::parse_object() {
  std::unordered_map<std::string, JSON> properties;
  advance();

  do {
    if (!current_token_pair_.has_value())
      return std::nullopt;

    const auto [first, _] = *current_token_pair_;
    switch (first) {
    case Token::RCURLY:
      return JSONObject(JSONType::Object, properties);
    case Token::COMMA:
      advance();
      continue;
    default:
      auto prop = parse_property();
      if (!prop.has_value())
        return std::nullopt;
      properties.insert(prop.value());
      advance();
    }
  } while (current_token_pair_);

  return std::nullopt;
}

std::optional<JSONArray> Parser::parse_array() {
  std::vector<JSON> array;
  advance();

  do {
    if (!current_token_pair_.has_value())
      return std::nullopt;

    const auto [first, _] = *current_token_pair_;
    switch (first) {
    case Token::RBRACE:
      return JSONArray(JSONType::Array, array);
    case Token::COMMA:
      advance();
      continue;
    default:
      auto value = parse_value();
      if (!value.has_value())
        return std::nullopt;
      array.emplace_back(value.value());
      advance();
    }
  } while (current_token_pair_);

  return std::nullopt;
}

std::optional<std::pair<std::string, JSON>> Parser::parse_property() {
  if (!current_token_pair_.has_value())
    return std::nullopt;

  const auto [first, second] = *current_token_pair_;
  switch (first) {
  case Token::STRING: {
    advance();
    if (first == Token::COLON) {
      advance();
      return parse_value().transform([second](const auto& value) { return std::make_pair(second, value); });
    }
  }
  default:
    break;
  }

  return std::nullopt;
}

void Parser::advance() {
  if (index_ < tokens_.size()) {
    current_token_pair_ = tokens_.at(index_);
    index_++;
  } else {
    current_token_pair_ = std::nullopt;
  }
}

std::optional<Content> Parser::get_content() {
  return parse_JSON().transform([](const JSONObject& obj) {
    return Content(obj.get_value());
  });
}

std::vector<std::pair<Token, string>> Parser::get_tokens() const {
  return tokens_;
}

void Parser::print_tokens() const {
  for (const auto &[token, value] : tokens_) {
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

    std::cout << "value: " << value << '\n';
  }
}

void Parser::print() const {
  for (const auto& [token, value] : tokens_) {
    switch (token) {
    case Token::STRING:
      std::cout << "STRING ";
      break;
    case Token::NUMBER:
      std::cout << "NUMBER ";
      break;
    case Token::JSONTRUE:
      std::cout << "JSONTRUE ";
      break;
    case Token::JSONFALSE:
      std::cout << "JSONFALSE ";
      break;
    case Token::JSONNULL:
      std::cout << "JSONNULL ";
      break;
    case Token::WHITESPACE:
      continue;
    default:
      break;
    }
    std::cout << value << " ";
  }
}

} // namespace picoJSON
