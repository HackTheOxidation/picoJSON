#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <exception>
#include <iostream>
#include <string>
#include <string_view>

namespace picoJSON {
class SyntaxException {
public:
  SyntaxException(const std::string_view msg,
                  const std::string_view suggestion = "",
                  const unsigned int line = 0)
    : msg_(msg), suggestion_(suggestion), line_(line) {}

  const std::string_view message() const noexcept;

private:
  const std::string_view msg_;
  const std::string_view suggestion_;
  const unsigned int line_ = 0;
};

struct ParserException {
public:
  constexpr ParserException(const std::string_view msg)
    : message(msg) {}
  const std::string_view message;
};
} // namespace picoJSON

#endif
