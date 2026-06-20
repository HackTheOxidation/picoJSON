#ifndef READER_HPP
#define READER_HPP

#include "Token.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>


namespace picoJSON {
const std::string_view Whitespace = "\r\n\t ";
const std::string_view Digits = "1234567890";

class Reader {
public:
  Reader(const std::string_view file_name);

  std::stringstream get_content() const;

private:
  const std::string_view file_name_;
};
} // namespace picoJSON

#endif
