#ifndef TOKEN_HPP
#define TOKEN_HPP

namespace picoJSON {
enum Token {
  WHITESPACE,
  COLON,
  COMMA,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  LCURLY,
  RCURLY,
  STRING,
  NUMBER,
  JSONTRUE,
  JSONFALSE,
  JSONNULL
};
}

#endif
