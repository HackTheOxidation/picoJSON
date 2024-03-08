#ifndef READER_HPP
#define READER_HPP

#include "Token.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>


namespace picoJSON {
const std::string_view Whitespace = "\r\n\t ";
const std::string_view Digits = "1234567890";

class Reader {
public:
  Reader(std::string file_name);

  std::string get_content() const;

private:
  std::string file_name_;
};
} // namespace picoJSON

#endif
